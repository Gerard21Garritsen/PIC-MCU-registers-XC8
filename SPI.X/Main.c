#include <xc.h>
#include <stdint.h>
#include "Config.h" //Archivo de cabecera con los FUSES
#include "SPI.h"
#define _XTAL_FREQ 4E6
#define CS LATDbits.LATD3

void main(void) {
    TRISDbits.RD3 = 0; //Pin RD3 com salida para CS
    //Configuramos el MCU como maestro con velocidad a 1 Mbps
    SPIInitMaster(SMP_Middle,CKE_Low_High,CKP_Low,0x00);
    __delay_ms(10);
    CS = 0; //Habilitamos al esclavo
    
    while(1){
        //SPIData(0xFF);
        //__delay_ms(3000);
        SPIData(0xA6);
        __delay_ms(3000);
        SPIData(0x02);
        __delay_ms(3000);
        CS = 1;
        __delay_ms(3000);
    }
}