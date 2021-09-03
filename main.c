#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //button 1 init:
    P5-> SEL0 &= ~BIT1; //GPIO
    P5-> SEL1 &= ~BIT1; //GPIO
    P5-> DIR &= ~BIT1;  //input
    P5-> REN |= BIT1;   //resistor enable
    P5-> OUT |= BIT1;   //pull-up

    P5-> IES |= BIT1;   // Port X Interrupt Edge Select Register
    P5-> IE  |= BIT1;   // Port X Interrupt Enable Register

    //button 2 init:
    P5-> SEL0 &= ~BIT2; //GPIO
    P5-> SEL1 &= ~BIT2; //GPIO
    P5-> DIR &= ~BIT2; //input
    P5-> REN |= BIT2; //resistor enable
    P5-> OUT |= BIT2; //pull-up
    P5-> IES |= BIT2; // Interrupt Service Routine
    P5-> IE  |= BIT2;

    //red, green, blue (respectively)LED init:
    P2-> SEL1 &= ~(BIT4 | BIT5 | BIT6); //GPIO
    P2-> SEL0 &= ~(BIT4 | BIT5 | BIT6); //GPIO
    P2-> DIR |= (BIT4 | BIT5 | BIT6); //output
    P2-> OUT &= ~(BIT4 | BIT5 | BIT6); //init to all off

    //RGB test:
    while(1){
        P2->OUT |= BIT4;
    }
}
