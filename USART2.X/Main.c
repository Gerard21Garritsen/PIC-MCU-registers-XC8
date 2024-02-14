//PIC18F4550
#include <xc.h>
#include "Config.h" //Archivo con la configuracion de los FUSES
#include <stdio.h> //Libreria para la funcion printf()
#include <string.h> //Libreria para la funcion strcmp()
#include "USART.h" //Libreria para el USART
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4MHz

void main(void) {
    unsigned char cadenarecibida[20]; //Arreglo donde se guardara la cadena recibida maximo 20 caracteres
    const char contrasena[] = "PIC18F4550"; //Arreglo con la contraseña PIC18F4550
    USART_Init(4E6,9600); //Inicializamos el USART a 9600 baudios
    printf("Introduce la contrasena: \n\r"); //Imprimimos el mensaje introducir la contraseña
    USART_Read_String(cadenarecibida); //Leemos la cadena enviada desde la PC
    while(strcmp(contrasena,cadenarecibida) != 0){ //Bucle para reingresar la contraseña
        printf("Contrasena erronea\n\r");
        USART_Read_String(cadenarecibida);
    }
    printf("BIENVENIDO"); //Si la contraseña es correcta se imprimira el mensaje
    
    while(1){
        
    }
}
