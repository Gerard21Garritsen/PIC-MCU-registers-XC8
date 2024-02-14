//PIC 18F4550
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = XT_XT     // Oscillator Selection bits (XT oscillator (XT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#include <xc.h> //Libreria XC

#define _XTAL_FREQ 4E6 //Frecuencia 4 MHz sin PLL

unsigned short N = 0; //Variable para la velocidad de muestreo de los digitos
unsigned short Numero = 0; //Variable de conteo

void __interrupt(high_priority) rutina(void); //Declaracion de la funcion de interrupcion de alta prioridad
void __interrupt(low_priority) rutina2(void); //Declaracion de la funcion de interrupcion de baja prioridad
void Display(unsigned short Numero); //Declaracion de la funcion Display

void main(void) {
    TRISC = 0x01; //Configuramos todo el puerto C como salida digital excepto el pin RC0
    TRISD = 0x07; //Configuramos RC<7:3> como salidas digitales excepto RC<2:0>
    INTCON2bits.RBPU = 0; //Habilitamos las resistencias de Pull Up
    INTCONbits.GIE = 1; //Habiltamos las interrupciones globales
    INTCONbits.PEIE= 1; //Habilitamos las interrupciones de baja prioridad
    INTCONbits.INT0IE = 1; //Habilitamos la interrupcion por pin RB0
    INTCON3bits.INT1IE = 1; //Habilitamos la interrupcion por el pin RB1
    INTCON2bits.INTEDG0 = 0; //Habilitamos la interrupcion por el pin RB0 en flanco descendente
    INTCON2bits.INTEDG1 = 0; //Configuramos la interrupcion por RB1 en flanco descendente (LOW)
    RCONbits.IPEN = 1; //Habilitamos los niveles de prioridad en interrupciones
    INTCON3bits.INT1IP = 0; //Configuramos que la interrupcionpor RB1 tenga menor prioridad
    LATC = 0x00; //Ponemos el puerto C en bajo
    LATD = 0x00; //Ponemos el puerto D en bajo
    
    while(1){
        Display(Numero); //Llamamos a la funcion display;
        N++;
        if(N == 10){
            N = 0;
            Numero++;
            if(Numero == 10000){
                Numero = 0;
            }
        }
    }
}

void Display(unsigned short Numero){/*Funcion que contiene el arreglo de los digitos y el algoritmo para mostrar
    los digitos por el display*/
    const unsigned short Num[10] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6}; //Arreglo contiene los digitos
    unsigned short Mil;
    unsigned short Cen;
    unsigned short Dec;
    unsigned short Un;
    //Operaciones para mostrar por los display cada unidad
    Mil = Numero/1000;
    Cen = (Numero % 1000)/100;
    Dec = (Numero % 100)/10;
    Un = Numero % 10;
    //Secuencia de muestreo de los valores en los display, cada aumento de unidad se realiza en  200ms
    LATC = Num[Un];
    LATD = 0x80;
    __delay_ms(5);
    LATC = Num[Dec];
    LATD = 0x40;
    __delay_ms(5);
    LATC = Num[Cen];
    LATD = 0x20;
    __delay_ms(5);
    LATC = Num[Mil];
    LATD = 0x10;
    __delay_ms(5);
    
}

void __interrupt() rutina(void){ //Funcion de interrupcion de alta prioridad para el pin RB0
    if(INTCONbits.RBIF == 1){
    for(unsigned short i = 0; i < 5; i++){ //Generamos un blink de 5 parpadeos de 500ms
    LATBbits.LATB0 = 1;
    __delay_ms(500);
    LATBbits.LATB0 = 0;
    __delay_ms(500);
    }
    INTCONbits.RBIF = 0; //Limpiamos el flag de interrupciones
  }
}

void __interrupt(low_priority) rutina2(void){ //Funcion de interrupcion de baja prioridad para el pin RB1
    if(INTCON3bits.INT1IF == 1){
        for(unsigned short i = 0; i < 3; i++){ //Generamos un blink de 3 parpadeos de 1s
            LATDbits.LATD3 = 1;
            __delay_ms(1000);
            LATDbits.LATD3 = 0;
            __delay_ms(1000);
        }
        INTCON3bits.INT1IF = 0; //Limpiamos la bandera de la interrupcion
    }
}
