//Archivo que contiene las funciones para el manejo del USART PIC18F4550
#include "USART.h" //Archivo de cabecera para el USART

void USART_Init(uint32_t FOSC,uint32_t BAUD){ //Parametros son FOSC y BAUD
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

void USART_Char(char caracter){ //Parametro es un caracter
    while(TXSTAbits.TRMT == 0); //Espera mientras el buffer esta lleno
    TXREG = caracter;
}

void USART_String(char *data){ //Parametro es una cadena
    while(*data != '\0'){
        USART_Char(*data);
        *data++;
    }
}

void putch(char data){ //Parametro es un caracter
    while(TXSTAbits.TRMT == 0); //Espere mientras el buffer esta lleno
    TXREG = data; //Cargamos el dato en el buffer
    
}

char USART_Read(void){
    char data; //Variable en la que se almacenara el dato leido
    while(PIR1bits.RCIF == 0); //Espera mientras se recibe un dato
    data = RCREG; //Guardar el dato leido en la variable data
    
    return data; //Retornar data
}

void USART_Read_String(unsigned char *cadena){
    unsigned char data; //Variable donde se guardara caracter por caracter
    
    do{
        while(PIR1bits.RCIF == 0); //Esperamos a recibir el dato
        data = RCREG; //Almacenamos el caracter en data
        if(data != '\r'){ //Si el caracter recibido es diferente del caracter retorno de carro (tecla enter)
            *cadena = data; //Almacenamos el caracter en cadena
            cadena++;
        }
    }while(data != '\r'); //Esto se repetira mientras no se presione la tecla enter
    
    *cadena = '\0'; //Agregamos al final el caracter de fin de cadena
}
