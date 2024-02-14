//PIC 18F4550
#include <xc.h>
#include <stdlib.h> //Libreria que contiene la funcion atoi
#include <stdio.h> //Libreria que contiene la funcion printf
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "USART.h" //Libreria para el manejo del EUSART
#include "Servo.h" //Libreria para el manejo de servomotores
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    unsigned char value[4]; //Arreglo para almacenar el angulo enviado
    unsigned int angulo; //variable entera para almacenar el angulo enviado
    TRISDbits.RD0 = 0; //Pin RD0 como salida para el PWM
    LATD = 0x00; //Ponemos en LOW el puerto D
    USART_Init(4000000,9600); //Inicializamos el USART a 4 MHz y 9600 baudios
    TIMER1_Init(); //Inicializamos el Timer1 con las configuraciones necesarias
    
    while(1){
        if(PORTDbits.RD1 == 1){ //Si se ha emparejado el bluetooth con un dispositivo
            printf("Ingresa el angulo en grados\n\r");
            USART_Read_String(value); //Leemos la cadena enviada desde el smarthphone
            angulo = atoi(value); //Convertimos la cadena a numeros enteros y almacenamos en angulo
            if(angulo > 180 || angulo < 0) //Si el angulo esta fuera del rango permitido
              printf("El angulo maximo es 180 y el minimo 0\n\r");
             else
              Servo_Duty(angulo);
        }
    
    }
}
