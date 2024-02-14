//This file contain main functions to initialize and control LCD display
#include <xc.h>
#define _XTAL_FREQ 4000000 //we have to define the frequency to work.

//Create some macros to define which pins we´re gonna use
#define RS LATDbits.LATD4
#define E  LATDbits.LATD5
#define D4 LATDbits.LATD0
#define D5 LATDbits.LATD1
#define D6 LATDbits.LATD2
#define D7 LATDbits.LATD3

//Define some macros to confgure LCD display
#define LCD_On 1
#define LCD_Off 0
#define Cursor_On 1
#define Cursor_Off 0
#define Blink_On 1
#define Blink_Off 0
#define LCD_Right 0x1C
#define LCD_Left 0x18

void LCD_Init(void);
void LCD_On_Off(char Backlight, char Cursor, char Blink);
void LCD_Clear(void);
void LCD_Cmd(unsigned char data);
void LCD_Char_CP(char letter);
void LCD_Write(unsigned char y, unsigned char x, char *cadena);
void LCD_Scroll(unsigned char data);