// Author: Sean Prendergast
// Code was initially started on September 26th, 2019
// Code was last modified on October 15th, 2019
// Submitted October 17th, 2019
// Exercise: Button Interrupt for MSP430FR6989

#include <msp430.h>     // header file for MSP430

/* The purpose of incorporating a static volatile variable for the enable_blink variable
 * is to showcase the compiler will not perform optimizations to store away
 * the value placed in enable_blink. Static volatile is utilized for convenience
 * as it tells the compiler to run code to read the value stored in enable_blink in memory.
 */
static volatile int enable_blink = 0;;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer (WDT)

    P1REN |= BIT1;                          /* Enables internal resistor such that P1.1 (Pin 1, Bit 1)
                                            can be connected to 3.6 V (VCC) or ground (GND)*/
    P1DIR |= BIT0;                          // Set P1.0 (Pin 1, Bit 0) as the output pin, P1.0 is LED1 on board
    P1OUT |= BIT1;                          /* Set P1.1 (Pin 1, Bit 1) as the input pin, in other words,
                                            the internal resistor is connected to 3.6 V (VCC) and functions as a pull-up resistor.*/
    P1IE |= BIT1;                           // Enable interrupts for button/switch (P1.1)
    P1IES |= BIT1;                          // Enable interrupts for button/switch (P1.1) at rising edge of clock
    P1IFG &= ~BIT1;                         // Clears interrupt flag for P1.1

    __enable_interrupt();                   // Function to enable interrupts

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
                                            // Without this line of code (line 31), none of the ports
                                            // such as buttons and LEDs can't be utilized

    while(1)
    {
        if (enable_blink == 1)              // If the button is pressed by the user
        {
            P1OUT ^= BIT0;                      // The LED will toggle at a set rate
            __delay_cycles(100000);
        }
    }

}

// Function to make interrupts tick
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)           // Button Interrupt for Port 1 (P1.3)
{
    enable_blink ^= 1;                   // Enable blink
    P1IFG &= ~BIT1;                       // Clears interrupt flag for P1.3
}
