//Libreria para el USART en modo Asincrono PIC18F4550
#include <xc.h> //Libreria del compilador XC8
#include <stdint.h> //Libreria para el manejo de datos en bits

void USART_Init(uint32_t FOSC,uint32_t BAUD); //Funcion para inicializar la comunicacion EUSART
void USART_Char(char caracter); //Funcion para enviar un caracter por puerto serie
void USART_String(char *cata); //Funcion para enviar una cadena de caracteres por puerto serie
void putch(char data); //Funcion que utiliza la funcion printf para imprimir por puerto serie
char USART_Read(void); //Funcion para leer un dato por puerto serie
void USART_Read_String(unsigned char *cadena); //Funcion para leer una cadena por puerto serie
