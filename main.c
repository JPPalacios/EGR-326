#include "msp.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //  Port 5.1 Button 1, 5.2 Button 2
    P5->SEL0 &= ~(BIT1 | BIT2);  // GPIO
    P5->SEL1 &= ~(BIT1 | BIT2);  // GPIO
    P5->DIR  &= ~(BIT1 | BIT2);  // Direction Register -> Input
    P5->REN  |=  (BIT1 | BIT2);  // Resistor Enable Register
    P5->OUT  |=  (BIT1 | BIT2);  // Data Output Register -> Pull-up
    P5->IES  |=  (BIT1 | BIT2);  // Interrupt Edge Select Register
    P5->IE   |=  (BIT1 | BIT2);  // Interrupt Enable Register

    P5->IFG   = 0;               // Clear Interrupt Flags

    // Port 2.4 Red LED, 2.5 Green LED, 2.6 Blue LED
    P2->SEL1 &= ~(BIT4 | BIT5 | BIT6);  // GPIO
    P2->SEL0 &= ~(BIT4 | BIT5 | BIT6);  // GPIO
    P2->DIR  |=  (BIT4 | BIT5 | BIT6);  // Direction Register -> Output
    P2->OUT  &= ~(BIT4 | BIT5 | BIT6);  // Data Output Register -> Pull-down

    //enable port interrupts:
    NVIC->ISER[5] = (1 << ((PORT5_IRQn) & 31)); //enable Port 5 interrupt on the NVIC
    __enable_interrupt();

    while(1){

    }

}

void PORT5_IRQHandler(void){ //port 5 ISR

        ///RGB///
    int checkColor1 = 0;
    int reset = 0;

    if(P5->BIT1){
        if((checkColor1 == 0) && (reset == 0)){
            P2->OUT |= BIT4; //set red LED on
            checkColor1++;
            reset = 1;
        }

        else if ((checkColor1 == 1) && (reset == 1)){
            P2->OUT ^= BIT4; //toggle red LED from on to off
            P2->OUT ^= BIT5; //toggle green LED from off to on
            checkColor1++;
        }

        else if ((checkColor1 == 2) && (reset == 1)){
            P2->OUT ^= BIT5; //toggle green LED from on to off
            P2->OUT ^= BIT6; //toggle blue LED from off to on
            checkColor1++;
        }

        else {
            P2->OUT &= ~(BIT4 | BIT5 | BIT6); //clear all
            P2->OUT |= BIT4; //set red LED high
            checkColor1 = 1; //reset color check value for next iteration thru
        }
    } else if(P5->BIT2){
        P2->OUT &= ~(BIT4 | BIT5 | BIT6); //clear all
    }

    P5->IFG = 0; //clear interrupt flags
}
