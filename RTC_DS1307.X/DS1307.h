//This header file contain the function headers which are declared on DS1307.c file
#include <xc.h>
#include "I2C.h" //include I2C library
//this function set the time and date in DS1307
void DS1307setTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t week, uint8_t month, uint8_t year);
void DS1307read(uint8_t data[]); //This function read all the date from module
uint8_t binBCD(uint8_t bin); //This function turns the binary digits to BCD
uint8_t BCDbin(uint8_t bcd); //This function turns the BCD to binary