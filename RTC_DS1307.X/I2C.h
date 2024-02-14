//This file contain the headers functions that are programming in the source file I2C.c
#include <xc.h>
#include <stdint.h>
void I2Cinit(uint32_t FCPU, uint32_t clock); //configure the I2C protocol taking as parameters the FOSC and clock speed comunication
void I2Cidle(void); //function to make a wait if there is a transmission in curse
void I2Cstart(void); //function which start the communication
void I2Cwrite(uint8_t data);//function to write a byte
void I2Cdata(uint8_t address, uint8_t data); //function to write the address byte and data byte
void I2Cstop(void); //function which contain the stop condition to communication
void I2Creset(void); //function to restart the communication
void I2CACK(void); //function to send ACK byte when the master is working in receive mode
void I2CNACK(void); //function to send NACK byte when the master is working in receive mode
uint8_t I2Cread(void); //function to read a simple byte when any slave is sending datas to the master
