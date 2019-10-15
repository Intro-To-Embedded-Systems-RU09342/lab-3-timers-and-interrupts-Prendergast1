// Author: Sean Prendergast
// Code was initially started on September 26th, 2019
// Code was last modified on October 15th, 2019
// Submitted October 17th, 2019
// Exercise: Button Based Delay for MSP430G2553

#include <msp430.h>

// Global variable is utilized to count
static volatile int counter = 0;

int main(void)
{
      WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer (WDT)

      P1DIR |= BIT0;                          // Set P1.0 (LED) to output direction
      P1OUT |= BIT3;                          // Set P1.3 (button/switch) to output direction
      P1DIR &= ~BIT3;                         // Change P1.3 (button/switch) from output to input
      P1REN |= BIT3;                          /* Enables internal resistor such that P1.3 (Pin 1, Bit 3)
                                              can be connected to 3.6 V (VCC) or ground (GND)*/
      P1IES &= ~BIT3;                         // Set interrupt flag on low to high
      P1IE |= BIT3;                           // Enable interrupt for button/switch (P1.3)
      P1IFG &= ~BIT3;                         // Clear button/switch (P1.3) interrupt flag so no immediate interrupt

      TA0CCTL0 = CCIE;                          // TA0CCR0 interrupt enabled
      TA0CCR0 = 3277;                           // TA0 set the max value to count to
      TA0CTL = TASSEL_1 | MC_1;                 // ACLK, up mode
      TA0CTL |= TACLR;                          // clear

      TA1CCTL0 |= CCIE;                         // TA1CCR0 interrupt enabled
      TA1CTL = TASSEL_1 | MC_0;                 // ACLK, stop mode
      TA1CCR0 = 4096;                           // Set value of TA1CCR0 for comparison
      TA1CTL |= ID_3;                           // Divide clock by 8
      TA1CTL |= TACLR;                          // Clear

      __enable_interrupt();                     // Enable interrupt

      for(;;)
      {
      while(!(P1IN & BIT3))                     // When the button (P1.3) is pressed
              {
                  if(TA1R == 0)                 // If the value of Timer1 = 0
                  {
                      TA1CTL |= TASSEL_1 + MC_1;    // Pick ACLK & Set Counter to Up Mode
                  }
              }
      }
}

// Timer0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)       // Timer 0 interrupt
{
    P1OUT ^= BIT0;                        // Toggle LED (P1.0)
}

// Timer1_A0 interrupt service routine
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR (void)           // Timer 1 Interrupt
{
    counter++;                                  // Enable counter
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)                   // Button Interrupt
{
      TA1CTL &= ~TASSEL_1;                      // Disable TA1
      TA0CCR0 = counter*3277;                   // Multiply the slowed down counter
      TA1CTL |= TACLR;                          // Clear Timer A1
      P1IFG &= ~BIT3;                           // Clear P1.3 flag
}
