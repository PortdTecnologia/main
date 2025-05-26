/*****************************************************************************/
/**                         MATRICIAL KEYBOARD 4x4                          **/
/** Created: 26/05/2025  V1.0                      IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

/* HARDWARE MAP - MAPEAMENTO DE HARDWARE */
#define KLINE1_SET        PORTC_OUT(0,1)
#define KLINE1_RESET      PORTC_OUT(0,0)
#define KLINE2_SET        PORTC_OUT(1,1)
#define KLINE2_RESET      PORTC_OUT(1,0)
#define KLINE3_SET        PORTC_OUT(2,1)
#define KLINE3_RESET      PORTC_OUT(2,0)
#define KLINE4_SET        PORTC_OUT(3,1)
#define KLINE4_RESET      PORTC_OUT(3,0)
#define KCOL1             PC4
#define KCOL2             PC5
#define KCOL3             PC6
#define KCOL4             PC7
#define KTEMP             Delay_Ms(1)

/*  FRIENDLY CALL - LEITURA AMIG?VEL  */
#define KEY               (KeyScan())       //if(KEY==1){ EXECUTE }
#define KEY_0             (KeyScan())==0    //if(KEY1)  { EXECUTE }
#define KEY_1             (KeyScan())==1
#define KEY_2             (KeyScan())==2
#define KEY_3             (KeyScan())==3
#define KEY_4             (KeyScan())==4
#define KEY_5             (KeyScan())==5
#define KEY_6             (KeyScan())==6
#define KEY_7             (KeyScan())==7
#define KEY_8             (KeyScan())==8
#define KEY_9             (KeyScan())==9
#define KEY_A             (KeyScan())=='A'
#define KEY_B             (KeyScan())=='B'
#define KEY_C             (KeyScan())=='C'
#define KEY_D             (KeyScan())=='D'
#define KEY_E1            (KeyScan())=='*'
#define KEY_E2            (KeyScan())=='#'


uint8_t KeyScan(){

    uint8_t k=255;

    KLINE1_SET; KTEMP;
    if(KCOL1){ k=1; }
    if(KCOL2){ k=2; }
    if(KCOL3){ k=3; }
    if(KCOL4){ k='A'; }
    KLINE1_RESET;
    KLINE2_SET; KTEMP;
    if(KCOL1){ k=4; }
    if(KCOL2){ k=5; }
    if(KCOL3){ k=6; }
    if(KCOL4){ k='B'; }
    KLINE2_RESET;
    KLINE3_SET; KTEMP;
    if(KCOL1){ k=7; }
    if(KCOL2){ k=8; }
    if(KCOL3){ k=9; }
    if(KCOL4){ k='C'; }
    KLINE3_RESET;
    KLINE4_SET; KTEMP;
    if(KCOL1){ k='*'; }
    if(KCOL2){ k=0; }
    if(KCOL3){ k='#'; }
    if(KCOL4){ k='D'; }
    KLINE4_RESET;

    return k;
}


/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/**          https://github.com/PortdTecnologia                **/
/****************************************************************/