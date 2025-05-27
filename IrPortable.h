/*****************************************************************************/
/**                          INFRARED SENSOR                                **/
/** Created: 27/05/2025  V1.0                      IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

#define IR_RXPIN   (PD4)    // MACRO OR FUNCTIONS THAT RETURN PIN STATUS
#define IRTIMEOUT  31000    // VARIABLE VALUE, RECONFIGURE FOR YOUR MCU

uint8_t IRADD =0;           // VARIABLE THAT STORES CONTROL ADDRESS
uint8_t IRCOMMAND =0;       // VARIABLE THAT STORES CONTROL COMMANDS


/*============== AUXILIAR FUNCTIONS-FUNCOES AUXILIARES ==============*/
volatile uint32_t IRBAUD =0;

void irgetbaud(){
    IRBAUD =0;
    while(!IR_RXPIN){ IRBAUD++; if(IRBAUD>IRTIMEOUT){ break; } }
    IRBAUD=IRBAUD+(IRBAUD * 0.20);
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
/*===================================================================*/

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


    //if(!PD4){Ir_RX();}
    //UART1_Printf("IR COMMAND-> 0x%x\n\r",IRCOMMAND);

/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/**          https://github.com/PortdTecnologia                **/
/****************************************************************/