//PIC 18F4550
#include <xc.h>
#include <stdio.h> //Libreria para la funcion printf()
#include <string.h> //Libreria para la funcion strcmp()
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "USART.h" //Libreria para manejar el USART
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    char dato[20]; //Arreglo para almacenar la cadena y controlar los leds
    const char led1[] = "Led azul"; //Arreglo para controlar el led azul
    const char led2[] = "Led verde"; //Arreglo para controlar el led verde
    const char led3[] = "Led amarillo"; //Arreglo para controlar el led amarillo
    //Configuramos los pines RC0 a RC2 como salidas
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    LATC = 0x00; //Ponemos en bajo el puerto C
    USART_Init(4000000,9600); //Inicializamos el USART a 4 MHz y 9600 baudios
    
    while(1){
        USART_Read_String(dato); //Leemos la cadena recibida
        
        //Encendemos el led correspondiente segun el dato recibido
        if(strcmp(led1,dato) == 0)
            LATCbits.LATC0 = !LATCbits.LATC0;
        if(strcmp(led2,dato) == 0)
            LATCbits.LATC1 = !LATCbits.LATC1;
        if(strcmp(led3,dato) == 0)
            LATCbits.LATC2 = !LATCbits.LATC2;
        //Cuando se recibe un dato inexistente se manda un mensaje de error
        if((strcmp(led1,dato) != 0) && (strcmp(led2,dato) != 0) && (strcmp(led3,dato) != 0))
            printf("Comando no valido\n\r");
                        
    }
}
