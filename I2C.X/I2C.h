//Archivo de cabecera de funciones del bus I2C
#include <xc.h>
#include <stdint.h>

void I2C_Init(void); //Funcion iniciar comunicacion I2C
void I2C_Wait(void);  //Funcion para esperar si el bus I2C esta ocupado
void I2C_Start(void);  //Funcion I2C para iniciar la comunicacion I2C
void I2C_Reset(void);  //Funcion para reiniciar la comunicacion I2C
void I2C_Stop(void);  //Funcion para detener la comunicacion I2C
uint8_t I2C_Data(uint8_t Dato); //Funcion para enviar los datos I2C
uint8_t I2C_Read(void);  //Funcion para leer los datos enviados a esclavo

