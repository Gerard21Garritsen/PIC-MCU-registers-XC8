//Archivo que contiene las funciones para el manejo del EPWM del PIC18F4550
#include "EPWM.h" //Archivo de cabecera de la libreria para el Enhanced PWM

void EPWM_Init(void){
    //Configuramos los pines P1A Y P1B como salidas del EPWM
    TRISCbits.RC2 = 0;
    TRISDbits.RD5 = 0;
    TRISDbits.RD6 = 0;
    TRISDbits.RD7 = 0;
    T2CONbits.T2CKPS = 0x01; //Seleccionamos un Prescaler de 4 TIMER2
    PR2 = 249; //Cargamos 64 para una frecuencia de 1 KHz y 4 MHz del CPU
    CCP1CONbits.P1M = 0x01; //Modo de Puente Completo
    CCP1CONbits.CCP1M = 0x0C; //P1D polaridad en alto
    //Configuramos un cyclo de trabajo del 30%
    CCPR1L = 0x4B;
    CCP1CONbits.DC1B = 0x00;
    PIR1bits.TMR2IF = 0; //Limpiamos la bandera del TIMER2
    T2CONbits.TMR2ON = 1; //Habilitamos el TIMER2
    
}
