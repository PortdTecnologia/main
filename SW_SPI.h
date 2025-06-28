/*****************************************************************************/
/**                             SOFTWARE SPI                                **/
/** Created: 26/06/2025  V1.1                      IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

// V1.1 => 28/06/2025 Changelog - Alteracoes
// Separate Low-Speed SW SPI and High-Speed SW SPI
// Separadas as funcoes de baixa e alta velocidade


/* DRIVER CONFIG */
#define SPI_CLK_HIGH    PORTC_OUT(4,1)      // SCLK PIN HIGH
#define SPI_CLK_LOW     PORTC_OUT(4,0)      // SCLK PIN LOW
#define SPI_SDO_HIGH    PORTC_OUT(6,1)      // MOSI PIN HIGH
#define SPI_SDO_LOW     PORTC_OUT(6,0)      // MOSI PIN LOW
#define SPI_SDI         PC7                 // MISO PIN READ

#define SPI_TEMP        Delay_Us(SPI_SPEED) // CONTROLE DE VELOCIDADE - SPEED

#define SPI_CS1_HIGH    PORTC_OUT(3,1)       // CHIP SELECT PIN HIGH
#define SPI_CS1_LOW     PORTC_OUT(3,0)       // CHIP SELECT PIN LOW

/* Mais linhas de CS podem ser adicionadas replicando cada par de funcoes */
/* More CS Lines can be added with mode SET RESET lines */

/*===========================================================================*/
                     /*= FUNCOES BASE - BASE FUNCTIONS =*/

void SPI_DATAOUT(uint8_t size, uint32_t b){

    for(uint8_t i=size;i>0;i--){
        if(b&(1<<(i-1))){ SPI_SDO_HIGH; } else{ SPI_SDO_LOW; }
        SPI_CLK_HIGH; SPI_CLK_LOW;
    }
}

uint32_t SPI_DATAIN(uint8_t size){
    
    uint32_t DATA=0;
    for(uint8_t i=size;i>0;i--){
        if(SPI_SDI){ DATA |= (1<<(i-1)); }
        SPI_CLK_HIGH; SPI_CLK_LOW;
    }
    return DATA;
}

/*===========================================================================*/
                            /*= LOW SPEED SW SPI =*/

uint16_t SPI_SPEED=0; // 10 for +- 100Khz

void SPI_DATAOUT_L(uint8_t size, uint32_t b){

    for(uint8_t i=size;i>0;i--){
        if(b&(1<<(i-1))){ SPI_SDO_HIGH; } else{ SPI_SDO_LOW; }
        SPI_CLK_HIGH; SPI_TEMP; SPI_CLK_LOW; SPI_TEMP;
    }
}

uint32_t SPI_DATAIN_L(uint8_t size){
    
    uint32_t DATA=0;
    for(uint8_t i=size;i>0;i--){
        if(SPI_SDI){ DATA |= (1<<(i-1)); }
        SPI_CLK_HIGH; SPI_TEMP; SPI_CLK_LOW; SPI_TEMP;
    }
    return DATA;
}

/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/****************************************************************/