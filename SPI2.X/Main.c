#include <xc.h>
#include <stdint.h>
#include "Config.h" //Archivo de cabecera con los FUSES
#include "SPI.h"
#define _XTAL_FREQ 4E6

void main(void) {
    char Data = 0;
    TRISDbits.RD7 = 0;
    TRISDbits.RD6 = 0;
    //Configuramos el MCU como maestro con velocidad a 1 Mbps
    SPIInitSlave(0x04);
    LATD = 0x00;
    __delay_ms(10);
    
    while(1){
        Data = SPIRead();
        if(Data == 0xA6)
            LATDbits.LATD7 = 1;
        else{
            LATDbits.LATD7 = 0;
        }
        if(Data == 0x02)
            LATDbits.LATD6 = 1;
        else{
            LATDbits.LATD6 = 0;
        }
    }
}