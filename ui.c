#include <xc.h>
#include "ui.h"

#define TRIS_LEDR TRISAbits.RA4
#define TRIS_LEDY TRISAbits.RA3
#define TRIS_LEDG TRISAbits.RA2

#define TRIS_BTN1 TRISAbits.RA1
#define TRIS_BTN2 TRISAbits.RA0

#define PORT_LEDR LATAbits.LATA4
#define PORT_LEDY LATAbits.LATA3
#define PORT_LEDG LATAbits.LATA2

#define PORT_BTN1 PORTAbits.RA1
#define PORT_BTN2 PORTAbits.RA0

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

char getBTN1(void){
    return !PORT_BTN1;
}

char getBTN2(void){
    return !PORT_BTN2;
}

char getBTNs(void){
    return getBTN1() || getBTN2();
}

void setLEDR(char v){
    PORT_LEDR = v;
}

void setLEDY(char v){
    PORT_LEDY = v;
}

void setLEDG(char v){
    PORT_LEDG = v;
}

char getLEDR(void){
    return PORT_LEDR;
}

char getLEDY(void){
    return PORT_LEDY;
}

char getLEDG(void){
    return PORT_LEDG;
}
