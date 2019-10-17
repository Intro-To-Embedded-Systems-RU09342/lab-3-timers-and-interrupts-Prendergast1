# Sean Prendergast

## Button Interrupt

For this assignment, all implemented code would be written in C with the ultimate goal consisting of allowing an LED to blink on and off initially and then stopped from the press of a button. If the button were to be pressed by the user again, the LED would continue to blink on and off at the set rate it was blinking at intially when the program is ran. In order to achieve this specific task, an interrupt has to be implemented. The procedure for this assignment is nearly the same as "Button Blink", apart from the interrupt implementation. With the introduction of the interrupt, its role was to alter the value of the volatile variable between 1 and 0 to enable and disable the LED blinking respectively. A pragma vector was incorporated to have a specific action occur when an interrupt occurs.

## Processors Utilized
* MSP430FR6989
* MSP430G2553

## Dependencies
This library would only be dependent on the MSP430.h header file used for all TI MSP430 processors. The MSP430.h header file is included in each C file submitted as no other header files were required for the assignment.

## Differences in implementation for FR6989 and G2553
One difference regarding the implementation for both boards, which will probably be seen for many assignments this semester, was that for the MSP430FR6989, the GPIO power-on default high impedance mode had to be disabled prior to testing. The reason behind this action is because the user will not be able to access any previously configured port settings if the default high-impedance mode isn't disabled. To put this into simpler terms, the user will not be able to utilize the appropriate ports and bits assigned to the on-board LEDs if this mode isn't disabled. The only other difference seen in both boards was the designated pins and bits assigned to the on-board button/switch. For both programs, these pins and bits were easily rearranged to ensure the appropriate ones assigned specificially to the on-board button/switch were utilized effectively.
