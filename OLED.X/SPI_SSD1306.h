//Libreria para el control de una pantalla OLED  SSD1306 128x64 con PIC 18F4550
#include <stdint.h>
#include <spi.h>
//Macros
#define _XTAL_FREQ 4E6
#define DC LATDbits.LATD7 //Pin RD7 para CS
#define RS LATDbits.LATD6 //Pin RD6 para RESET
//#define WHITE 0xA6 //Pixeles en alto encendidos
//#define BLACK 0xA7 //Pixeles en alto apagados

const unsigned char Fuente[][8]={ //Arreglo en mapa de bits de los carateres ascii en 8x8 pixeles
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
{0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
{0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
{0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
{0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
{0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
{0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
{0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
{0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
{0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
{0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
{0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
{0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
{0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
{0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
{0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
{0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
{0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
{0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
{0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
{0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
{0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
{0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
{0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
{0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
{0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
{0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
{0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
{0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
{0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
{0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
{0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
{0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
{0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
{0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
{0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
{0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
{0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
{0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
{0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
{0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
{0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
{0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
{0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
{0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
{0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
{0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
{0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
{0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
{0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
{0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
{0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
{0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
{0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
{0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
{0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
{0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
{0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
{0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
{0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
{0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
{0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
{0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
{0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
{0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
{0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
{0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
{0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
{0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
{0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
{0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
{0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
{0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
{0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
{0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
{0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
{0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
{0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
{0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
{0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
{0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
{0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
{0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
{0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
{0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
{0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
{0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
{0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
{0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
{0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
{0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
{0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
{0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
{0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
};

const unsigned char cypress1[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0x7f, 0x7f, 0x7f, 0x3f, 
0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0xe7, 0xe7, 0xe3, 0xc3, 0xc2, 0xc2, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x81, 0x81, 0x81, 0x83, 0xd3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x08, 0xfe, 0xff, 0x07, 
0x03, 0x03, 0x03, 0x1f, 0x1e, 0x1c, 0x00, 0x01, 0x07, 0x3f, 0xfe, 0xf0, 0xf8, 0xff, 0x1f, 0x03, 
0x00, 0x00, 0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x87, 0xff, 0xfe, 0x7c, 0x00, 0x00, 0xff, 0xff, 
0xff, 0x83, 0x83, 0x83, 0x87, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x83, 0x83, 0x83, 
0x83, 0x83, 0x03, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xe3, 0xc3, 0x83, 0x07, 0x1f, 0x1e, 0x00, 0x00, 
0x00, 0x3e, 0x7f, 0xf7, 0xc3, 0xc3, 0x83, 0x1f, 0x1f, 0x1c, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0x7e, 0x18, 0x00, 0x82, 0xc6, 0xe2, 0xf0, 0xf8, 0xfc, 0xfc, 
0xfc, 0xfd, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x10, 0x7f, 0xff, 0xc0, 
0xc0, 0xc0, 0xc0, 0xf8, 0x78, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 
0xff, 0x03, 0x03, 0x0f, 0x7f, 0xfd, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xc1, 
0xc1, 0xc1, 0xc0, 0x00, 0x00, 0x38, 0xf8, 0xf8, 0xc1, 0xc3, 0xc3, 0xe7, 0xfe, 0x7c, 0x00, 0x00, 
0x00, 0x78, 0xf8, 0xe0, 0xc1, 0xc3, 0xc7, 0xff, 0xfe, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x2f, 0x6f, 0x6f, 0xef, 0xef, 0xef, 0xe7, 
0xe7, 0xe7, 0xe3, 0xe3, 0xe1, 0xe0, 0xe0, 0xe0, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0x63, 
0x63, 0x23, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x01, 
0x01, 0x31, 0x21, 0x30, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x20, 0x21, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x21, 0x00, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x01, 
0x01, 0x00, 0x10, 0x00, 0x70, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x31, 0x21, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x21, 0x21, 0x11, 0x00, 0x30, 0x20, 0x10, 
0x00, 0x50, 0x00, 0x70, 0x01, 0x11, 0x41, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char cypress2[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0xb0, 0x98, 0x8c, 0x0e, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1e, 
0x1e, 0x1c, 0x18, 0x80, 0x00, 0x00, 0xe0, 0x30, 0x10, 0x30, 0x60, 0x00, 0x70, 0xc0, 0xc0, 0x30, 
0x00, 0xf0, 0x30, 0x10, 0x30, 0xe0, 0x00, 0xf0, 0x30, 0x10, 0xb0, 0xc0, 0x00, 0xf0, 0x30, 0x10, 
0x10, 0x00, 0x00, 0xe0, 0x90, 0x30, 0x60, 0x00, 0x40, 0xf0, 0x10, 0x30, 0x60, 0x00, 0x00, 0x00, 
0x00, 0x03, 0x1f, 0x3f, 0x3f, 0xbf, 0xbe, 0xbf, 0xbf, 0xbf, 0x9e, 0x8c, 0xb0, 0x92, 0x9c, 0x9e, 
0x9e, 0x1d, 0x3e, 0x0e, 0x00, 0x00, 0x0f, 0x18, 0x10, 0x98, 0x0c, 0x00, 0x00, 0x1f, 0x1d, 0x00, 
0x00, 0x1f, 0x1b, 0x03, 0x01, 0x01, 0x00, 0x1f, 0x01, 0x03, 0x1f, 0x10, 0x00, 0x1f, 0x11, 0x11, 
0x91, 0x00, 0x00, 0x1c, 0x11, 0x13, 0x0e, 0x00, 0x04, 0x1c, 0x11, 0x1b, 0x0e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*//Funciones
void SPIInitMaster(unsigned char smp,unsigned char cke,unsigned char ckp,unsigned char mode);
void SPIInitSlave(unsigned char mode);
void SPIData(unsigned char Data);
char SPIRead(void);
void SPIClose(void);
void cmdWrite(unsigned char command);
void dataWrite(unsigned char data);
void displayInit(void);
void displaySet(unsigned char x,unsigned char y);
void displayClear(void);
void displayChar(unsigned char caracter);
void displayString(unsigned char x, unsigned char y,unsigned char *cadena);
void displayBitmap(void);
void displayInvert(unsigned char value);*/

void SPIInitMaster(unsigned char mode,unsigned char clock,unsigned char smp){ //Funcion para configurar el MCU como maestro
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    OpenSPI(mode,clock,smp);
}

void SPIClose(void){
    CloseSPI();
}

//Funciones de la OLED

void cmdWrite(unsigned char command){ //Funcion para enviar un comando a la OLED
    DC = 0; //Comando low dato high
    WriteSPI(command);
}

void dataWrite(unsigned char data){ //Funcion para enviar un dato a la OLED
    DC = 1;
    WriteSPI(data);
}

void displayInit(void){ //Funcion para inicializar la OLED
    //Inicializacion de la pantalla OLED
    RS = 1;
    __delay_ms(5);
    RS = 0;
    __delay_ms(10);
    RS = 1;
    __delay_ms(20);
    //Comandos de configuracion de la OLED
    cmdWrite(0xAE); //Apagamos la OLED
    //Estblecemos el maximo de filas en 64
    cmdWrite(0xA8);
    cmdWrite(0x3F);
    //Configuramos el offset de la OLED en cero (sin offset))
    cmdWrite(0xD3);
    cmdWrite(0x00);
    //Configuramos el inicio de la pantalla en el pixel 0 de 64
    cmdWrite(0x40);
    //Invertimos el eje X de la OLED
    cmdWrite(0xA1);
    //Invertimos el eje Y de la OLED
    cmdWrite(0xC8);
    //Mapeamos los pines COM
    cmdWrite(0xDA);
    cmdWrite(0x12);
    //Configuramos el contraste de la OLED al maximo 0- 255
    cmdWrite(0x81);
    cmdWrite(0xFF);
    //Configuramos que la OLED muestre el contenido en su RAM
    cmdWrite(0xA4);
    //Configuramos la OLED en modo normal con pixeles en alto encendidos y en bajo apagados
    cmdWrite(0xA6);
    //Configuramos el reloj de la OLED
    cmdWrite(0xD5);
    cmdWrite(0x80);
    //Configuramos las columnas a usar de la 0 a la 127
    cmdWrite(0x21);
    cmdWrite(0x00);
    cmdWrite(0x7F);
    //Configuramos las filas a usar de la 0 a la 7
    cmdWrite(0x22);
    cmdWrite(0x00);
    cmdWrite(0x07);
    //Configuramos el modo de escritura en horizontal con direccion de pagina
    cmdWrite(0x20);
    cmdWrite(0x02);
    //Hbilitamos el Oscilador DC-DC para 9v (PUMP)
    cmdWrite(0x8D);
    cmdWrite(0x14);
    //Encender la OLED
    cmdWrite(0xAF);
}

void displaySet(unsigned char x, unsigned char y){ //Funcion para fijar las coordenadas de la OLED
    cmdWrite(0xB0 + y);
    cmdWrite(0x00 + ((8 * x) & 0x0F));
    cmdWrite(0x10 + ((8 * x>>4) & 0x0F));
}

void displayClear(void){ //Funcion para limpiar la OLED
    for(uint8_t i = 0; i < 8; i++){ //Recorremos las 8 filas o paginas
        displaySet(0,i);
        for(uint8_t j = 0; j < 128; j ++){ //Recorremos las columnas
            dataWrite(0x00); //Ponemos en cero cada pixel
        }
    }
}

void displayChar(unsigned char caracter){ //Funcion para imprimir una caracter en la OLED
    for(uint8_t i = 0; i < 8; i++){
        dataWrite(Fuente[caracter - 0x20][i]);
    }
}

void displayString(unsigned char x,unsigned char y,unsigned char *cadena){ //Funcion para desplegar texto en la OLED
    displaySet(x,y);
    while(*cadena){
        for(uint8_t i = 0; i < 8; i++){
            dataWrite(Fuente[*cadena - 0x20][i]);
        }
        *cadena++;
        x++;
        if(x >= 15){
            x = 0;
            y++;
            displaySet(x,y);
        }
    }
}

void displayBitmap(void){ //Funcion para desplegar un mapa de bits de 128x64 para otras dimensiones requiere modificacion
    for(uint8_t i = 0; i < 8; i++){
        displaySet(0,i);
        for(uint16_t j = 128*i; j < 128*(i+1); j ++){
            dataWrite(cypress1[j]);
        }
    }
}

void displayInvert(unsigned char value){ //Funcion que invierte el background de la OLED
    cmdWrite(value);
}