
#include "I2C_1.h"

int main(void)
{
	/* Initialize with default settings */
	I2CInit();
	
	/* Or initialize with custom settings */
	enableTWI();
	setDeviceAddress(0x52, 1);		// 7 bit address = 0x52 and General call recognition is enabled.
	setSCLFrequency(18);		 	// SCL Frequency = 100Khz.
}