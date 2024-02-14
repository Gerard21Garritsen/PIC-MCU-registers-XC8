//PIC 18F4550
#include <xc.h>
#include "Config.h" //Archivo con la configuracion de los FUSES
#include "EUSART.h" //Libreria para el EUSART
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    EUSART_Init(4000000,1200); //Inicializamos el EUSART a 2400 baudios
    __delay_ms(1000);
    while(1){
        EUSART_Char('B'); //Enviamos el dato al transmisor
       __delay_ms(100);
       EUSART_Char('G');
       __delay_ms(100);
       EUSART_Char('Y');
       __delay_ms(100);
        
    }
}
