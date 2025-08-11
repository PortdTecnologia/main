/*****************************************************************************/
/**                      SERIAL SYNCHRONOUS PDM V1.0                        **/
/** Created: 11/08/2025                            IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

/* Transmissao serial sincrona usando PDM Modulacao por Distancia de Pulso   */
/* Synchronous serial transmission using PDM Pulse Distance Modulation       */

#define PDMTX_HIGH     PORTC_OUT(0,1)  /* Linha em nivel alto - Level High Line */
#define PDMTX_LOW      PORTC_OUT(0,0)  /* Linha em nivel baixo - Level Low Line */
#define PDMRX          PC0             /* Leitura de entrada - Input Read       */
#define PDM_TIMER      Delay_Us        /* Temporizador - Timer                  */
uint16_t PDM_SPEED=10;               /* Velocidade da transmissao - TX Speed  */

void Delay_PDM(uint16_t d){
    volatile uint16_t dt=0;
    while(dt<d){dt++;}
}

void Pdmserial_TXbyte(uint8_t b){

    PDMTX_LOW;
    PDM_TIMER(PDM_SPEED);
    PDMTX_HIGH;
    PDM_TIMER(PDM_SPEED/2); // Amostra - Sample
    PDMTX_LOW;
    PDM_TIMER(PDM_SPEED/2);

    for(uint8_t i=0;i<8;i++){
        PDMTX_HIGH;
        if(b&1<<i){ PDM_TIMER(PDM_SPEED); } else{ PDM_TIMER(PDM_SPEED/2); }
        PDMTX_LOW;
        PDM_TIMER(PDM_SPEED/2);
    }
    PDMTX_HIGH;
    PDM_TIMER(PDM_SPEED);
}


/* PDM SERIAL RX */

volatile uint16_t PDM_RXBAUD=0;
uint16_t PDM_TIMEOUT=0;

void PDM_GETBAUD(){
    PDM_RXBAUD=0;
    PDM_TIMEOUT=0;
    while(PDMRX && PDM_RXBAUD<40000){ PDM_RXBAUD++; }
    PDM_RXBAUD=PDM_RXBAUD+(PDM_RXBAUD/4);
    PDM_TIMEOUT=PDM_RXBAUD*4;
}

uint8_t PDM_GETBIT(){
    volatile uint16_t i=0;
    while(PDMRX && i<PDM_TIMEOUT){ i++; }
    if(i<PDM_RXBAUD){ i=0; }
    return i;
}

uint8_t PdmserialRX(){

    uint8_t rx=0;
    volatile uint16_t count=0;

    while(!PDMRX && count<40000){count++;}
    count=0;
    PDM_GETBAUD();
    while(!PDMRX && count<PDM_TIMEOUT){count++;}
    count=0;

    for(uint8_t i=0;i<8;i++){
        if((PDM_GETBIT())){ rx|=(1<<i); }
        while(!PDMRX && count<PDM_TIMEOUT){count++;}
        count=0;
    }
    return rx;
}

/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/****************************************************************/