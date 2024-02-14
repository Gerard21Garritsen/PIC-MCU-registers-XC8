/*This file contain the DS1307 configuration to adjust the hour and date also
the function to read the dates configured before*/
//Address from device to write is 0xD0 and to read is 0xD1;
#include "DS1307.h" //include the DS1307.h header file
#define add_write 0xD0 //DS1307 address to write data
#define add_read 0xD1 //DS1307 address to read data

void DS1307setTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t week, uint8_t month, uint8_t year){
    seconds = seconds & 0x7F; //Enable the oscillator from DS1307
    hours = hours & 0x3F; //Set the 24 hours mode
    I2Cstart();
    I2Cdata(add_write,0x00); //We're gonna configure the seconds in the 0x00 register
    I2Cwrite(binBCD(seconds));
    I2Cwrite(binBCD(minutes));
    I2Cwrite(binBCD(hours));
    I2Cwrite(binBCD(day));
    I2Cwrite(binBCD(week));
    I2Cwrite(binBCD(month));
    I2Cwrite(binBCD(year));
    I2Cstop();
}

void DS1307read(uint8_t data[]){
    I2Cstart();
    I2Cdata(add_write,0x00);
    I2Creset();
    I2Cwrite(add_read); //we're gonna read from 0x00 register til 0x07;
    data[0] = BCDbin(I2Cread());
    I2CACK();
    data[1] = BCDbin(I2Cread());
    I2CACK();
    data[2] = BCDbin(I2Cread());
    I2CACK();
    data[3] = BCDbin(I2Cread());
    I2CACK();
    data[4] = BCDbin(I2Cread());
    I2CACK();
    data[5] = BCDbin(I2Cread());
    I2CACK();
    data[6] = BCDbin(I2Cread());
    I2CNACK(); //Master sent NACK to slave device to slave stop to sending data
    I2Cstop(); //Finish the I2C communication
    
}

uint8_t binBCD(uint8_t bin){ //function which turns binary to BCD
    return (((bin/10) << 4) + bin%10);
}

uint8_t BCDbin(uint8_t bcd){ //function which turns BCD to binary
    return (bcd%16 + 10 * (bcd/16));
}