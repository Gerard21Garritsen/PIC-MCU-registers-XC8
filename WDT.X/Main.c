//PIC 16F877A
//Configuracion de los FUSES
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void main(void) {
    //Configuramos RB0 y RB1 como salidas para los leds
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    PORTB = 0x00; //Ponemos en bajo el puerto B
    OPTION_REGbits.PSA = 1; //Asignamos el Postcaler al WDT
    OPTION_REGbits.PS = 0x06; //Configuramos el Postcaler a 64 para tener 1.152 segundos
    PORTBbits.RB0 = 1;
    __delay_ms(1200);
    PORTBbits.RB1 = 1;
    
    while(1){
        
    }
}
