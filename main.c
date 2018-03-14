#include <xc.h>
#include "pragma.h"
#include "motors.h"
#include "timer.h"
#include "ui.h"
#include "etc.h"

enum {
    INIT,
    MENU,
    CLEAN,
    READY,
    WAIT,
    RUN
};

int status = INIT;
char flagStatus = 0;

void setStatus(int s){
    status = s;
    flagStatus = 1;
}

char newStatus(void){
    char x = flagStatus;
    flagStatus = 0;
    return x;
}

void loop(void){
    unsigned long now = millis();
    unsigned long next = 0;
    switch(status){
        case INIT:
            initEtc();
            initUI();
            setLEDs(0, 1, 0);
            initInterrupts();
            initTimer();
            initMotors();
            setStatus(MENU);
            break;

        case MENU:
            if(newStatus()){
                setLEDs(0, 0, 0);
                setMotors(0, 0);
            }
            
//            setLEDR(IR2);
//            setLEDY(IR3);
//            setLEDG(IR4);
            
            if(getBTN1()){
                setStatus(CLEAN);
                return;
            }
            if(getBTN2()){
                setStatus(READY);
                return;
            }
            break;
            
        case CLEAN:
            if(newStatus()){
                setMotors(1000, 1000);
                setLEDs(1, 1, 1);
            }
            if(now >= next){
                next = now + 500;
                setLEDR(!PORT_LEDR);
                setLEDY(!PORT_LEDY);
                setLEDG(!PORT_LEDG);
            }
            if(!getBTN1()) setStatus(MENU);
            break;
            
        case READY:
            if(newStatus()){
                setMotors(0, 0);
                setLEDs(0, 0, 0);
            }
            if(now >= next){
                next = now + 500;
                setLEDR(!PORT_LEDR);
            }
            if(!getBTN2()) setStatus(WAIT);
            break;
            
        case WAIT:
            if(newStatus()){
                next = now + 4900;
                setLEDs(1, 0, 0);
                setMotors(0, 0);
            }
            setLEDY(now > (next - 3000));
            if(next >= now){
                setStatus(RUN);
                return;
            }
            
        case RUN:
            //LUCHAR
            //HACER ESTADOS PARA CADA CASO EN ESTA MISMA MAQUINA
            break;
    }
}

void main(void){
    while(1) loop();
}

void interrupt ISR(void){
    if(timerInterrupt()) return;
}