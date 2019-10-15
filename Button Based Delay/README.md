# Button Based Delay
Now that you have begun to familiarize yourself with the TIMER modules, why don't we make an interesting change to our code from the last lab.

## Task
Setup your microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of the buttons on board, a user should be able to set the delay or blinking rate of the LED by holding down a button. The duration in which the button is depressed should then become the new rate at which the LED blinks. As previously stated, you most likely will want to take advantage of the fact that TIMER modules exist and see if you can let them do a bulk of the work for you.

### Extra Work
## Reset Button
What is a piece of electronics without a reset button? Instead of relying on resetting your processor using the built in reset circuitry, why not instead use another button to reset the rate back to 10Hz.

## Button Based Hertz
Most likely using two buttons, what if instead of making a delay loop based on the time, the user could instead enter a mode where the number of times they pressed the button would become the number in Hz of the blinking rate? How do you think you would implement that with just one button?

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
