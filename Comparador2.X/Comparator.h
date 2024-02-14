//Libreria para el manejo del Comparador Analogico del PIC 18F4550
#define C1POSITIVE 0x01 //Comparador 1 V+ > V-
#define C1NEGATIVE 0x00 //Comparador 1 V- > V+
#define C2POSITIVE 0x01 //Comparador 2 V+ > V-
#define C2NEGATIVE 0x00 //Comparador 2 V- > V+
#define C1NOINVERT 0x00 //Comparador 1 sin salida invertida
#define C1INVERT 0x01 //Comparador 1 con salida invertida
#define C2NOINVERT 0x00 //Comparador 2 sin salida invertida
#define C2INVERT 0x01 //Comparador 2 con salida invertida
#define COMPARATORONE 0x00 //Solo usamos el comparador 1
#define COMPARATORTWO 0x01 //Usamos los dos comparadores
#define LOWSCALE 0x01 //Rango bajo del VREF
#define HIGHSCALE 0x00 //Rango alto del VREF
#define SOURCEMCU 0x00 //Fuente del MCU para el VREF
#define SOURCEEXT 0x01 //Fuente externa para el VREF

// Funcion para Inicializar las configuraciones del modulo Comparador Analogico
void Comp_Init(char Comparators,char C1Out,char C2Out,char C1Logic,char C2Logic,char Mode){
    ADCON1bits.PCFG = 0x0B; //Configuramos el puerto A como A/D segun corresponda
    //Configuramos los pines de los comparadores segun los que vayamo a utilizar
    if(Comparators == 0x00){
        TRISAbits.RA0 = 1;
        TRISAbits.RA3 = 1;
        TRISAbits.RA4 = 0;
    }
    else{
        TRISAbits.RA1 = 1;
        TRISAbits.RA2 = 1;
        TRISAbits.RA5 = 0;
    }
    //Configuramos el modo de operacion de los comparadores
    CMCONbits.C1OUT = C1Out;
    CMCONbits.C2OUT = C2Out;
    CMCONbits.C1INV = C1Logic;
    CMCONbits.C2INV = C2Logic;
    CMCONbits.CM = Mode;
    
}

//Funcion para inicializar el Modulo Generador de VREF
void Voltajereference_Init(char scale,char source,char CVREF,char CVRSRC){
    CVRCONbits.CVROE = 1; //Habilitar el pin RA2 como salida del VREF
    CVRCONbits.CVRR = scale; //Seleccionamos la escala baja para el VREF
    CVRCONbits.CVRSS = source; //Seleccionamos el VDD y VSS del Microcontrolador como CVRSRC
    CVRCONbits.CVR = (unsigned int)(24*CVREF/CVRSRC);
    CVRCONbits.CVREN = 1; //Habilitamos el Modulo Generador VREF
}