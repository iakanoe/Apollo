#include <xc.h>
#include "etc.h"

void initInterrupts(void){
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void initEtc(void){
    ADCON1bits.PCFG = 0xF;
}