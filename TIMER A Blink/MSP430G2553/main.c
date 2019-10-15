// Author: Sean Prendergast
// Code was initially started on September 26th, 2019
// Code was last modified on October 15th, 2019
// Submitted October 17th, 2019
// Exercise: Timer A Blink for MSP430G2553

#include <msp430.h>

int main(void)
{

      WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer (WDT)
      P1SEL &= ~(BIT0 + BIT6);                  // Select I/O (Input/Output) direction for P1.0 and P1.6 (LED1 and LED2)
      P1DIR |= (BIT0 + BIT6);                   // Set P1.0 (LED1) and P1.6 (LED2) to output direction
      P1OUT |= ~(BIT0 + BIT6);                  // Clears P1.0 and P1.6 off

      // Timer 0
      TA0CCTL0 = CCIE;                          // Enable interrupt in compare mode
      TA0CTL = TASSEL_2 + MC_1 + ID_2;          // SMCLK/4, Up
      TA0CCR0 = 250000/ 5;                      // 250000 / 5 = 50000, (10^6 [Hz] / 4) / (50000) = 5 Hz

      // Timer 1
      TA1CCTL0 = CCIE;                          // Enable interrupt in compare mode
      TA1CTL = TASSEL_2 + MC_1 + ID_2;          // SMCLK/4, Up
      TA1CCR0 = 250000/ 10;                     // 250000 / 10 = 25000, (10^6 [Hz] / 4) / (25000) = 10 Hz



      __enable_interrupt();                     // Enable interrupt

      __bis_SR_register(LPM0 + GIE);             // Input LPMO (Low-power mode 0) with GIE (General Interrupt Enable)
}

// Timer 0 Interrupt
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0(void)

    {
      P1OUT ^= BIT0;                     // Toggle first LED (P1.0)
    }

// Timer 1 Interrupt
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0(void)

    {
      P1OUT ^= BIT6;                     // Toggle second LED (P1.6)
    }
