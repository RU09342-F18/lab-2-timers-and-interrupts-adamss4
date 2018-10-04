# TIMER A Blink
In this code, The timer A peripheral was utilized to blink the led at a user set rate
in the code. First, the inputs and outputs were set up as normal for the LED, exactly 
the same as if blinking an LED using a loop or a button. Next, instead of a loop, the
Timer A peripheral was initialized, and set into continuous counting mode. Before
initializing the A clock, the line of code BCSCTL3 = LFXT1S_2; was used to set the 
internal oscillator of the MSP430G2553 as A clock, which has a frequency of 1.2 MHz.
This code was not needed for the F5529 due to the A clock already using the internal
oscillator by default. Interrupts were enabled on timer A0 by setting the TACCTL0
register to CCIE. This was the same for the 5529, except the register name was TA0CCTL
instead. Next, the value where the interrupt occurs was set by setting register 
TACCR0 to 12000, which would cause the LED to blink at approximately 1 Hz. Similar to 
enabling interrupt, the register for the 5529 was TA0CCR0 instead. Finally, Timer A was 
then set to Continous mode for both codes, which has the timer count from zero to 0FFFFh,
by setting register TACTL to TASSEL_1, which selects timer A, OR'ed with MC_1, which sets
the timer to continuous mode. For the F5529, it was register TACTL0 that was set, while
the code to set the timer reamined the same. Once the timer was set up, the ISR for timer
A0 was set up using the vector TIMER0_A0_VECTOR, which was the same for both boards, and
inside the ISR, P1OUT was XOR'ed with 0x01, which toggles the LED on and off whenever the
counter counts to 12000.
