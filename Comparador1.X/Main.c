//PIC 18F4550
#include <xc.h>
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "Comparator.h" //Libreria para el manejo del Comparador Analogico

void main(void) {
    //Inicializamos el modulo comparador con el comparador 1, V+ > V- y salida invertida
    Comp_Init(COMPARATORONE,C1POSITIVE,C2POSITIVE,C1INVERT,C2NOINVERT,0x01);
    
    while(1){
        
        
    }
}
