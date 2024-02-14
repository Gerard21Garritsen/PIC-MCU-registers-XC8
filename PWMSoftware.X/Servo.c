#include <stdint.h> //Libreria para tipo de datos en bits
#include "Servo.h" //Header de las funciones para el manejo de servomotores
#define PORT LATDbits.LATD0 //Directiva para el manejo de pines

uint8_t count = 0; //Variable para el incremento del PWM
uint8_t Duty = 1; //Variable para colocar el ciclo de trabajo deseado

void TIMER1_Init(void){
    T1CONbits.RD16 = 1; //Lectura/escritura de 16 bits
    T1CONbits.T1CKPS = 0x03; //Prescaler de 8
    INTCONbits.GIE = 1; //Habilitamos interrupciones globales
    INTCONbits.PEIE = 1; //Habilitamos interrupciones perifericas
    PIE1bits.TMR1IE = 1; //Habilitamos interrupciones por TIMER1
    PIR1bits.TMR1IF = 0; //Limpiamos el flag del TIMER1
    TMR1 = 65510; //Cargamos el TIMER1 para una temporizacion de 200us
    T1CONbits.TMR1ON = 1; //Encendemos el TIMER1
    
}

void Servo_Duty(unsigned int angle){
    if(angle <= 30) //Si el angulo enviado es menor o igual a 30 grados
        Duty = 1; //Ciclo de trabajo en 1 ms
    else
        Duty = angle*9/180; //Conversion de grados a ms del periodo*/
}

void __interrupt()TIMER1_Interrupt(void){
    if(PIR1bits.TMR1IF){
        if(count <= 100)
            count++;
        else
            count = 0;
        if(count <= Duty)
            PORT = 1;
        else
            PORT = 0;
        PIR1bits.TMR1IF = 0; //Limpiamos el flag
        TMR1 = 65513; //Recargamos TIMER1 con 3 mas para tener un periodo de 20 ms mas aproximado
    }
}
