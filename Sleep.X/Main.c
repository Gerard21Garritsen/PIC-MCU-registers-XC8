//PIC 18F4550
#include <xc.h>
#include <stdbool.h> //Libreria para usar variables booleanas
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#define _XTAL_FREQ 4E6 //Frecuencia del CPU 4 MHz

bool state = 0; //Variable para entrar o salir del modo SLEEP

void __interrupt() sleep(void); //Funcion de interrupcion

void main(void) {
    TRISB = 0xFF; //Puerto B como entrada
    TRISC =0xFE; //Pin RC0 como salida
    TRISD = 0xFF; //Puerto B como entrada
    INTCONbits.GIE = 1; //Habilitamos las interrupciones globales
    INTCONbits.PEIE = 0; //No habilitamos las PEIE por que no se necesitan para interrupciones por RB0
    INTCON2bits.INTEDG0 = 0; //La interrupcion se genera por flanco de bajada
    INTCONbits.INT0IE = 1; //Habilitamos la interrupcion por INT0
    INTCONbits.INT0IF = 0; //Limpiamos la flag del INT0
    CMCONbits.CM = 0x07; //Apagamos los comparadores
    T0CONbits.TMR0ON = 0;
    INTCON2bits.RBPU = 1; //Deshabilitamos las PullUp resistors
    
    while(1){
        //Rutina del blink
        LATCbits.LATC0 = !LATCbits.LATC0;
        __delay_ms(100);
        if(state == 1){ //Si se genera la interrupcion se entra o sale del modo SLEEP
            SLEEP(); //Sentencia para entrar en el modo SLEEP
        }
        
    }
}

void __interrupt() sleep(void){
    if(INTCONbits.INT0IF == 1){ //Si se genera la interrupcion
        state = !state; //Se cambia el estado de la variable
        INTCONbits.INT0IF = 0; //Limpia la bandera
    }
}