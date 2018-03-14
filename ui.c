#include <xc.h>
#include "ui.h"

#define TRIS_LEDR TRISAbits.RA4
#define TRIS_LEDY TRISAbits.RA3
#define TRIS_LEDG TRISAbits.RA2

#define TRIS_BTN1 TRISAbits.RA1
#define TRIS_BTN2 TRISAbits.RA0

void initUI(void){
    TRIS_LEDR = 0;
    PORT_LEDR = 0;
    
    TRIS_LEDY = 0;
    PORT_LEDY = 0;
    
    TRIS_LEDG = 0;
    PORT_LEDG = 0;
    
    TRIS_BTN1 = 1;
    TRIS_BTN2 = 1;
}

void setLEDs(char r, char y, char g){
    setLEDR(r);
    setLEDY(y);
    setLEDG(g);
}
