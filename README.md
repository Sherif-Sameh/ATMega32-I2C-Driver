Author: Sherif Sameh

For the latest version of the driver : https://github.com/Sherif-Sameh/ATMega32-I2C-Driver

This document describes the I2C/TWI driver for the ATMega32 family of microcontrollers.

Current version: 1.0

The I2C/TWI driver includes functions for:

	- Enabling/Disabling the I2C peripheral.
	- Configuring the SCL frequency.
	- Configuring the 7 bit device address as well as the enabling/disabling general call recognition.
	- Initializing the I2C peripheral with some default settings.
	- Making a write request to a specific address onto the I2C bus.
	- Making a read request from a specific address onto the I2C bus.
	- After making a write request succesfully, writing one or multiple bytes in succession to that device.
	- After making a read request succesfully, reading one multiple bytes in succession from that device.
	- Ending communication and releasing control of the I2C bus.

Important notes about the driver:

	- All functions in the driver that interact with the I2C bus return 1 upon succesfully completing or 0 otherwise.
	- Currently using interrupts is not supported only polling techniques are available.
	- If a request is made to an address of a device that is not active or does not exist, the microcontroller will get stuck infinitely waiting for a reply.
	
Planned future updates:
	
	- Implementing support for use with interrupts rather than polling.
	- Implementing a time-out timer using at least one if not both a software timer and a hardware timer. 
	- Changing the return value to an enum which can support multiple return values other than just 1 or 0 and give more information
	about the cause of error (lost aribitration, timeout, etc...).