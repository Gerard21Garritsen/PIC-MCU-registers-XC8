//Libreria para el control de un motor a pasos con el PIC18F4550
#include <xc.h>

void TIMER3_Init(void); //Funcion que contiene la configuracion del TIMER3
void Motor(float periodo,unsigned int numero_de_pasos); //Funcion para asignar el valor del periodo de la señal
