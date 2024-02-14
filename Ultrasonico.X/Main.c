//PIC 18F4550
#include <xc.h>
#include <stdbool.h> //Libreria para poder manejar datos boolean
#include <stdlib.h> //Libreria para la conversion de cadenas
#include "Config.h" //Archivo que contiene la configuracion de los FUSES
#include "I2C_OLED1.h" //Libreria para OLED SSD1306 por I2C
#define _XTAL_FREQ 4E6 //Frecuencia CPU 4 MHz

//Variables
uint16_t ts = 0; //Variable que almacena el tiempo de subida
uint16_t tb = 0; //Variable que almacena el tiempo de bajada
uint16_t tt = 0; //Variable almacena la diferencia entre bajada y subida
uint16_t d = 0; //Variable que almacena la distacia detectada
char df[8]; //Variable para mostrar la distancia en caracteres
bool pulso = 0; //Variable para realizar el cambio de un pulso a otro
bool mostrar = 0; //Variable para mostrar la captura en la OLED

void ccpInit(void); //Funcion configuraciones del modulo CCP1 en modo Captura
void TIMERInit(void); //Funcion configuraciones de los TIMERS
void interrupt TIMER0(void); //Funcion de interrupcion para el TIMER0

void main(void) {
    //Inicializacion de la OLED
    I2CInit(MASTER,SLEW_ON);
    display_Init();
    display_Clear();
    //Configuraciones
    ccpInit();
    TIMERInit();
    
    while(1){
        if(mostrar == 1){ //Mostrar la lectura del ancho del pulso en la OLED
            tt = tb - ts; //Diferencia del tiempo final menos inicial
            d = tt * (343/20E3); //multiplicamos el tiempo del ancho del pulso por la velocidad del sonido
            display_Clear(); //Limpiar la OLED
            ltoa(df,d,10); //Conversion a una cadena de la lectura
            display_String(0,0,df); //Mostramos en la OLED la lectura
            display_String(6,0,"us"); //Mostramos la palabra us para saber de que hablamos
            for(uint8_t i = 0; i < 5; i++){ //Ciclo for de retardos para poder visualizar la OLED
                __delay_ms(100);
            }
        }
    }
}

void ccpInit(void){
    TRISCbits.RC2 = 1; //Pin RC2 (CCP1) como entrada
    TRISCbits.RC0 = 0; //Pin RC0 como salida para los pulsos
    PIR1bits.CCP1IF = 0; //Ponemos el flag del CCP1 en cero
    CCP1CON = 0x05; //CCP1 en modo Captura por flanco ascendente
}

void TIMERInit(void){
    //Configuracion del TIMER0 de 8 bits con prescaler de 256
    T0CON = 0x47;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    PIE1bits.CCP1IE = 1; //Habilitamos las interrupciones por CCP1
    INTCONbits.TMR0IF = 0;
    //Configuracion del TIMER1 como temporizador sin prescaler
    PIR1bits.TMR1IF = 0;
    //Cargamos los TIMERS
    TMR0 = 252; //Contabilizar 1 ms de alto y bajo
    TMR1 = 0;
    T0CONbits.TMR0ON = 1; //Encendemos el TIMER0
    T1CONbits.TMR1ON = 1; //Encendemos el TIMER1
}

void interrupt TIMER0(void){
    if(INTCONbits.TMR0IF){
        LATCbits.LATC0 = !LATCbits.LATC0; //Cambiamos de estado el pin RC0
        TMR0 = 252;
        INTCONbits.TMR0IF = 0;
    }
    
    if(PIR1bits.CCP1IF == 1){ //Rutina de la Captura
        if(pulso == 0){
        mostrar = 0;
        ts = CCPR1; //Guardamos la captura del primer flanco
        CCP1CON = 0x04; //Cambiamos el CCP1 a Captura por flanco descendente
        pulso = 1;
        }
        else{
            tb = CCPR1; //Guardamos la captura del segundo flanco
            CCP1CON = 0x05; //Cambiamos el CCP1 a captura por flanco ascendente
            mostrar = 1; //Ponemos a 1 mostrar para poder ver el valor final en la OLED
            pulso = 0;
        }
        PIR1bits.CCP1IF = 0; //Limpiamos el flag del CCP1
    }
}