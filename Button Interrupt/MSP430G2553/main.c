#include <msp430.h> 


/**
 * main.c
 */
 main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1SEL = 0; // selects pin 1 as gpio
    P1DIR |= BIT0; // set port 1.0 as output (led)
    P1DIR &= ~(BIT3); // set port 1.3 as input (the button)

    P1REN |= BIT3; // enables pull up resistor on port 1.3
    P1OUT |= BIT3;

    P1IE |= BIT3; // enable interrupt on port 1.3
    P1IES |= BIT3; // set interrupt on falling edge
    P1IFG &= ~(BIT3); // clear interrupt flag

    _BIS_SR(LPM4_bits + GIE); // enter LPM4 mode and enable global interrupt
}                              // LPM4 = low power mode 4, CPU and all clocks disabled

    // Port 1 ISR (interrupt service routine)
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P1OUT ^= 0x01; // toggles port 1.3 on and off
    P1IFG &= ~(BIT3); // clears the interrupt flag
}


