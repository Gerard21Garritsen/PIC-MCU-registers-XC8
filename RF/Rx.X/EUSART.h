//Libreria para el Modulo EUSART PIC 18F4550
#include <stdint.h> //Libreria para usar tipos de datos de bits

void EUSART_Init(uint32_t FCPU,uint32_t BAUDRATE); //Funcion Inicializar el EUSART
void EUSART_Char(unsigned char Data); //Funcion enviar un caracter
void EUSART_String(unsigned char *String); //Funcion para enviar una cadena 
char EUSART_Read(void); //Funcion para leer un dato

void EUSART_Init(uint32_t FCPU,uint32_t BAUDRATE){
    TRISCbits.TRISC7 = 1; //Configuramos el pin RC7 como entrada
    TRISCbits.TRISC6 = 0; //Configuramos el pin RC6 como entrada
    TXSTAbits.BRGH = 1; //Configuramos el modo de Alta velocidad
    SPBRG = (unsigned int)(FCPU/(16*BAUDRATE)-1); //Cargamos el valor en el registro SPBRG para la velocidad
    TXSTAbits.TXEN = 1; //Habiltamos el Transmisor
    RCSTAbits.CREN = 1; //Habilitamos la recepcion continua de datos
    RCSTAbits.SPEN = 1; //Habilitamos el EUSART
    
}

void EUSART_Char(unsigned char Data){
    while(TXSTAbits.TRMT == 0); //Espere mientras esta lleno el Buffer
    TXREG = Data; //Cargamos el dato
}

void EUSART_String(unsigned char *String){
    while(*String != '\0'){
        EUSART_Char(*String);
        *String++;
    }
}

char EUSART_Read(void){
    char Data;
    while(PIR1bits.RCIF == 0); //Espere mientras se recibe un dato
    Data = RCREG;
    
    return Data;
}
