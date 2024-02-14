//Libreria para el manejo de la memoria EEPROM 24LC256
//El dato se guardara en el formato que se eliga char para carater y int para numerico
#include <i2c.h> //Libreria para el manejo del I2C de MPLAB X
#include <stdint.h> //Libreria para el manejo de tipo de datos en bits
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz
#define WRITE 0xA0 //Direccion del esclavo para escritura
#define READ 0xA1 //Direccion del esclavo para lectura

void I2C_Init(char modo, char speed){ //Funcion configurar el Bus I2C
    //Configuramos los pines del BUS IIC
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    OpenI2C(modo,speed);
}

void writeData(uint16_t Address,uint8_t Data){ //Funcion para escribir un dato
    IdleI2C();
    StartI2C();
    WriteI2C(WRITE);
    WriteI2C(Address>>8);
    WriteI2C(Address);
    WriteI2C(Data);
    StopI2C();
    __delay_ms(5);
}

char readData(uint16_t Address){ //Funcion para leer un dato
    char Data;
    IdleI2C();
    StartI2C();
    WriteI2C(WRITE);
    WriteI2C(Address>>8);
    WriteI2C(Address);
    RestartI2C();
    WriteI2C(READ);
    Data = ReadI2C();
    __delay_ms(5);
    NotAckI2C();
    StopI2C();
    
    return Data;
}

void readsData(uint16_t AddressStart,uint16_t NumData,char value[]){ //Funcion para leer varios datos consecutivos
    uint8_t i = 0;
    IdleI2C();
    StartI2C();
    WriteI2C(WRITE);
    WriteI2C(AddressStart>>8);
    WriteI2C(AddressStart);
    RestartI2C();
    WriteI2C(READ);
    while(AddressStart < NumData){
        value[i] = ReadI2C();
        __delay_ms(5);
        if(AddressStart < NumData-1){
            AckI2C();
        }
        else{
            NotAckI2C();
        }
        AddressStart++;
        i++;
    }
    StopI2C(); //Finalizamos la comunicacion*/
    value[i] = '\n'; //Agregamos el caracter nueva linea al array
    value[i+1] = '\r'; //Agregamos el caracter de retorno de carro al array
    value[i+2] = '\0'; //Agregamos el caracter nulo para indicar el fin del array
}

void I2C_Close(void){ //Funcion para deshabilitar el Bus I2C
    CloseI2C();
}