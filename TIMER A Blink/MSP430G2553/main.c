// Author: Sean Prendergast
// Code was initially started on September 18th, 2019
// Code was last modified on October 13th, 2019
// Submitted October 17th, 2019
// Exercise: Timer A for MSP430G2553

#include <msp430.h>

int main(void)
{

      WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
      P1SEL &= ~(BIT0 + BIT6);                  // Select I/O direction for P1.0 and P1.6
      P1DIR |= (BIT0 + BIT6);                    // Set P1.0 and P1.6 to output direction
      P1OUT |= ~(BIT0 + BIT6);                   // Clears the LEDs off

      TA0CCTL0 = CCIE; // Enable interrupt in compare mode
      TA0CTL = TASSEL_2 + MC_1 + ID_2; // SMCLK/4, Up
      TA0CCR0 = 250000/ 5; // 250000 / 5 = 50000, (10^6 [Hz] / 4) / (50000) = 5 Hz

      TA1CCTL0 = CCIE; // Enable interrupt in compare mode
      TA1CTL = TASSEL_2 + MC_1 + ID_2; // SMCLK/4, Up
      TA1CCR0 = 250000/ 10; // 250000 / 10 = 25000, (10^6 [Hz] / 4) / (25000) = 10 Hz



  __enable_interrupt();

  __bis_SR_register(LPM0 + GIE);
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0(void)

    {
      P1OUT ^= BIT0;                     // Toggle first LED (P1.0)
    }

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0(void)

    {
      P1OUT ^= BIT6;                     // Toggle second LED (P1.6)
    }
