//PIC 18F4550
#include <xc.h>
#include <stdio.h> //Libreria para el manejo de cadenas
#include <adc.h> //Libreria para el manejo del ADC
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "USART.h" //Libreria para el USART
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    float lectura; //Variable para almacenar las lecturas del ADC
    /*Configuramos el ADC como FOSC/4, 4 TAD, Justificado a la derecha, canal 0, sin interrupciones,
    voltaje de referencia del MCU y canal AN0 como entrada analogica, el resto como entradas digitales*/
    OpenADC(ADC_FOSC_4 & ADC_4_TAD & ADC_RIGHT_JUST, ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS, ADC_1ANA);
    USART_Init(4E6,9600); //Le pasamos la frecuencia del CPU y los baudios que queremos
    
    while(1){
        ConvertADC(); //Iniciamos la conversion AD
        while(BusyADC()); //Esperamos en lo que termina la conversion
        lectura = ReadADC(); //Leemos la conversion y lo guardamos en lectura
        lectura = (lectura*5.0)/1023; //Realizamos la conversion a voltaje
        //printf("El voltaje es: %.3f\n\r",lectura); //Imprimimos la lectura del ADC por puerto serie
        for(uint8_t i = 0; i < 10; i++){ //Retardo de 1 segundo
            __delay_ms(100);
        }
        
    }
}
