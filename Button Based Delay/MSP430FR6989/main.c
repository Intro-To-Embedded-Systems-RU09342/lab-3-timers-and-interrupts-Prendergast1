// Author: Sean Prendergast
// Code was initially started on September 18th, 2019
// Code was last modified on October 5th, 2019
// Submitted October 17th, 2019
// Exercise: Button Based Delay for MSP430FR6989

#include <msp430.h>

// Global variable is utilized to count
static volatile int counter = 0;

int main(void)
{
      WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer (WDT)

      P1DIR |= BIT0;                          // Set P1.0 (LED) to output direction
      P1OUT |= BIT1;                          // Set P1.1 (button/switch) to output direction
      P1DIR &= ~BIT1;                         // Change P1.1 (button/switch) from output to input
      P1REN |= BIT1;                          /* Enables internal resistor such that P1.3 (Pin 1, Bit 3)
                                              can be connected to 3.6 V (VCC) or ground (GND)*/
      P1IES &= ~BIT1;                         // Set interrupt flag on low to high
      P1IE |= BIT1;                           // Enable interrupt for button/switch (P1.3)
      P1IFG &= ~BIT1;                         // Clear button/switch (P1.3) interrupt flag so no immediate interrupt


      // Disable the GPIO power-on default high-impedance mode to activate
      // previously configured port settings
      PM5CTL0 &= ~LOCKLPM5;

      TA0CCTL0 = CCIE;                          // TA0CCR0 interrupt enabled
      TA0CCR0 = 3277;                           // TA0 set the max value to count to
      TA0CTL = TASSEL__ACLK | MC__UP;           // ACLK, up mode
      TA0CTL |= TACLR;                          // Clear

      TA1CCTL0 |= CCIE;                         // TA1CCR0 interrupt enabled
      TA1CTL = TASSEL__ACLK | MC__STOP;         // Configure second timer
      TA1CCR0 = 512;                            // Set value of TA1CCR0 for comparison
      TA1CTL |= ID_3;                           // Divide clock by 8
      TA1EX0 |= TAIDEX_7;                       // Divide clock further by 8 to 512 hz
      TA1CTL |= TACLR;                          // Clear

      __enable_interrupt();                     // Enable interrupt

      for(;;)
      {
      while(!(P1IN & BIT1))                    // When the button (P1.3) is pressed
              {
                  if(TA1R == 0)                // If value in Timer1 = 0
                  {
                      TA1CTL |= TASSEL_1 + MC__UP;    // Pick ACLK & Set Counter to Up Mode
                  }
              }
      }
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)       // Timer 0 interrupt
{
    P1OUT ^= BIT0;                          // Toggle LED (P1.0)
}

// Timer1_A0 interrupt service routine
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR (void)       // Timer 1 interrupt
{
    counter++;                              // Enable counter
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)               // Button interrupt
{
      TA1CTL &= ~TASSEL_1;                  // Disable TA1
      TA0CCR0 = (counter)*3277;             // Multiply the slowed down counter
      TA1CTL |= TACLR;                      // Clear Timer A1
      P1IFG &= ~BIT1;                       // Clear P1.1 flag
}
