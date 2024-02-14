//This file contain the declaration of whole functions to initialize and control LCD display
//Please put the macro indicate frequency that you're going to use to delays
#include "LCD_HDD44780.h"

void LCD_Init(void){
    TRISD = 0x00; //All port D as output
    LATD = 0x00; //set port D in LOW state
    __delay_ms(20); //wait more than 15 ms
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 1; D4 = 1; E = 0;
    __delay_ms(5); //wait more than 4.1 ms
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 1; D4 = 1; E = 0;
    __delay_us(120); //wait more than 100 us
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 1; D4 = 1; E = 0;
    __delay_us(120); //wait more than 100 us
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 1; D4 = 0; E = 0;
    __delay_ms(120); //wait more than 100 us
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 1; D4 = 0; E = 0; //configure Function Set register
    RS = 0; E = 1; D7 = 1; D6 = 0; D5 = 0; D4 = 0; E = 0; //4 bits mode, enable 2 lines and 5x8 pixels
    __delay_us(50); //wait more than 37 us
    
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 0; E = 0; //configure Display On/Off Control register
    RS = 0; E = 1; D7 = 1; D6 = 0; D5 = 0; D4 = 0; E = 0; //display off without cursor and blink
    __delay_us(50); //wait more than 37 us
    
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 0; E = 0;//configure Clear Display register
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 1; E = 0;
    __delay_ms(2); //wait more than 1.52 ms
    
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 0; E = 0; //configure Entry Mode Set
    RS = 0; E = 1; D7 = 0; D6 = 1; D5 = 1; D4 = 0; E = 0; //increase AC and cursor won't follow the DDRAM
    __delay_us(50); //wait more than 37 us
    
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 0; E = 0; //configure Display On/Off Control register
    RS = 0; E = 1; D7 = 1; D6 = 1; D5 = 0; D4 = 0; E = 0; //turn on the display and disable cursor and blink of it.
    __delay_us(50);
    //end of initilization of LCD
}

void LCD_On_Off(char Backlight, char Cursor, char Blink){
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 0; E = 0;
    RS = 0; E = 1; D7 = 1; D6 = Backlight; D5 = Cursor; D4 = Blink; E = 0;
    __delay_us(50);
}

void LCD_Clear(void){
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 0; E = 0;
    RS = 0; E = 1; D7 = 0; D6 = 0; D5 = 0; D4 = 1; E = 0;
    __delay_ms(2);
}

void LCD_Cmd(unsigned char data){
    RS = 0; E = 1; D7 = (data & 0b10000000)>>7; D6 = (data & 0b01000000)>>6; D5 = (data & 0b00100000)>>5;
    D4 = (data & 0b00010000)>>4; E = 0;
    RS = 0; E = 1; D7 = (data & 0b00001000)>>3; D6 = (data & 0b00000100)>>2; D5 = (data & 0b00000010)>>1;
    D4 = (data & 0b00000001); E = 0;
    __delay_us(50);
}

void LCD_Char_CP(char letter){
    RS = 1; E = 1; D7 = (letter & 0b10000000)>>7; D6 = (letter & 0b01000000)>>6; D5 = (letter & 0b00100000)>>5;
    D4 = (letter & 0b00010000)>>4; E = 0;
    RS = 1; E = 1; D7 = (letter & 0b00001000)>>3; D6 = (letter & 0b00000100)>>2; D5 = (letter & 0b00000010)>>1;
    D4 = (letter & 0b00000001); E = 0;
    __delay_us(50);
}

void LCD_Write(unsigned char y, unsigned char x, char *cadena){
    unsigned char row;
    switch (y){
        case 0: row = 128 + x;
        break;
        case 1: row = 192 + x;
        break;
        case 2: row = 148 + x;
        break;
        case 3: row = 212 + x;
        defaultcase: break;
    }
    LCD_Cmd(row);
    while(*cadena != 0){
        LCD_Char_CP(*cadena);
        cadena++;
    }
}

void LCD_Scroll(unsigned char data){
    LCD_Cmd(data);
}
