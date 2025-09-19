/*****************************************************************************/
/**                             TONE GENERATOR                              **/
/** Created: 17/09/2025  V1.0                      IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                PORTD Tecnologia         **/
/*****************************************************************************/

// Pre-requisito: Funcao de delay em Us - Requiriment: Delay Us function

#define TONEPIN_HIGH      PORTC_OUT(0,1)
#define TONEPIN_LOW       PORTC_OUT(0,0)
#define TONEDELAY_US      Delay_Us        // Nao abrir parenteses - Not open ()


uint16_t notes[127] = {
    15290, 14430, 13620, 12856, 12135, 11454, 10810, 10204, 9632, 9090, 8580, 8098,  // Octave 1
    7645, 7215, 6810, 6428, 6068, 5727, 5405, 5102, 4816, 4545, 4290, 4049,          // Octave 2
    3823, 3608, 3405, 3214, 3034, 2864, 2703, 2551, 2408, 2273, 2145, 2025,          // Octave 3
    1911, 1804, 1703, 1607, 1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012,          // Octave 4
    956, 902, 851, 804, 758, 716, 676, 638, 602, 568, 536, 506,                      // Octave 5
    478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253,                      // Octave 6
    239, 226, 213, 201, 190, 179, 169, 159, 150, 142, 134, 126,                      // Octave 7
    119, 113, 106, 100, 95, 89, 84, 80, 75, 71, 67, 63,                              // Octave 8
    60, 56, 53, 50, 47, 45, 42, 40, 38, 35, 33, 32,                                  // Octave 9
    30,28,27,25,24,22,21,20,19,18,17,16                                              // Octave 10
};


// Dados do MIDI ou das notas - MIDI or notes data
static uint8_t music[1] = {};


uint8_t oitava = 1;    // Ajuste de oitava - Octave adjust

// tonetmr: Para ser usado dentro de um loop de timer - for use inside a timer loop
void tonettmr(uint8_t n){
        TONEPIN_HIGH; Delay_Us(notes[n]*oitava); 
        TONEPIN_LOW;  Delay_Us(notes[n]*oitava);
}


// tonegen: Para ser usada sem loop de timer - For use without timer loop
void tonegen(uint8_t note, uint16_t duracao){
    uint32_t cycle=0;

    while(( ( (notes[note]*oitava) * (cycle*2) ) / 1000) <= duracao){
        TONEPIN_HIGH; Delay_Us(notes[note]*oitava);
        TONEPIN_LOW;  Delay_Us(notes[note]*oitava); 
        cycle++;
    }
}


void MidiPlay(){

	uint8_t midich =0;
    uint16_t i=0;

    while(i<=(sizeof(music))-1){

        if(music[i]==0x90 + midich){
            i++;
            tonegen(music[i],300);
        }
        i++;
    }
}

void Tone_Play(){

    uint16_t i=0;

    while(i<=(sizeof(music))-1){

        tonegen(music[i],140);
        i++;
    }
}


/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@PORTDTech               **/
/**              https://x.com/gustavo_portd                   **/
/****************************************************************/