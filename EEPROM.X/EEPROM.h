//Libreria para el manejo de la memoria EEPROM del PIC18F4550
#include <xc.h> //Libreria del compilador XC8
#include <stdint.h> //Libreria para utilizar tipos de datos en bits

void EEPROM_Write(char address,char dato); //Funcion para esrcibir en la EEPROM
void EEPROM_Write_Integer(char address,int16_t data); //Funcion para escrbir una variable entera
void EEPROM_Write_Float(char address,float data); //Funcion para escribir una varable float en la EEPROM
char EEPROM_Read(char address); //Funcion para leer un caracter almacenado en la EEPROM
int16_t EEPROM_Read_Integer(char address); //Funcion para leer una variable entera de la EEPROM
float EEPROM_Read_Float(char address); //Funcion para leer una variable float de la EEPROM
