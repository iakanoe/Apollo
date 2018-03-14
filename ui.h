#ifndef UI_H
#define	UI_H

#define PORT_LEDR LATAbits.LATA4
#define PORT_LEDY LATAbits.LATA3
#define PORT_LEDG LATAbits.LATA2

#define PORT_BTN1 PORTAbits.RA1
#define PORT_BTN2 PORTAbits.RA0

#define setLEDR(v) PORT_LEDR = (v)
#define setLEDY(v) PORT_LEDY = (v)
#define setLEDG(v) PORT_LEDG = (v)

#define getBTN1() (!(PORT_BTN1))
#define getBTN2() (!(PORT_BTN2))

void initUI(void);
void setLEDs(char r, char y, char g);

#endif
