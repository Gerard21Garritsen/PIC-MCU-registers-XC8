/*Program that show in LCD display with HD44780 IC the hour and date read it from
DS1307 module*/
#include <xc.h>
#include <stdio.h>
#include "Fuses.h"
#include "I2C.h"
#include "DS1307.h"
#include "LCD_HDD44780.h"
#define _XTAL_FREQ 4000000 //frecuency clock source to CPU is 4 MHz

void main(void) {
    OSCCONbits.SCS = 0x02; //select the internal oscillator as the main clock source
    OSCCONbits.IRCF = 0x06; //set internal oscillator as 4 MHz
    uint8_t datos[7]; //array to save the parameters read from the DS1307
    unsigned char date[20]; //array to save the parameters in integer as char after use itoa() function
    unsigned char time[10];
    //Begin the LCD configuration
    I2Cinit(4000000,100000);
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    //put the date and hour in the next format DS1307(hour,minutes,seconds,day,da of week, month, year)
    DS1307setTime(13,53,0,1,5,10,18);
    
    while(1){
        DS1307read(datos);
        sprintf(date,"%d/Octubre/2018",datos[4]);
        sprintf(time,"%d:%d:%d",datos[2],datos[1],datos[0]);
        Lcd_Out2(1,2,"Reloj RTC DS1307");
        Lcd_Out2(2,3,date);
        Lcd_Out2(3,6,time);
        __delay_us(100);
    }
}
