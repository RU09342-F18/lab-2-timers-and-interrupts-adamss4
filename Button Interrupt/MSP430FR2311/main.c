#include <msp430.h> 


/**
 * main.c
 */
 main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1SEL0 = 0; // selects pin 1 as gpio
    P1SEL1 = 0; // selects pin 1 as gpio seleciton has two bits so both set to 0
    P1DIR |= BIT0; // set port 1.0 as output (led)
    P1DIR &= ~(BIT1); // set port 1.1 as input (the button)

    P1REN |= BIT1; // enables pull up resistor on port 1.1
    P1OUT |= BIT1;

    P1IE |= BIT1; // enable interrupt on port 1.1
    P1IES |= BIT1; // set interrupt on falling edge
    P1IFG &= ~(BIT1); // clear interrupt flag

    _BIS_SR(LPM4_bits + GIE); // enter LPM4 mode and enable global interrupt
}                              // LPM4 = low power mode 4, CPU and all clocks disabled

    // Port 1 ISR (interrupt service routine)
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P1OUT ^= 0x01; // toggles port 1.1 on and off to turn led on or off
    P1IFG &= ~(BIT1); // clears the interrupt flag
}
