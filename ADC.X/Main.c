//PIC 18F4550
#include <xc.h>
#include <stdio.h> //Libreria para usar la funcion sprintf
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "I2C_OLED.h" //Libreria para controlar la OLED
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void ADC_Init(void); //Funcion que contiene la configuracion del ADC

void main(void) {
    uint16_t lec;
    float valor; //Variable que almacena la lectura del ADC
    uint16_t res;
    unsigned char voltaje[2]; //Variable para mostrar la lectura del ADC
    I2CInit(MASTER,SLEW_ON); //Inicializamos la comunicacio I2C
    display_Init(); //Inicializamos la configuracion de la OLED
    __delay_ms(1);
    display_Clear(); //Limpiamos la OLED
    ADC_Init(); //Inicializamos la configuracion del ADC
    
    while(1){
        ADCON0bits.GO_DONE = 1; //Iniciamos la conversion
        while(ADCON0bits.GO_DONE == 1); //Esperamos miesntras termina la conversion
        lec = ADRESH<<8;
        lec = lec + ADRESL;
        valor = lec * 4.887E-3;
        res = valor * 100;
        sprintf(voltaje,"%d.%d",res/100,res%100);
        display_String(0,0,voltaje);
        
    }
}

void ADC_Init(void){
    ADCON0bits.CHS = 0x00; //Canal AN0
    ADCON1bits.PCFG = 0x05; //Todos los canales analogicos excepto AN10,AN11 y AN12 para la comunicacion I2C
    ADCON2bits.ADFM = 1; //Justificado a la derecha
    ADCON2bits.ACQT = 0x02; //4 TAD 1 TAD = 1 us
    ADCON2bits.ADCS = 0x04; //FOSC/4
    ADCON0bits.ADON = 1; //Habilitamos el ADC
    __delay_us(20); //Esperamos el tiempo de adquiscion
    
}
