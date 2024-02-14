//Funciones para el manejo del motor a pasos
#include <pic18f4550.h> //Libreria del PIC 18F4550
#include "Motor_Pasos.h" //Archivo de cabecera de las definiciones
#define _XTAL_FREQ 4E6 //Frecuencia CPU
#define Out TRISBbits.RB0 //Con la directiva Out configuramos el pin RB0
#define step LATBbits.LATB0 //Con la directiva Pin controlamos el estado del pin RB0

float period = 0; //Variable para el periodo de la señal
unsigned int valor = 0; //Variable para asignar el resultado al registro TMR3

void TIMER3_Init(void){
    Out = 0; //Configuramos el pin RB0 como salida
    LATB = 0x00; //Ponemos en LOW al puerto B
    T3CONbits.RD16 = 1; //Escritura/Lectura de 16 bits
    T3CONbits.T3CKPS = 0x03; //Prescaler de 8
    PIR2bits.TMR3IF = 0; //Ponemos a cero el flag del TIMER3
    T3CONbits.TMR3ON = 0; //Deshabilitamos el TIMER3
    
}

void Motor(float periodo,unsigned int numero_de_pasos){ //El periodo se pone en ms y no debe exceder 800 ms
    unsigned int i = 0; //Variable que lleva el conteo del numero de pulsos
    
    if(periodo <= 1E-3) //Si el periodo es menor o igual a 1 milisegundo
        period = 1E-3; //Se establece el minimo periodo posible
    else
        period = periodo;
    
    valor = 65535-(period*_XTAL_FREQ/64); //Calculamos el valor del TIMER3 para el periodo
    TMR3 = valor; //Cargamos al TIMER3
    T3CONbits.TMR3ON = 1; //Habilitamos el TIMER3
    
    while(i < numero_de_pasos * 2){
        if(PIR2bits.TMR3IF == 1){
            step = !step; //Cambiamos el estado del pin step
            i++; //Incrementamos a i
            PIR2bits.TMR3IF = 0; //Limpiamos la bandera del TIMER3
            TMR3 = valor; //Recargamos el registro del TIMER3
        }
    }
    T3CONbits.TMR3ON = 0; //Deshabilitamos el TIMER3
}