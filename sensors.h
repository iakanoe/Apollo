#ifndef SENSORS_H
#define	SENSORS_H

void initSensors(void);
char getCNYs(void);
char getCNY(char n);
void switchIR(char n);
char getIRs(void);
char getIR(char n);

enum {
    NOIR,
    IR_L,
    IR_CL,
    IR_C,
    IR_CR,
    IR_R
};

#endif