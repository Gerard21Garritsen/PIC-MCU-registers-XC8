//Libreria para manejar uno o varios servomotores con el PIC 18F4550
#include <xc.h>

void TIMER1_Init(void); //Funcion contiene las configuraciones del TIMER1
void __interrupt()TIMER1_Interrupt(void); //Funcion de interrupcion para generar el PWM
void Servo_Duty(unsigned int angle); //Funcion para asignar el ciclo de trabajo deseado