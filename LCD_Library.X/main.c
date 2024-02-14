#include <xc.h>
#include <stdint.h>
#include "Fuses.h" //header file which contains Fuses configuration
#include "LCD_HDD44780.h" //header file which contain the header functions to control the LCD
#define _XTAL_FREQ 4000000 //Oscillator source to CPU is 4 MHz

void main(void) {
    OSCCONbits.IRCF = 0x06; //frequency internal oscillator block is 4 MHz
    OSCCONbits.SCS = 0x02; //frequency source to CPU come from Internal oscillator block
    LCD_Init(); //Initialize the LCD
    LCD_Clear(); //clear the LCD
    LCD_Write(2,6,"LCD_20X4"); //Write on the LCD "LCD_20X4" apart of file 2 row 7
    __delay_ms(1000);
    for(uint8_t i = 0; i < 6; i++){
        LCD_Scroll(LCD_Right);
        __delay_ms(1000);
    }
    for(uint8_t i = 0; i < 6; i++){
        LCD_Scroll(LCD_Left);
        __delay_ms(1000);
    }
    
    while(1){
        
        
    }
}
