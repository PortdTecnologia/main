/*****************************************************************************/
/**                        SHIFT REGISTER 74HC595                           **/
/** Created: 10/06/2025  V1.0                      IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

/* DRIVER CONFIG */
#define SR74_BITL    PORTC_OUT(1,0)  // Reset data pin to 0
#define SR74_BITH    PORTC_OUT(1,1)  // Set data pin to 1
#define SR74_CLKL    PORTC_OUT(2,0)  // Reset clock pin to 0
#define SR74_CLKH    PORTC_OUT(2,1)  // Set clock pin to 1
#define SR74_ATTL    PORTC_OUT(3,0)  // Reset ATT pin(RCLK) to 0
#define SR74_ATTH    PORTC_OUT(3,1)  // Set ATT pin(RCLK) to 1

/*=========================== MODO 8 BITS MSB ================================*/
void SR_OUT(uint8_t b){

    for(uint8_t i=8;i>0;i--){
        if(b&(1<<(i-1))){ SR74_BITH; } else{ SR74_BITL; }
        SR74_CLKH; SR74_CLKL;
    }
    SR74_ATTH; SR74_ATTL;
}

/*==================== MODO VARIAVEL MSB - VARIABLE MODE =====================*/

void SR_OUT_V(uint8_t size, uint32_t b){

    for(uint8_t i=size;i>0;i--){
        if(b&(1<<(i-1))){ SR74_BITH; } else{ SR74_BITL; }
        SR74_CLKH; SR74_CLKL;
    }
    SR74_ATTH; SR74_ATTL;
}

/*==================== EXPANS?O DE PORTS - PORTS EXPANDER =====================*/

uint8_t PORTE=0;
uint8_t PORTF=0;

void PORTE_OUT(uint8_t pin,uint8_t hl){

    if(hl){ PORTE|=(1<<pin); }else{ PORTE &= ~(1<<pin); }

    for(uint8_t i=8;i>0;i--){
        if(PORTF&(1<<(i-1))){ SR74_BITH; } else{ SR74_BITL; }
        SR74_CLKH; SR74_CLKL;
    }
    for(uint8_t i=8;i>0;i--){
        if(PORTE&(1<<(i-1))){ SR74_BITH; } else{ SR74_BITL; }
        SR74_CLKH; SR74_CLKL;
    }
    SR74_ATTH; SR74_ATTL;
}

void PORTF_OUT(uint8_t pin,uint8_t hl){

    if(hl){ PORTF|=(1<<pin); }else{ PORTF &= ~(1<<pin); }

    for(uint8_t i=8;i>0;i--){
        if(PORTF&(1<<(i-1))){ SR74_BITH; } else{ SR74_BITL; }
        SR74_CLKH; SR74_CLKL;
    }
    for(uint8_t i=8;i>0;i--){
        if(PORTE&(1<<(i-1))){ SR74_BITH; } else{ SR74_BITL; }
        SR74_CLKH; SR74_CLKL;
    }
    SR74_ATTH; SR74_ATTL;
}


/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/**          https://github.com/PortdTecnologia                **/
/****************************************************************/