#include <xc.h>
#include "pragma.h"
#include "motors.h"
#include "timer.h"
#include "ui.h"
#include "etc.h"
#include "sensors.h"

#define ATTACK_SPEED 1000
#define TURN_SPEED 1000
#define BACK_SPEED 1000
#define BACK_TIME 1000
#define WAIT_TIME 4950

enum {
    INIT,
    MENU,
    CLEAN,
    READY,
    WAIT,
    RUN,
    ATTACK,
    BACK,
    RIGHT,
    LEFT,
    OPEN_RIGHT,
    OPEN_LEFT,
    CLOSED_RIGHT,
    CLOSED_LEFT
};

int status = INIT;
char flagStatus = 0;
int targetDirection;

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
            initSensors();
            switchIR(0);
            initInterrupts();
            initTimer();
            initMotors();
            setStatus(MENU);
            return;

        case MENU:
            if(newStatus()){
                setLEDs(0, 0, 0);
                setMotors(0, 0);
            }
            
//            switchIR(1);
//            setLEDR(IR2);
//            setLEDY(IR3);
//            setLEDG(IR4);
//            switchIR(0);
            
            if(getBTN1()){
                setStatus(CLEAN);
                return;
            }
            if(getBTN2()){
                while(getBTN2()) continue;
                setStatus(READY);
                return;
            }
            return;
            
        case CLEAN:
            if(newStatus()){
                setMotors(1000, 1000);
                setLEDs(1, 1, 1);
            }
            if(now >= next){
                next = now + 500;
                setLEDR(!getLEDR());
                setLEDY(!getLEDY());
                setLEDG(!getLEDG());
            }
            if(!getBTN1()) setStatus(MENU);
            return;
            
        case READY:
            if(newStatus()){
                setMotors(0, 0);
                setLEDs(1, 0, 0);
            }
            if(now >= next){
                next = now + 500;
                setLEDR(!getLEDR());
            }
            if(getBTN1()){
                setLEDs(1, 1, 1);
                while(getBTN1()) continue;
                targetDirection = LEFT;
                setStatus(WAIT);
            }
            if(getBTN2()){
                setLEDs(1, 1, 1);
                while(getBTN2()) continue;
                targetDirection = RIGHT;
                setStatus(WAIT);
            }
            return;
            
        case WAIT:
            if(newStatus()){
                next = now + WAIT_TIME;
                setLEDs(1, 0, 0);
                setMotors(0, 0);
            }
            setLEDY(now > next - WAIT_TIME / 2);
            if(next >= now){
                setStatus(RUN);
                return;
            }
            return;
            
        case RUN:
            switchIR(1);
            if(getBTNs()){
                setStatus(MENU);
                return;
            }
            if(getCNYs()){
                setStatus(BACK);
                return;
            }
            if(getIR(IR_C)){
                if(getIR(IR_CL)){
                    setStatus(CLOSED_LEFT);
                    targetDirection = LEFT;
                    return;
                }
                if(getIR(IR_CR)){
                    setStatus(CLOSED_RIGHT);
                    targetDirection = RIGHT;
                    return;
                }
                setStatus(ATTACK);
                return;
            }
            if(getIR(IR_CL)){
                setStatus(OPEN_LEFT);
                targetDirection = LEFT;
                return;
            }
            if(getIR(IR_CR)){
                setStatus(OPEN_RIGHT);
                targetDirection = RIGHT;
                return;
            }
            if(getIR(IR_R)){
                setStatus(RIGHT);
                targetDirection = RIGHT;
                return;
            }
            if(getIR(IR_L)){
                setStatus(LEFT);
                targetDirection = LEFT;
                return;
            }
            setStatus(targetDirection);
            switchIR(0);
            return;
            
        case ATTACK:
            setBothMotors(ATTACK_SPEED);
            setStatus(RUN);
            return;
            
        case BACK:
            if(newStatus()){
                setBothMotors(BACK_SPEED);
                next = now + BACK_TIME;
            }
            if(now >= next || getIRs()) setStatus(RUN);
            return;
            
        case RIGHT:
            setMotors(TURN_SPEED, -TURN_SPEED);
            setStatus(RUN);
            return;
            
        case LEFT:
            setMotors(-TURN_SPEED, TURN_SPEED);
            setStatus(RUN);
            return;
            
        case OPEN_RIGHT:
            setMotors(TURN_SPEED, 0);
            setStatus(RUN);
            return;
            
        case OPEN_LEFT:
            setMotors(0, TURN_SPEED);
            setStatus(RUN);
            return;
            
        case CLOSED_RIGHT:
            setMotors(TURN_SPEED, TURN_SPEED / 2);
            setStatus(RUN);
            return;
            
        case CLOSED_LEFT:
            setMotors(TURN_SPEED / 2, TURN_SPEED);
            setStatus(RUN);
            return;
    }
}

void main(void){
    while(1) loop();
}

void interrupt ISR(void){
    if(timerInterrupt()) return;
}