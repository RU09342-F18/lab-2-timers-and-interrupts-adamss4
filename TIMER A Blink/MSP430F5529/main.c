#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1SEL = 0; // selects pin 1.0 as gpio
    P1DIR |= BIT0; // set port 1.0 as output (led)
    P1OUT = 0; // sets the led to start as off



    TA0CCTL0 = CCIE; // enables interrupt on timer A0
    TA0CCR0 = 12000; // timer A0 counts to 12000
    TA0CTL = TASSEL_1 + MC_1; // sets timer A to up mode


    __bis_SR_register(LPM0_bits + GIE); // sets LPM0, and enables global interrupt
    // CPU and MCLK are disabled, SMCLK and ACLK are active
}
    // Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer_A (void){
        P1OUT ^= 0x01; // toggles the led on and off
    }

