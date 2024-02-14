#include "EEPROM.h" //Archivo de cabecera de las funciones de la EEPROM

void EEPROM_Write(char address, char dato){
    EEADR = address; //Cargamos la direccion a escribir
    EEDATA = dato; //Caragamos el dato
    //Utilizamos la EEPROM
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1; //Habilitamos la escritura/lectura de la EEPROM
    INTCONbits.GIE = 0; //Deshabilitamos las interrupciones globales
    //Secuencia a cargar en EECON2
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1bits.WR = 1; //Iniciamos el proceso de escritura
    INTCONbits.GIE = 1; //Habilitamos las interrupciones globales
    while(PIR2bits.EEIF == 0); //Espere mientras se escribe el dato
    PIR2bits.EEIF = 0; //Limpiamos el flag
    
}

void EEPROM_Write_Integer(char address,int16_t data){
    for(uint8_t i = 0; i < 2; i++){ //Almacenamos el primer byte y luego el segundo byte
        EEPROM_Write(address + i,*((int8_t*)(&data)+i)); //Le pasamos la direccion y el byte
    }
}

void EEPROM_Write_Float(char address,float data){
    for(uint8_t i = 0; i < 4; i++){
        EEPROM_Write(address + i,*((int8_t*) (&data)+ i));
    }
}

char EEPROM_Read(char address){
    char Data; //Variable para leer el dato
    EEADR = address; //Cargamos la direccion a leer
    //Selecionamos la EEPROM
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1; //Iniciamos el proceso de lectura
    Data = EEDATA; //Almacenamos el dato leido en la variable
    return Data; //Devolvemos el contenido de Data
}

int16_t EEPROM_Read_Integer(char address){
    int data; //Variable para almacenar el dato
    for(uint8_t i = 0; i < 2; i++){ //Leemos el primer byte y luego el segundo byte
        *((int8_t*)(&data)+i) = EEPROM_Read(address + i); //Almacenamos el dato leido
    }
    
    return data; //Devolvemos el dato
}

float EEPROM_Read_Float(char address){
    float data;
    for(uint8_t i = 0; i < 4; i++){
        *((int8_t*)(&data) + i) = EEPROM_Read(address + i);
    }
    
    return data;
}
