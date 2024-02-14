//Libreria para el EUSART en modo Asincrono PIC 18F4550
#include <stdint.h> //Libreria para el manejo de tipos de datos de bits
void EUSART_Init(uint32_t FOSC,uint32_t BAUD); //Funcion para inicializar la comunicacion EUSART
void EUSART_Char(unsigned char caracter); //Funcion para enviar un caracter por puerto serie
void putch(unsigned char byte); //Funcion para enviar cadenas con la funcion printf()
void EUSART_String(char *Data); //Funcion para enviar una cadena de caracteres por puerto serie
void EUSART_Read(char *buffer); //Funcion para leer un dato por puerto serie
unsigned char getche();
