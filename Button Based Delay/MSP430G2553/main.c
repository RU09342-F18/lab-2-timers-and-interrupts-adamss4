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
    P1DIR &= ~(BIT3); // set port 1.3 as input (the button)

    P1REN |= BIT3; // enables pull up resistor on port 1.3
    P1OUT |= BIT3;

    P1IE |= BIT3; // enable interrupt on port 1.3
    P1IES |= BIT3; // set interrupt on falling edge
    P1IFG &= ~(BIT3); // clear interrupt flag

    BCSCTL3 = LFXT1S_2; // switches A clock to internal oscillator
    TACCTL0 = CCIE; // enables interrupt on timer A0
    TACCR0 = 1200; // timer A0 counts to 1200, or 10Hz
    TACTL = TASSEL_1 + MC_1; // sets timer A to up mode


    __bis_SR_register(LPM0_bits + GIE); // sets LPM0, and enables global interrupt
    // CPU and MCLK are disabled, SMCLK and ACLK are active
}
    // Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer_A (void){
        P1OUT ^= 0x01; // toggles the led on and off
    }
    // Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
    __interrupt void Port_1(void){
        if (P1IES & BIT3){
            TACTL = TASSEL_1 + MC_2 + ID_3; // timer counts in continuous mode, clock divided by 8 or 1500KHz
            TACTL = TACCR0;
        }
        else if (P1IES & ~(BIT3)){
            TACTL = TASSEL_1 + MC_0;// stops counting
            TACCR0 = TAR; // new delay gets stored in TACCR0

        }
        P1IFG &= ~(BIT3); // clears interrupt flag
        TACTL = TASSEL_1 + MC_1; // sets timer back to up mode
    }
