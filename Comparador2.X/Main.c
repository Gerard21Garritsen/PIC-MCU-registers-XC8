//PIC 18F4550
#include <xc.h>
#include "Config.h" //Archivo que cotiene la configuracion de los FUSES
#include "Comparator.h" //Libreria para el manejo del Modulo Comparador
#define _XTAL_FREQ 4E6 //Frecuencia del CPU4 MHz

void main(void) {
    //Inicializamos el modulo comparador con el comparador 1, V+ > V- y salida no invertida
    Comp_Init(COMPARATORONE,C1POSITIVE,C2POSITIVE,C1NOINVERT,C2NOINVERT,0x01);
    /*Inicializamos el modulo generador de VREF en baja escala, funte del MCU,
    3 voltios de VREF y 5 voltios del MCU*/
    Voltajereference_Init(LOWSCALE,SOURCEMCU,0x03,0x05);
    
    while(1){
        
    }
}
