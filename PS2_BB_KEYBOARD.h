/*****************************************************************************/
/**                       PS/2 BITBANG KEYBOARD V1.0                        **/
/** Created: 08/10/2025                            IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/
//OBS: As entradas de DATA e CLOCK devem ser input pull-up
//OBS: The DATA and CLOCK pins needs to be input pull-up

/* Registradores de leitura - Read registers */
#define PS2_DATA_READ      PC0
#define PS2_CLK_READ       PC1
#define PS2_KDELAY         Delay_Us(1)

uint8_t PS2_KEYBOARD_READ(){
    uint8_t ret=0;
    uint8_t timeout=0;

    timeout=0; 
    while(!PS2_CLK_READ && timeout <64){timeout++; PS2_KDELAY;}    // START BIT
    while(PS2_CLK_READ && timeout <128){timeout++; PS2_KDELAY;}

    for(uint8_t i=0; i<8;i++){
        if(PS2_DATA_READ){ ret |=(1<<i); }                         // BITS 0-7 RX
        timeout=0;
        while(!PS2_CLK_READ && timeout <64){timeout++; PS2_KDELAY;} 
        while(PS2_CLK_READ && timeout <128){timeout++; PS2_KDELAY;}
    }

    timeout=0;
    while(!PS2_CLK_READ && timeout <64){timeout++; PS2_KDELAY;}    // SKIP PARITY
    while(PS2_CLK_READ && timeout <128){timeout++; PS2_KDELAY;}    // IGNORAR PARIDADE

    timeout=0;
    while(!PS2_CLK_READ && timeout <64){timeout++; PS2_KDELAY;}    // stop bit

    return ret;
}

/* Tabela de conversao */

const char ps2_ascii[128] = {
    [0x1C] = 'a',
    [0x32] = 'b',
    [0x21] = 'c',
    [0x23] = 'd',
    [0x24] = 'e',
    [0x2B] = 'f',
    [0x34] = 'g',
    [0x33] = 'h',
    [0x43] = 'i',
    [0x3B] = 'j',
    [0x42] = 'k',
    [0x4B] = 'l',
    [0x3A] = 'm',
    [0x31] = 'n',
    [0x44] = 'o',
    [0x4D] = 'p',
    [0x15] = 'q',
    [0x2D] = 'r',
    [0x1B] = 's',
    [0x2C] = 't',
    [0x3C] = 'u',
    [0x2A] = 'v',
    [0x1D] = 'w',
    [0x22] = 'x',
    [0x35] = 'y',
    [0x1A] = 'z',

    [0x45] = '0',
    [0x16] = '1',
    [0x1E] = '2',
    [0x26] = '3',
    [0x25] = '4',
    [0x2E] = '5',
    [0x36] = '6',
    [0x3D] = '7',
    [0x3E] = '8',
    [0x46] = '9',

    [0x0E] = '`',
    [0x4E] = '-',
    [0x55] = '=',
    [0x5D] = '\\',
    [0x29] = ' ',
    [0x54] = '[',
    [0x5B] = ']',
    [0x4C] = ';',
    [0x52] = '\'',
    [0x41] = ',',
    [0x49] = '.',
    [0x4A] = '/',
    [0x5A] = '\n',
    [0x66] = '\b',
    [0x0D] = '\t'
};

/*****  Como usar leitura - how to use read ******/
// if(!PS2_CLK_READ ou/or interrupcao/interrup){
//    uint8_t data = PS2_KEYBOARD_READ();
//    usar data; - use data;}
/*************************************************/

/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/****************************************************************/