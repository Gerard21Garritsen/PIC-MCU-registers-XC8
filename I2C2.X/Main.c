//PIC 18F4550
#include <xc.h>
#include <stdio.h> //Libreria para el manejo de cadenas
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "24LC256.h" //Libreria para la memoria EEPROM 24LC256
#include "EUSART.h" //Libreria para la comuncacion serial
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    char Data[13]; //Arreglo en el que se guardaran los caracteres
    EUSART_Init(4E6,9600); //Inicializamos el EUSART con 4 MHz y 9600 baudios
    I2C_Init(MASTER,SLEW_ON);
    //writeData(0x000A,0x70);
    readsData(0x0000,0x000A,Data); //Leemos los datos continuos de memoria
    
    while(1){
        EUSART_String(Data); //Los mandamos por puerto serie
        for(uint8_t i = 0; i < 10; i++){
            __delay_ms(100);
        }
        
    }
}
