//PIC 18F4550
#include <xc.h> //Libreria del compilador
#include "Config.h" //Archivo header de la configuracion de los FUSES
#include <stdint.h> //Libreria para tipos de dato de bits
#include <stdio.h> //Libreria para el manejo de datos de entrada y salida
#include <i2c.h> //Libreria para el I2C de MPLAB X
#include "LCD.h" //Libreria para el manejo del LCD por el bus de 4 bits
#define _XTAL_FREQ 4E6 //Frecuencia del CPU de 4 MHz

void main(void) {
    unsigned char Data; //Variable para almacenar el dato leido
    char i[2]; //Variable para convertir el dato leido en char
    OpenI2C(MASTER,SLEW_OFF); //Inicializamos el I2C para el PIC como maestro y a 100 KHz
    Lcd_Init(); //Inicializamos el LCD
    Lcd_Cmd(LCD_CURSOR_OFF); //Apagamos el cursor
    Lcd_Cmd(LCD_CLEAR); //Limpiamos la LCD
    while(1){
        StartI2C(); //Iniciamos la comunicacion I2C
        IdleI2C(); //Esperamos a que el bus este vacio para evitar colisiones de datos
        WriteI2C(0xA0); //Enviamos la direccion del esclavo mas el bit de escritura
        IdleI2C();
        //Enviamos la direccion de la memoria a escribir enviando el byte MSB y luego el LSB
        WriteI2C(0>>8);
        WriteI2C(0);
        WriteI2C(64); //Enviamos el dato a guardar en formato ascii
        __delay_ms(10); //Retardo de 10 ms ya que la EEPROM tarda 5 ms en almacenar y enviar el dato
        StopI2C(); //Finalizamos la comunicacion I2C
        __delay_ms(10); //Generamos un retardo entre operacion y operacion
        StartI2C(); //Iniciamos la comunicacion I2C
        IdleI2C();
        WriteI2C(0xA0); //Enviamos la direccion del esclavo
        IdleI2C();
        //Enviamos la direccion a leer de la memoria, primero el byte MSB y luego el LSB
        WriteI2C(0>>8);
        WriteI2C(0);
        RestartI2C(); //Reseteamos la comunicacion I2C
        IdleI2C();
        WriteI2C(0xA1); //Enviamos la direccion del esclavo mas el bit de lectura
        IdleI2C();
        Data = ReadI2C(); //Leemos el dato y lo almacenamos en Dato
        __delay_ms(10);
        NotAckI2C(); //Le decimos al esclavo que ya no envie mas datos
        StopI2C(); //Detenemos la comunicacion I2C
        __delay_ms(10);
        sprintf(i,"%c",Data); //Covertimos el dato leido en carater en la variable i
        Lcd_Out2(1,0,i); //Imprimimos en la posicion (1,0) el dato leido de la memoria
    }
}