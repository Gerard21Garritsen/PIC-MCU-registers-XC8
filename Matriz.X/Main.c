#include <xc.h>
#include "Config.h" //Archivo de cabecera que contiene la configuracion de los FUSES
#include "MAX7219.h" //Libreria para el manejo de matrices con el MAX7219
#define _XTAL_FREQ 4000000

void main(void) {
    //Se inicializa el SPI con una velocidad de 1 Mbps, CKE de bajo a alto, CKP alto y
    //SMP al final, es importante para el MAX7219 tener CKP en alto
    SPI_Init(0x00, CKE_LOW_HIGH, CKP_HIGH, SMP_DATA_MIDDLE);
    MAX7219_Init(4); //Inicializamos las configuraciones del MAX7219 para el manejo de matrices
    clearMatrix(4);
    
    while(1){
    charMatrix(1,'H');
    __delay_ms(1000);
    charMatrix(2,'O');
    __delay_ms(1000);
    charMatrix(3,'L');
    __delay_ms(1000);
    charMatrix(4,'A');
    __delay_ms(1000);
    clearMatrix(4);
    charMatrix(1,'A');
    __delay_ms(1000);
    charMatrix(2,'L');
    __delay_ms(1000);
    charMatrix(3,'M');
    __delay_ms(1000);
    charMatrix(4,'A');
    __delay_ms(1000);
    clearMatrix(4);
    
    }
}
        