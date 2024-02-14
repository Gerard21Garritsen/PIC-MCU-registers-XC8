//PIC 18F4550
#include <xc.h>
#include <stdint.h> //Libreria para utilizar tipos de datos de bits
#include <adc.h> //Libreria adc de MPLAB X
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#define _XTAL_FREQ 4E6 //Frecuencia del CPU 4 MHz

void main(void) {
    TRISD = 0xE0; //Configuamos los pines RD0 a RD5 como salidas y el resto entradas
    int lect[2]; //Arreglo para almacenar la lectura de cada canal
    //Configuracin del ADC FOSC/4, 4 TAD, justificado a la derecha, canal 0, sin interrupciones
    //voltaje de referencia del PIC
    OpenADC(ADC_FOSC_4 & ADC_4_TAD & ADC_RIGHT_JUST,ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS,ADC_2ANA);
    
    while(1){
        for(uint8_t i = 0; i < 2; i++){
            ADCON0bits.CHS = i; //Cambiamos de canal
            ConvertADC();
            while(BusyADC());
            lect[i] = ReadADC();
        }
        
        //Eje X
        if(lect[0] >= 0 && lect[0] < 480){
            LATDbits.LATD0 = 1;
        }
        else{
            LATDbits.LATD0 = 0;
        }
        if(lect[0] >= 530 && lect[0] <= 1023){
            LATDbits.LATD1 = 1;
        }
        else{
            LATDbits.LATD1 = 0;
        }
        //Eje Y
        if(lect[1] >= 0 && lect[1] < 480){
            LATDbits.LATD2 = 1;
        }
        else{
            LATDbits.LATD2 = 0;
        }
        if(lect[1] >= 530 && lect[1] <= 1023){
            LATDbits.LATD3 = 1;
        }
        else{
            LATDbits.LATD3 = 0;
        }
        //Boton
        if(PORTAbits.RA2 == 1){
            LATDbits.LATD4 = 0;
        }
        else{
            LATDbits.LATD4 = 1;
        }
        
    }
}
