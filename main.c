#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //  Port 5.1 - Button 1
    P5->SEL0 &= ~BIT1;  // GPIO
    P5->SEL1 &= ~BIT1;  // GPIO
    P5->DIR  &= ~BIT1;  // Direction Register -> Input
    P5->REN  |=  BIT1;  // Resistor Enable Register
    P5->OUT  |=  BIT1;  // Data Output Register -> Pull-up
    P5->IES  |=  BIT1;  // Interrupt Edge Select Register
    P5->IE   |=  BIT1;  // Interrupt Enable Register

    //  Port 5.2 - Button 1
    P5->SEL0 &= ~BIT2;  // GPIO
    P5->SEL1 &= ~BIT2;  // GPIO
    P5->DIR  &= ~BIT3;  // Direction Register -> Input
    P5->REN  |=  BIT2;  // Resistor Enable Register
    P5->OUT  |=  BIT2;  // Data Output Register -> Pull-up
    P5->IES  |=  BIT2;  // Interrupt Edge Select Register
    P5->IE   |=  BIT2;  // Interrupt Enable Register

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
