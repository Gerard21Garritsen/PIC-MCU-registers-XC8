//Libreria para el EUSART en modo Asincrono PIC 18F4550
#include <stdint.h> //Libreria para el manejo de tipos de datos de bits

void EUSART_Init(uint32_t FOSC,uint32_t BAUD); //Funcion para inicializar la comunicacion EUSART
void EUSART_Char(char Caracter); //Funcion para enviar un caracter por puerto serie
void EUSART_String(char *Data); //Funcion para enviar una cadena de caracteres por puerto serie
char EUSART_Read(void); //Funcion para leer un dato por puerto serie

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
        EUSART_Char(*Data);
        *Data++;
    }
}

void EUSART_Char(char Caracter){ //Parametro es un caracter
    while(TXSTAbits.TRMT == 0); //Espera mientras el buffer esta lleno
    TXREG = Caracter;
}

char EUSART_Read(void){
    char data; //Variable en la que se almacenara el dato leido
    while(PIR1bits.RCIF == 0); //Espera mientras se recibe un dato
    data = RCREG; //Guardar el dato leido en la variable data
    
    return data; //Retornar data
}
