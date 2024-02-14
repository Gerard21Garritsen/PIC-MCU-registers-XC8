//PIC 18F4550
#include <xc.h>
#include <stdio.h> //Libreria para usar la funcion printf()
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "USART.h" //Libreria para el manejo del EUSART
#include "EEPROM.h" //Libreria para el manejo del EEPROM Interno
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    int dato = 25768; //Varible entera para almacenar en la EEPROM
    float dec = 3.141592; //Variable float para almacenar en la EEPROM
    int dato1; //Variable para almacenar el valor entero leido de la EEPROM
    float dato2; //Variable para almacenar el valor float lido de la EEPROM
    USART_Init(4000000,9600); //Inicializamos el UART a 4 MHz y 9600 baudios
    //Almacenamos el contenido de la variable dato en la EEPROM
    EEPROM_Write_Integer(0x00,dato); //Almacenamos el dato a partir de la direccion 0
    EEPROM_Write_Float(0x02,dec); //Almacenamos el dato a partir de la direccion 2
    dato1 = EEPROM_Read_Integer(0x00); //Leemos el dato almacenado desde la direccion 0
    dato2 = EEPROM_Read_Float(0x02); //Leemos el dato almacendo desde la direccion 2
    
    
    while(1){
        //Enviamos los datos por el puerto serie para mostrarlos en pantalla del terminal
        printf("El dato entero almacenado es: %d\n\r",dato1);
        __delay_ms(500);
        printf("El dato float almacenado es: %f\n\r",dato2);
        __delay_ms(500);
            
    }
}