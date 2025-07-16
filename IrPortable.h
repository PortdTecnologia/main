/*****************************************************************************/
/**                          INFRARED SENSOR                                **/
/** Created: 27/05/2025  V1.1                      IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

#define IR_RXPIN    (PC0)    // MACRO OR FUNCTIONS THAT RETURN PIN STATUS
#define IRTIMEOUT   31000    // VARIABLE VALUE, RECONFIGURE FOR YOUR MCU

uint8_t IRADD =0;           // VARIABLE THAT STORES CONTROL ADDRESS
uint8_t IRCOMMAND =0;       // VARIABLE THAT STORES CONTROL COMMANDS


/*============== RX AUXILIAR FUNCTIONS-FUNCOES AUXILIARES ==============*/
volatile uint32_t IRBAUD =0;

void irgetbaud(){
    IRBAUD =0;
    while(!IR_RXPIN){ IRBAUD++; if(IRBAUD>IRTIMEOUT){ break; } }
    IRBAUD=IRBAUD+((IRBAUD/100)*20);
}

uint8_t irgetbit(){
    volatile uint32_t irb=0;
    while(IR_RXPIN){ irb++; if(irb>IRTIMEOUT){ break; } }
    if(irb>IRBAUD){ irb=1; } else{ irb=0; }
    return irb;
}

void irwait(uint8_t hl){
    volatile uint32_t w=0;
    if(hl){ while(IR_RXPIN){ w++; if(w>IRTIMEOUT){ break; } } } 
     else{ while(!IR_RXPIN){ w++; if(w>IRTIMEOUT){ break; } } }
}
/*======================================================================*/

void Ir_RX(){

    irwait(0); irwait(1);

    for(uint8_t i=0;i<8;i++){
        irgetbaud();
        if((irgetbit())){ IRADD|=(1<<i); } else{ IRADD &=~(1<<i); }        
    }
    for(uint8_t i=0;i<8;i++){
        irwait(0); irwait(1);      
    }
    for(uint8_t i=0;i<8;i++){
        irgetbaud();
        if((irgetbit())){ IRCOMMAND|=(1<<i); } else{ IRCOMMAND &=~(1<<i); }        
    }
    for(uint8_t i=0;i<8;i++){
        irwait(0); irwait(1);      
    }
    Delay_Ms(100);
}


/*=============================== TX ====================================*/
#define IR_TXSET        PORTC_OUT(4,1); //Set TX pin
#define IR_TXRESET      PORTC_OUT(4,0); //Reset TX pin
#define IR_TXFREQ       47          //Calibration of carrier at 38kHz

void Delay_IrTx(uint32_t t){            //Temporization function for TX
    volatile uint32_t i=0;
    while(i<t){i++;}
}

void IR_CARRIER(uint32_t n)
{
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = n * (SystemCoreClock / 8000000);

    SysTick->CMP = i;
    SysTick->CNT = 0;
    SysTick->CTLR |=(1 << 0);

    while(SysTick->CNT<SysTick->CMP){
        IR_TXSET; Delay_IrTx(IR_TXFREQ); IR_TXRESET; Delay_IrTx(IR_TXFREQ);
    }
    SysTick->CTLR &= ~(1 << 0);
    IR_TXRESET;
}

void IR_TX(uint8_t ADDR, uint8_t COMMAND){

    IR_CARRIER(9000);
    Delay_Us(4500);

    for(uint8_t i=0;i<8;i++){
        IR_CARRIER(562);
        if(ADDR&(1<<i)){ Delay_Us(1687); } else{ Delay_Us(562); }
    }
    for(uint8_t i=0;i<8;i++){
        IR_CARRIER(562);
        if(ADDR&(1<<i)){ Delay_Us(562); } else{ Delay_Us(1687); }
    }
    for(uint8_t i=0;i<8;i++){
        IR_CARRIER(562);
        if(COMMAND&(1<<i)){ Delay_Us(1687); } else{ Delay_Us(562); }
    }
    for(uint8_t i=0;i<8;i++){
        IR_CARRIER(562);
        if(COMMAND&(1<<i)){ Delay_Us(562); } else{ Delay_Us(1687); }
    }
    IR_CARRIER(562);

}


    //if(!PD4){Ir_RX();}
    //UART1_Printf("IR COMMAND-> 0x%x\n\r",IRCOMMAND);

/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/**          https://github.com/PortdTecnologia                **/
/****************************************************************/
