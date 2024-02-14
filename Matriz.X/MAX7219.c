//Funciones de la libreria MAX7219.h
#include "MAX7219.h"

void SPI_Init(unsigned char mode, unsigned char cke, unsigned char ckp, unsigned char data){
    TRISBbits.RB1 = 0; //Pin SCK
    TRISBbits.RB0 = 1;
    TRISCbits.RC7 = 0; //Pin del MOSI
    TRISCbits.RC6 = 0; //Pin para seleccionar el esclavo CS
    SSPCON1bits.SSPM = mode; //Modo de operacion
    SSPSTATbits.CKE = cke; //Transicion para enviar la trama
    SSPCON1bits.CKP = ckp; //Polaridad inicial de la señal de clock
    SSPSTATbits.SMP = data; //Lectura de la trama
    SSPSTATbits.BF = 0; //Si BF == 1 el dato se ha enviado correctamente
    CS = 1; //Desactivamos al esclavo
    SSPCON1bits.SSPEN = 1; //Habilitamos el bus SPI
    __delay_ms(10);
}

void sendData(unsigned char data){
    SSPBUF = data; //Cargamos el byte en el registro SSPBUF
    while(!SSPSTATbits.BF);
}

void writeData(unsigned char address, unsigned char data){
    sendData(address); //Enviamos el registro a escribir
    sendData(data); //Enviamos el dato
}

void writeMatrix(unsigned char address, unsigned char data, uint8_t device){
    CS = 0;
    for(uint8_t Index = 1; Index <= Num_Devices; Index++){
        if(Index == device)
            writeData(address,data);
        else
            writeData(0x00,0x00);
    }
    CS = 1;
}

void MAX7219_Init(uint8_t devices){
    for(uint8_t i = 1; i <= devices; i++){
        writeMatrix(0x09,0x00, i); //Configuramos el modo no codificado del digito 0 al 7 del registro Decode Mode
        writeMatrix(0x0B,0x07, i); //Habilitamos el uso de los digitos 0 a 7 del registro Scan Limit
        writeMatrix(0x0A,0x07, i); //Configuramos un nivel de brillo de 15/32 del registro Intensity
        writeMatrix(0x0F,0x00, i); //Condiguramos el modo operacion normal del registro Display Test
        writeMatrix(0x0C,0x01, i); //Configuramos el modo de operacion normal del registro Shutdown
        __delay_ms(1);
    }
}

void clearMatrix(uint8_t devices){
    for(uint8_t i = 1; i <= devices; i++){
        for(uint8_t j = 1; j < 9; j++)
            writeMatrix(j, 0x00, i);
    }
}

void charMatrix(uint8_t device, unsigned char caracter){
    for(uint8_t i = 1; i < 9; i++){
        
        writeMatrix(i, Font[caracter - 0x20][i-1], device);
    }
}

void printString(unsigned char *cadena){
    while(*cadena != '\0'){
        uint8_t i = 1;
            for(uint8_t j = 1; j < 9; j++)
                writeMatrix(j, Font[*cadena - 0x20][j-1], i);
           *cadena++;
           i++;
           if(i > Num_Devices)
               i = 1;
    }
}