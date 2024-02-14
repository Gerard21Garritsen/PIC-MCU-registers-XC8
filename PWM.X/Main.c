//PIC 18F4550
#include <xc.h>
#include <stdint.h> //Libreria para manejar tipos de dato en bits
#include <pwm.h> //Libreria para el PWM de MPLAB X
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void TIMER2Init(void); //Funcion que contiene la configuracion del TIMER2

void main(void) {
    TIMER2Init(); //Llamamos a las configuraciones del TIMER2
    OpenPWM1(249); //Configuramos la frecuencia del PWM a 1 KHz (PR2 = 249)
    SetDCPWM1(0); //Configuramos el ciclo de trabajo al 0%
    
    while(1){
        for(uint16_t i = 1; i < 1000; i++){ //Aumentamos el Duty Cycle de 0% a 100%
            SetDCPWM1(i);
            __delay_ms(10);
        }
        for(uint16_t i = 999; i >= 1; i--){ //Disminuimos el Duty Cycle de 100% a 0%
            SetDCPWM1(i);
            __delay_ms(10);
        }
        
    }
}

void TIMER2Init(void){
    TRISCbits.TRISC2 = 0; //Pin RC2 como salida para PWM
    T2CONbits.T2CKPS = 0x01; //Prescaler de 4
    T2CONbits.TMR2ON = 1; //Habilitamos el TIMER 2
}