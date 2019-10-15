# TIMER A Blink
The TIMER peripherals can be used in many situations thanks to it flexibility in features. For this lab, you will be only scratching the surface as to what this peripheral can do. 

## Up, Down, Continuous 
There are a few different ways that the timer module can count. For starters, one of the easiest to initialize is Continuous counting where in the TIMER module will alert you when its own counting register overflows. Up mode allows you to utilize a Capture/Compare register to have the counter stop at a particular count and then start back over again. You can also set the TIMER to Up/Down mode where upon hitting a counter or the overflow, instead of setting the counter back to zero, it will count back down to zero. 

## Task
Using the TIMER module instead of a software loop, control the speed of two LEDS blinking on your development boards. Experiment with the different counting modes available as well as the effect of the pre-dividers. Why would you ever want to use a pre-divider? What about the Capture and Compare registers? Your code should include a function (if you want, place it in its own .c and .h files) which can convert a desired Hz into the proper values required to operate the TIMER modules.

### Extra Work
#### Thinking with HALs
So maybe up to this point you have noticed that your software is looking pretty damn similar to each other for each one of these boards. What if there was a way to abstract away all of the particulars for a processor and use the same functional C code for each board? Just for this simple problem, why don't you try and build a "config.h" file which using IFDEF statements can check to see what processor is on board and initialize particular registers based on that.

#### Low Power Timers
Since you should have already done a little with interrupts, why not build this system up using interrupts and when the processor is basically doing nothing other than burning clock cycles, drop it into a Low Power mode. Do a little research and figure out what some of these low power modes actually do to the processor, then try and use them in your code. If you really want to put your code to the test, using the MSP430FR5994 and the built in super cap, try and get your code to run for the longest amount of time only using that capacitor as your power source.

# Sean Prendergast

## Timer A Blink

For this assignment, all implemented code would be written in C with the ultimate goal consisting of having two LEDs blink on and off at different frequencies through the utilization of interrupts. For both processors, the interrupts utilized in this assignment were from within Timer A. As two LEDs needed to blink at different frequencies, two timers were used. Both implemented timers were built to count to different, specified values and once these specific values were reached for both timers, an interrupt would be enabled. For this assignment, the interrupt would be used to toggle the LED blink on and off.

## Processors Utilized
* MSP430FR6989
* MSP430G2553

## Dependencies
This library would only be dependent on the MSP430.h header file used for all TI MSP430 processors. The MSP430.h header file is included in each C file submitted as no other header files were required for the assignment.

## Differences in implementation for FR6989 and G2553
One difference regarding the implementation for both boards, which will probably be seen for many assignments this semester, was that for the MSP430FR6989, the GPIO power-on default high impedance mode had to be disabled prior to testing. The reason behind this action is because the user will not be able to access any previously configured port settings if the default high-impedance mode isn't disabled. To put this into simpler terms, the user will not be able to utilize the appropriate ports and bits assigned to the on-board LEDs if this mode isn't disabled. The only other difference seen in both boards was the designated pins and bits assigned to the on-board button/switch. For both programs, these pins and bits were easily rearranged to ensure the appropriate ones assigned specificially to the on-board button/switch were utilized effectively.
