#include <xc.h>
#include <stdint.h>
#include "Config.h" //Archivo de cabecera con los FUSES
#include "SPI_SSD1306.h" //Libreria para OLED SSD1306 por SPI
#define _XTAL_FREQ 4E6 //Frecuencia del CPU

void main(void) {
    TRISDbits.RD7 = 0; //Pin DC 
    TRISDbits.RD6 = 0; //Pin Reset
    //Configuramos el MCU como maestro con velocidad a 1 Mbps
    SPIInitMaster(SMP_Middle,CKE_Low_High,CKP_High,0x00);
    __delay_ms(10);
    displayInit();
    displayClear();
    displayString(0,4,"PIC 18F4550");
    __delay_ms(2000);
    displayClear();
    displayBitmap();
    for(uint8_t i = 0; i < 10; i++){
        displayInvert(BLACK);
        __delay_ms(1000);
        displayInvert(WHITE);
        __delay_ms(1000);
    }
    
    while(1){
        
    }
}