#include "msp.h"

void Port2_Init(void);
void Port5_Init(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //enable port interrupts:
    NVIC->ISER[5] = (1 << ((PORT5_IRQn) & 31)); //enable Port 5 interrupt on the NVIC
    __enable_interrupt();

    Port2_Init();
    Port5_Init();

    while(1){
// goodbye testing
    }
}

// Port 2.4 Red LED, 2.5 Green LED, 2.6 Blue LED
void Port2_Init(void){

    P2->SEL1 &= ~(BIT4 | BIT5 | BIT6);  // GPIO
    P2->SEL0 &= ~(BIT4 | BIT5 | BIT6);  // GPIO
    P2->DIR  |=  (BIT4 | BIT5 | BIT6);  // Direction Register -> Output
    P2->OUT  &= ~(BIT4 | BIT5 | BIT6);  // Data Output Register -> Pull-down
}

//  Port 5.1 Button 1, 5.2 Button 2
void Port5_Init(void){

    P5->SEL0 &= ~(BIT1 | BIT2);  // GPIO
    P5->SEL1 &= ~(BIT1 | BIT2);  // GPIO
    P5->DIR  &= ~(BIT1 | BIT2);  // Direction Register -> Input
    P5->REN  |=  (BIT1 | BIT2);  // Resistor Enable Register
    P5->OUT  |=  (BIT1 | BIT2);  // Data Output Register -> Pull-up
    P5->IES  |=  (BIT1 | BIT2);  // Interrupt Edge Select Register
    P5->IE   |=  (BIT1 | BIT2);  // Interrupt Enable Register

    P5->IFG   = 0;               // Clear Interrupt Flags
}

void Port5_IRQHandler(void){
    if(P5->IFG & BIT1){ // If P5.1 had an interrupt (going from high to low)
        P2->OUT ^= BIT4; // Toggling the output on the LED
        P2->OUT &= ~(BIT5 | BIT6);
    }

    P5->IFG &= ~BIT1; // Reset the interrupt flag
}
