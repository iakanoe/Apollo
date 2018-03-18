#include <xc.h>
#include "motors.h"

#define TRIS_MOT_R1 TRISBbits.TRISB1
#define TRIS_MOT_R2 TRISBbits.TRISB0
#define TRIS_MOT_L1 TRISCbits.TRISC6
#define TRIS_MOT_L2 TRISCbits.TRISC7

#define LAT_MOT_R1 LATBbits.LATB1
#define LAT_MOT_R2 LATBbits.LATB0
#define LAT_MOT_L1 LATCbits.LATC6
#define LAT_MOT_L2 LATCbits.LATC7

#define TRIS_MOTL_PWM TRISCbits.TRISC1
#define TRIS_MOTR_PWM TRISCbits.TRISC2

void initMotors(void){
    TRIS_MOT_R1 = 0;
    TRIS_MOT_R2 = 0;
    TRIS_MOT_L1 = 0;
    TRIS_MOT_L2 = 0;
    
    LAT_MOT_R1 = 0;
    LAT_MOT_R2 = 0;
    LAT_MOT_L1 = 0;
    LAT_MOT_L2 = 0;
    
    TRIS_MOTL_PWM = 0;
    TRIS_MOTR_PWM = 0;
    
    // Bajar frecuencia si no funciona bien
    // 149 = 20kHz // 199 = 15kHz // 249 = 12kHz (classic)
    PR2 = 149;
    
    CCPR1L = 0;
    CCPR2L = 0;
    CCP1CONbits.DC1B = 0;
    CCP2CONbits.DC2B = 0;
    T2CON = 0x05;
    CCP1CONbits.CCP1M = 0xF;
    CCP2CONbits.CCP2M = 0xF;
}

void setMotors(signed int left, signed int right){
    setLeftMotor(left);
    setRightMotor(right);
}

void setBothMotors(signed int speed){
    setLeftMotor(speed);
    setRightMotor(speed);
}

void setLeftMotor(signed int speed){
    LAT_MOT_L1 = speed >= 0;
    LAT_MOT_L2 = speed <= 0;
    if(speed < 0) speed = -speed;
    if(speed > 1000 || speed == 0) speed = 1000; // Para trabar
    speed = speed * 1024 / 1000;
    CCP2CONbits.DC2B = speed & 3;
    CCPR2L = speed >> 2;
}

void setRightMotor(signed int speed){
    LAT_MOT_R1 = speed >= 0;
    LAT_MOT_R2 = speed <= 0;
    if(speed < 0) speed = -speed;
    if(speed > 1000 || speed == 0) speed = 1000; // Para trabar
    speed = speed * 1024 / 1000;
    CCP1CONbits.DC1B = speed & 3;
    CCPR1L = speed >> 2;
}
