#include <xc.h> //Libreria elemental de MPLAB
#include <stdint.h> //Libreria para tipos de datos de bits
#include "Config.h" //Archivo de la configuracion de los FUSES
#include "I2C_OLED.h" //Libreria para la OLED
#define _XTAL_FREQ 4E6 //Frecuencia del CPU a 4 MHz

void main(void) {
    OpenI2C(MASTER,SLEW_ON); //Configuramos el MCU como maestro y una velocidad de 400 kbps
    display_Init(); //Inicializamos la OLED
    __delay_ms(1);
    display_Clear(); //Limpiamos la OLED
    displayString(0,4,"PIC 18F4550");
    __delay_ms(1000);
    display_Clear();
    displayBitmap(); //Imprimimos el mapa de bits
    displayInvert(WHITE);
    __delay_ms(5000);
    displayInvert(BLACK);
    
    while(1){
        
    }
}