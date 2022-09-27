
#include "I2C_1.h"
#define TARGET_ADDRESS 0x34

int main(void)
{
	char status = 0;
	char dataOut[3] = {'a', 'r', 'm'};
	char dataIn;
	
	/* Initialize TWI */
	I2CInit();
	
	/* Write 3 bytes to the target device */
	status = initiateWrite(TARGET_ADDRESS);
	if(status)
	{
		status = burstWrite(dataOut, 3);
	}
	
	/* Read 1 byte from the target device */
	status = initiateRead(TARGET_ADDRESS); 		// Initiates a repeated start without releasing control of the I2C bus.
	if(status)
	{
		status = burstRead(&dataIn, 1);
	}
	stopTransmission();
	