//PIC18F4550
#include <xc.h>
#include "Config.h" //Archivo de cabecera con la configuracion de los FUSES
#include "Motor_Pasos.h" //Libreria para el control del motor a pasos
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    TRISBbits.RB1 = 0; //Configuramos el pin RB1 como salida para controlar el giro
    TIMER3_Init(); //Inicializamos las configuraciones del TIMER3
    
    while(1){
        LATBbits.LATB1 = 0; //El motor gira en el sentido horario
        Motor(100E-3,200); //Enviamos al motor 100 pulsos de 100 ms
        __delay_ms(1000);
        LATBbits.LATB1 = 1; //El motro gira en el sentido anti horario
        Motor(10E-3,200);
        __delay_ms(1000);
    }
}
