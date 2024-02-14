//Funciones de la libreria EUSART.h
#include "EUSART.h"

void EUSART_Init(uint32_t FOSC,uint32_t BAUD){ //Parametros son FOSC y BAUD
    //Configuramos los pines Tx y Rx para una comunicacion asincrona
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    //Configuramos la comunicacion asincrona de alta velocidad y en modo de 8 bits
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    BAUDCONbits.BRG16 = 0;
    SPBRG = (unsigned int)(FOSC/(16*BAUD)-1); //Segun el valor de FOSC y BAUD sera el valor de SPBRG
    RCSTAbits.SPEN = 1; //Habilitamos la comunicacion EUSART
    TXSTAbits.TXEN = 1; //Habilitamos la transmision del EUSART
    RCSTAbits.CREN = 1; //Habilitamos la recepcion del EUSART
}

void EUSART_String(char *Data){ //Parametro es una cadena
    while(*Data != '\0'){
        putch(*Data);
        Data++;
    }
}

void EUSART_Char(unsigned char caracter){ //Parametro es un caracter
    while(TXSTAbits.TRMT == 0); //Esperamos mientras el buffer esta lleno
    TXREG = caracter; //Cargamos el dato en TXREG
}

void putch(unsigned char byte){ //Parametro es un caracter
    while(TXSTAbits.TRMT == 0); //Espera mientras el buffer esta lleno
    TXREG = byte; //Cargamos el dato en el registro TXREG
}

void EUSART_Read(char *buffer){
    unsigned char data; //Variable en la que se almacenara el dato leido
    
    do{
        while(PIR1bits.RCIF == 0);
        data = RCREG;
        if(data != '\r'){
              *buffer = data;
               buffer++;
        }
    }while(data != '\r');
    
    *buffer = '\0';
}