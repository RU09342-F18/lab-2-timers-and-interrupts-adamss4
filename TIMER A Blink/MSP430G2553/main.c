#include <msp430.h>


/**
 * main.c
 */
// unsigned int timerCount = 0; // creates an unsigned int for the timer count
void main(void)
{
 	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1SEL = 0; // selects pin 1.0 as gpio
	P1DIR |= BIT0; // set port 1.0 as output (led)
	P1OUT = 0; // sets the led to start as off


	BCSCTL3 = LFXT1S_2; // switches A clock to internal oscillator
	TACCTL0 = CCIE; // enables interrupt on timer A0
	TACCR0 = 12000; // timer A0 counts to 12000
    TACTL = TASSEL_1 + MC_1; // sets timer A to up mode


	__bis_SR_register(LPM0_bits + GIE); // sets LPM0, and enables global interrupt
	// CPU and MCLK are disabled, SMCLK and ACLK are active
}
	// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
	__interrupt void Timer_A (void){
	    P1OUT ^= 0x01; // toggles the led on and off
	}

