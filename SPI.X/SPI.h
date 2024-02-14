//Libreria para el manejo del bus SPI con el PIC 18F4550
#include <stdint.h>
//Macros
#define _XTAL_FREQ 4E6
#define SMP_End 0x01 //Leer dato al final del envio
#define SMP_Middle 0x00 //Leer dato a la mitad del envio
#define CKE_High_Low 0x01 //Envio en transicion de alto a bajo
#define CKE_Low_High 0x00 //Envio en transicion de bajo a alto
#define CKP_High 0x01 //Polaridad del reloj alto
#define CKP_Low 0x00 //Polaridad del reloj bajo
//#define DC LATDbits.LATD7
//#define RS LATDbits.LATD6

void SPIInitMaster(unsigned char smp,unsigned char cke,unsigned char ckp,unsigned char mode){ //Funcion para configurar el MCU como maestro
    TRISCbits.RC7 = 0; //Pin SDO o MOSI como salida para el maestro
    TRISBbits.RB0 = 1; //Pin SDA o MISO como entrada para el esclavo
    TRISBbits.RB1 = 0; //Pin SCK como salida de reloj por el maestro
    SSPSTATbits.SMP = smp; //Configuramos el bit SMP
    SSPSTATbits.CKE = cke; //Configuramos el bit de envio de datos segun transicion
    SSPCON1bits.CKP = ckp; //Configuramos el bit de polaridad del reloj
    SSPCON1bits.SSPM = mode; //Configuramos el modo de trabajo del MCU
    SSPCON1bits.SSPEN = 1; //Habilitamos el puerto SPI
}

void SPIInitSlave(unsigned char smp,unsigned char cke,unsigned char ckp,unsigned char mode){ //Funcion para configurar el MCU como esclavo
    ADCON1 = 0x0F;
    TRISAbits.RA5 = 1; //Pin del CS
    TRISCbits.RC7 = 0; //Pin SDO o MOSI como salida para el maestro
    TRISBbits.RB0 = 1; //Pin SDA o MISO como entrada para el esclavo
    TRISBbits.RB1 = 1; //Pin SCK como salida de reloj por el maestro
    SSPSTATbits.SMP = smp; //Configuramos el bit SMP
    SSPSTATbits.CKE = cke; //Configuramos el bit de envio de datos segun transicion
    SSPCON1bits.CKP = ckp; //Configuramos el bit de polaridad del reloj
    SSPCON1bits.SSPM = mode; //Configuramos el modo de trabajo del MCU
    SSPCON1bits.SSPEN = 1; //Habilitamos el puerto SPI
}

void SPIData(unsigned char Data){ //Funcion para enviar un dato por parte del maestro
    SSPBUF = Data; //Cargamos el dato a enviar en el registro SSPBUF
}

char SPIRead(void){ //Funcion para leer un dato del esclavo
    
    return SSPBUF; //Devolvemos el contenido del Buffer
}

//Funciones de la OLED

/*void cmdWrite(uint8_t reg,uint8_t data){
    SPIData(reg);
    SPIData(data);
    __delay_ms(10);
}
void displayInit(void){
    TRISDbits.RD7 = 0; //Pin DC 
    TRISDbits.RD6 = 0; //Pin Reset
    RS = 1;
    DC = 0; //Comandos en low y datos en high
    SPIData(0xAE);
    SPIData(0x2E);
    SPIData(0xA4);
    SPIData(0x20);
    SPIData(0x02);
    SPIData(0xA1);
    SPIData(0xC8);
    SPIData(0xA6);
    SPIData(0x81);
    SPIData(0xFF);
    SPIData(0xAF);
    RS = 0; //Inicializar la OLED
    __delay_ms(10);
    RS = 1; //Mientras funciona
}

void displaySet(unsigned char x, unsigned char y){
    DC = 0;
    SPIData(0xB0 + y);
    SPIData(0x00 + ((8 * x) & 0x0F));
    SPIData(0x10 + ((8 * x>>4) & 0x0F));
}

void displayClear(void){
    DC = 1;
    for(uint8_t i = 0; i < 8; i++){
        displaySet(0,i);
        for(uint8_t j = 0; j < 128; j++){
            SPIData(0x01);
        }
    }
}*/