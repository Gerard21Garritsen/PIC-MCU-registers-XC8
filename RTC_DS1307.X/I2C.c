//This file contain the main configuration of I2C peripheripal
#include "I2C.h"

void I2Cinit(uint32_t FCPU, uint32_t clock){
    uint8_t speed; //variable int type to save the value to load in the SSPADD register
    TRISBbits.RB0 = 1; //SDA pin
    TRISBbits.RB1 = 1; //SCL pin
    SSPSTATbits.SMP = 1; //Set transmission speed in 1 KHz
    SSPCON1bits.SSPM = 0x08; /*configure microcontroller as master where the clock source
    it will be SSPADD = FOSC/(4*clock)-1*/
    speed = FCPU/(4*clock)-1;
    SSPADD = speed;
    SSPCON2 = 0x00; //clear all flags
    SSPCON1bits.SSPEN = 1; //enable the I2C pins
}

void I2Cidle(void){ //function which supervise if at the moment to start a communication the I2C bus is busy
    while((SSPCON2 & 0x1F) | SSPSTATbits.RW);
}

void I2Cstart(void){
    I2Cidle();
    SSPCON2bits.SEN = 1; //begin transmision
    while(SSPCON2bits.SEN); //wait until it will be send
}

void I2Cwrite(uint8_t data){
    SSPBUF = data;
    while((SSPSTATbits.RW == 1) || (SSPSTATbits.BF == 1)); //wait if there is a transmission in curse
    if(SSPCON2bits.ACKSTAT) //if slave didn't receive the ACK bit
        SSPCON2bits.PEN = 1; //begin STOP condition
    else
        SSPIF = 0; //In opposite case, clear the flag
}

void I2Cdata(uint8_t address, uint8_t data){ //function to send the device's addres and data
    I2Cwrite(address);
    I2Cwrite(data);
}

void I2Cstop(void){
    SSPCON2bits.PEN = 1; //stop transmission
    while(SSPCON2bits.PEN);
}

void I2Creset(void){
    SSPCON2bits.RSEN = 1; //restart I2C communication
    while(SSPCON2bits.RSEN);
}

void I2CACK(void){ //function to send ACK condition when the master device is reading datas from the slave
    SSPCON2bits.ACKDT = 0; //enable ACK bit
    SSPCON2bits.ACKEN = 1;//begin ACKDT bit transmission
    while(SSPCON2bits.ACKEN);
}

void I2CNACK(void){ //function to send NACK condition when the master device is reading datas from the slave
    SSPCON2bits.ACKDT = 1; //enable NOACK bit
    SSPCON2bits.ACKEN = 1;//begin ACKDT bit transmission
    while(SSPCON2bits.ACKEN);
}

uint8_t I2Cread(void){
    SSPCON2bits.RCEN = 1; //Enable reception master mode
    while(SSPSTATbits.BF == 0); //wait until the buffer it will be full
    return SSPBUF;
}
