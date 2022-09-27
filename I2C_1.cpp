// This file includes all the function definitions of functions that are needed for interfacing the Atmega32 TWI

#include "I2C_1.h"

// This function sets the SCL frequency according to the eqn in the datasheet Freq = Fosc/ (16 + 2 * TWBR* 4^(TWPS)) where TWPS is fixed at a value of 1
// Therefore bitRateRegister should be equal to ((Fosc/Fdesired)-16)/8
void setSCLFrequency (unsigned char bitRateRegister)
{
  TWSR &= ~(1<<TWPS1);
  TWSR |= (1<<TWPS0);
  TWBR = bitRateRegister;
}

void enableTWI ()
{
  TWCR |= (1<<TWEN) | (1<<TWINT);
}

void disableTWI ()
{
  TWCR &= ~(1<<TWEN);
}

// 7 bit slave address
// General call is 1 for recognition of general call, 0 otherwise
void setDeviceAddress(char addr, char generalCall)
{
  generalCall &= (1<<0);
  TWAR = ((addr<<1) | generalCall); 
}

void I2CInit()
 {
	enableTWI();
	setDeviceAddress(0x32,0);
	setSCLFrequency(3); // SCL Freq = 400Khz
 }
 
// addr is the 7 bit address of the slave device
// Return 1 if tranmission was succesfull and slave recieved the data
char initiateWrite (char addr)
{
  TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
  while(!(TWCR & (1<<TWINT)));
  if((TWSR & 0xF8) == 0x38) // Check if master lost arbitration to another master on the bus
  {
    return 0; 
  }
  
  TWDR = (addr<<1); // 7 bit address shifted left once with a 0 in the LSB indicating a write operation
  TWCR = (1<<TWEN) | (1<<TWINT);
  while(!(TWCR & (1<<TWINT)));
  if((TWSR & 0xF8) == 0x20) // SLA+W transmitted but slave does not acknowledge
  {
    return 0;
  } 
  return 1;
}

char burstWrite(char*data, char n)
{
	for(;n>0;n--)
	{
		TWDR = *data;
		TWCR = (1<<TWEN) | (1<<TWINT);
		while(!(TWCR & (1<<TWINT)));
		data++;
		if((TWSR & 0xF8) == 0x30) // Data transmitted and slave returned not acknowledge
		{
			if(n!=1) // not all data was transmitted succesfully
			{
				return 0;
			}
		}
	}
	return 1;
}

char initiateRead (char addr)
{
  TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA);
  while(!(TWCR & (1<<TWINT)));
  if((TWSR & 0xF8) == 0x38) // Check if master lost arbitration to another master on the bus
  {
    return 0; 
  }

  TWDR = ((addr<<1) | (1<<0)); // 7 bit address shifted left once with the LSB set to 1 indicating a read operation
  TWCR = (1<<TWEN) | (1<<TWINT);
  while(!(TWCR & (1<<TWINT)));
  if((TWSR & 0xF8) == 0x48) // SLA+R transmitted but slave does not acknowledge
  {
    return 0;
  }
  return 1;
}

char burstRead(char* data, char n)
{
	for(;n>0;n--)
	{
		TWCR = (1<<TWEN) | (1<<TWINT);
		if(n!=1)
		{
			TWCR |= (1<<TWEA); // If this is not the last byte; send ACK
		}
		while(!(TWCR & (1<<TWINT)));
		*data = TWDR;
		data++;
		if((TWSR & 0xF8) == 0x58) // Last byte recieved and not acknowledge returned
		{
			if(n!=1) // not all data was recieved succesfully
			{
				return 0;
			}
		}
	}
	return 1;
}
void stopTransmission()
{
  TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTO);
}
 