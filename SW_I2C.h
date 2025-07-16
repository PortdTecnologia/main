/*****************************************************************************/
/**                          SOFTWARE I2C V1.0                              **/
/** Created: 15/07/2025                            IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

/* DRIVER CONFIG */
#define SWSDA_HIGH   PORTC_OUT(1,1)
#define SWSDA_LOW    PORTC_OUT(1,0)
#define SWSDA_READ   PC1
#define SWSCL_HIGH   PORTC_OUT(2,1)
#define SWSCL_LOW    PORTC_OUT(2,0)

#define SWSDA_OUT    TRISCbits(1,Out30OD);
#define SWSDA_IN     TRISCbits(1,InFloat);

#define SWI2C_T      Delay_Us(SWI2C_SPEED)
uint16_t SWI2C_SPEED = 5;


/*= FUNCOES BASE - BASE FUNCTIONS =*/

void I2C_START(){
    SWSDA_OUT; 
    SWSCL_HIGH; SWSDA_HIGH; SWI2C_T;
    SWSDA_LOW; SWI2C_T; SWSCL_LOW; SWI2C_T;
}

void I2C_STOP(){
    SWSDA_OUT;
    SWSDA_LOW; SWI2C_T;
    SWSCL_HIGH; SWI2C_T; SWSDA_HIGH; SWI2C_T;
}

uint8_t I2C_ACK(){
    uint8_t n=0;
    SWSDA_IN;
    if(SWSDA_READ){ n=1; }
    SWSDA_OUT; SWSDA_LOW;
    SWSCL_HIGH; SWI2C_T; SWSCL_LOW; SWI2C_T;
    return n;
}

uint8_t I2C_DATAIN(){

    SWSDA_IN;
    uint8_t DATA=0;
    for(uint8_t i=8;i>0;i--){
        if(SWSDA_READ){ DATA |= (1<<(i-1)); }
        SWSCL_HIGH; SWI2C_T; SWSCL_LOW; SWI2C_T;
    }
    return DATA;
}

void I2C_DATAOUT(uint8_t b){
    SWSDA_OUT;
    for(uint8_t i=8;i>0;i--){
        if(b&(1<<(i-1))){ SWSDA_HIGH; } else{ SWSDA_LOW; }
        SWI2C_T;
        SWSCL_HIGH; SWI2C_T; SWSCL_LOW; SWI2C_T;
    }
}

void I2C_SEND_ADD(uint8_t address, uint8_t rw){
    uint8_t add=address<<1;
    if(address<=127){
        if(rw){ add|=(1<<0); } else{ add &=~(1<<0); }
        I2C_DATAOUT(add);
    }
}

void I2C_SCAN(){

    uint8_t f=0;

    for(uint8_t i=0;i<=127;i++){
        I2C_START();
        I2C_SEND_ADD(i,1);
        if(!(I2C_ACK())){ f=1; UART1_Printf("FOUND-> %d\n\r",i); }
        I2C_STOP();
    }
    if(!f){ UART1_Printf("DEVICE NOT FOUND\n\r"); }
}



/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/****************************************************************/