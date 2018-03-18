#include <xc.h>
#include "sensors.h"

#define TRIS_IR1 TRISCbits.RC0
#define TRIS_IR2 TRISAbits.RA5
#define TRIS_IR3 TRISBbits.RB5
//#define TRIS_IR4 TRISCbits.RC5
//#define TRIS_IR5 TRISCbits.RC4
#define TRIS_IR_SWITCH TRISBbits.RB2
#define TRIS_CNY1 TRISBbits.RB4
#define TRIS_CNY2 TRISBbits.RB3

#define PORT_IR1 PORTCbits.RC0
#define PORT_IR2 PORTAbits.RA5
#define PORT_IR3 PORTBbits.RB5
#define PORT_IR4 PORTCbits.RC5
#define PORT_IR5 PORTCbits.RC4
#define PORT_IR_SWITCH LATBbits.LB2
#define PORT_CNY1 PORTBbits.RB4
#define PORT_CNY2 PORTBbits.RB3

void initSensors(void){
    TRIS_IR1 = 1;
    TRIS_IR2 = 1;
    TRIS_IR3 = 1;
//    TRIS_IR4 = 1;
//    TRIS_IR5 = 1;
    TRIS_IR_SWITCH = 0;
    TRIS_CNY1 = 1;
    TRIS_CNY2 = 1;
    PORT_IR_SWITCH = 0;
}

char getCNYs(void){
    return PORT_CNY1 || PORT_CNY2;
}

char getCNY(char n){
    if(n == 1) return PORT_CNY1;
    if(n == 2) return PORT_CNY2;
    return 0;
}

void switchIR(char n){
    PORT_IR_SWITCH = n != 0;
}

char getIRs(void){
    return PORT_IR_SWITCH && (PORT_IR1 || PORT_IR2 || PORT_IR3 || PORT_IR4 || PORT_IR5);
}

char getIR(char n){
    if(!PORT_IR_SWITCH) return 0;
    if(n == 1) return PORT_IR1;
    if(n == 2) return PORT_IR2;
    if(n == 3) return PORT_IR3;
    if(n == 4) return PORT_IR4;
    if(n == 5) return PORT_IR5;
    return 0;
}
