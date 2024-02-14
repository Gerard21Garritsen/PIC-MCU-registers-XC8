//Libreria para el EUSART en modo Asincrono PIC 18F4550
#include <xc.h> //Libreria del compilador XC8
#include <stdint.h> //Libreria para el manejo de tipos de datos de bits

void USART_Init(uint32_t FOSC,uint32_t BAUD); //Funcion para inicializar la comunicacion EUSART
void USART_Char(char Caracter); //Funcion para enviar un caracter por puerto serie
void putch(char dato); //Funcion que usa la funcion printf() para enviar datos por puerto serie
void USART_String(char *Data); //Funcion para enviar una cadena de caracteres por puerto serie
char USART_Read(void); //Funcion para leer un dato por puerto serie
