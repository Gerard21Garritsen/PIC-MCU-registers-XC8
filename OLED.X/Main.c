//PIC 18F4550
//Control de pantalla LCD y OLED
#include <xc.h>
#include <stdint.h>
#include "LCD.h" //Libreria pantalla LCD 16x2 bus 4 bits
//#include "SPI_SSD1306.h" //Libreria pantalla OLED SSD1306 SPI
//#include "I2C_OLED.h" //Libreria pantalla OLED SH1106 I2C
#include "Config.h" //Archivo de cabecera que contiene la configracion de los FUSES

#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

void LCD(void){
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_UNDERLINE_ON);
    Lcd_Cmd(LCD_BLINK_CURSOR_ON);
    Lcd_Out(1,0,"Display LCD 20x4");
    Lcd_Out(2,0,"PIC18F4550");
    Lcd_Out(3,0,"HOLA A TODOS");
    Lcd_Out(4,0,"ELECTRONICA");
    for(uint8_t i = 0; i < 10; i++){
        __delay_ms(100);
    }
}
/*
void I2C(void){
    I2CInit(MASTER,SLEW_ON);
    display_Init();
    __delay_ms(1);
    display_Clear();
    display_String(0,0,"PROTOCOLO I2C");
 for(uint8_t i = 0; i < 20; i++){
     __delay_ms(100);
  }
}

void SPI(void){
    SPIInitMaster(SPI_FOSC_4,MODE_10,SMPEND);
    displayInit();
    __delay_ms(1);
    displayClear();
    displayString(0,0,"PROTOCOLO SPI");
    for(uint8_t i = 0; i < 20; i++){
        __delay_ms(100);
    }
}

void SPI2(void){
    displayClear();
    __delay_ms(1);
    displayBitmap();
}

void I2C2(void){
    display_Clear();
    display_Bitmap();
    for(uint8_t i = 0; i < 20; i++){
        __delay_ms(100);
    }
    I2CClose();
    __delay_ms(10);
}*/

void main(void) {
    
    
    while(1){
        
        
    }
}
