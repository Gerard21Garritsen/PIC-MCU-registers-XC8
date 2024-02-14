//Archivo contiene las funciones para el uso del I2C
#include <xc.h>
#include <stdint.h>
#include "I2C.h"

void I2C_Init(void){ //Inicializacion del I2C
    //Configuracion de los pines del I2C como salida
    TRISBbits.TRISB0 = 1; //Configuramos el pin RC3 como salida
    TRISBbits.TRISB1 = 1; //Configuramos el pin RC4 como salida
    //Configuracion del I2C
    SSPSTAT = 0x80; //Configuramos el registro para velocidad estandar de 100 kbps
    SSPCON1 = 0x28; //Habilitamos el I2C y configuramos el PIC como maestro
    SSPCON2 = 0x00;  //Comunicacion I2C no iniciada
    SSPADD = 0x09; //Cargamos con 9 el registro para una velocidad de 100 kbps con 4 MHz del CPU
}

void I2C_Wait(void){ //Funcion espera para cuando este ocupado el bus I2C
    while((SSPCON2 & 0b00011111) || (SSPSTAT & 0b1000100));
}

void I2C_Start(void){ //Funcion iniciar la comunicacion I2C
    I2C_Wait();
    SSPCON2bits.SEN = 1; //Iniciamos la comunicacion I2C
}

void I2C_Reset(void){ //Funcion reiniciar la comunicacion I2C
    I2C_Wait();
    SSPCON2bits.RSEN = 1; //Reiniciamos la comunicacion I2C
}

void I2C_Stop(void){ //Funcion detener la comunicacion I2C
    I2C_Wait();
    SSPCON2bits.PEN = 1; //Detener la comunicacion
}

uint8_t I2C_Data(uint8_t Dato){  //Funcion envio de la informacion
    I2C_Wait();
    SSPBUF = Dato; //Cargamos el byte de informacion en el registro
    return ACKSTAT; //Regresamos el bit de confirmacion a cero tenemos una comnicacion exitosa
}

uint8_t I2C_Read(void){  //Funcion para leer el dato enviado al esclavo
    uint8_t Datorecibido; //Variable para almacenar el dato en cierta direccion de memoria
    
    I2C_Wait();
    SSPCON2bits.RCEN = 1;  //Reiniciamos la comunicacion I2C lectura por parte del maestro
    
    I2C_Wait();
    Datorecibido = SSPBUF;  //Guardamos el dato recibido del registro SSPBUF
    
    I2C_Wait();
    SSPCON2bits.ACKDT = 1;  //Ponemos el bit de reconocimento despues de que el maestro recibio el dato
    
    I2C_Wait();
    SSPCON2bits.ACKEN = 1;  //Le decimos al esclavo que ya no se leeran mas datos
    
    return Datorecibido;  //La funcion devuelve el dato almacenado en el esclavo.
}
