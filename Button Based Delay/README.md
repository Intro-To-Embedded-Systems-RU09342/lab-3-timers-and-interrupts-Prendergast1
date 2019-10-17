# Sean Prendergast

## Button Based Delay

For this assignment, all implemented code would be written in C with the ultimate goal consisting of utilizing the timer to blink the on-board LED on and off at a set, constant rate, followed by altering the rate the LED toggles at from the press of the on-board button/switch. To achieve this certain task, three interrupts would need to be incorporated. To begin, the first interrupt would be to utilized to initially blink the on-board LED at the constant rate set for the first timer, Timer 0. The following interrupt would be used to enable a counter built to stop counting once the on-board button/switch is released by the user. The purpose of the third interrupt is to change the value the first timer is counting up to the new value from the second interrupt.  

## Processors Utilized
* MSP430FR6989
* MSP430G2553

## Dependencies
This library would only be dependent on the MSP430.h header file used for all TI MSP430 processors. The MSP430.h header file is included in each C file submitted as no other header files were required for the assignment.

## Differences in implementation for FR6989 and G2553
One difference regarding the implementation for both boards, which will probably be seen for many assignments this semester, was that for the MSP430FR6989, the GPIO power-on default high impedance mode had to be disabled prior to testing. The reason behind this action is because the user will not be able to access any previously configured port settings if the default high-impedance mode isn't disabled. To put this into simpler terms, the user will not be able to utilize the appropriate ports and bits assigned to the on-board LEDs if this mode isn't disabled. The only other difference seen in both boards was the designated pins and bits assigned to the on-board button/switch. For both programs, these pins and bits were easily rearranged to ensure the appropriate ones assigned specificially to the on-board button/switch were utilized effectively.
