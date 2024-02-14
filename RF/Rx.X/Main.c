//PIC 18F4550
#include <xc.h>
#include "Config.h" //Archivo con la configuracion de los FUSES
#include "EUSART.h" //Libreria para el EUSART
#define _XTAL_FREQ 4E6 //Frecuencia CPU

void main(void) {
    char Data; //Variable para almacenar el dato recibido
    //Configuramos los pines RC0, RC1 y RC2 como salidas
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    LATC = 0x00; //Ponemos en LOW el puerto C
    EUSART_Init(4000000,1200); //Inicializamos el EUSART a 2400 baudios
    
    while(1){
        Data = EUSART_Read(); //Leemos el dato recibido del transmisor
        //Acciones a realizar dependiendo el dato recibido
        if(Data == 'B') //Led Azul
            LATCbits.LATC0 = !LATCbits.LATC0;
        if(Data == 'G') //Led Verde
            LATCbits.LATC1 = !LATCbits.LATC1;
        if(Data == 'Y') //Led Amarillo
            LATCbits.LATC2 = !LATCbits.LATC2;
        
    }
}
