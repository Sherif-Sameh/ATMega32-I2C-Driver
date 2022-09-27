/** @file I2C_1.h
 * I2C/TWI Driver.
 * This is a driver for the I2C/TWI peripheral on the AVR 8 bit ATMega32 family of microcontrollers.
 */

#ifndef I2C_1_H
#define I2C_1_H

#include <avr/io.h>

/**
 * This function is used to set the frequency of the SCL line according to the value of the bitRateRegister.
 * @param bitRateRegister This parameter is used to set the SCL frequency and should be chosen
 * according to the following equation:
 * \f[
 \textnormal{bitRateRegister} = \frac{(\frac{Foscillator}{Fdesired} - 16)} {8}
 \f]
 */
void setSCLFrequency (unsigned char bitRateRegister);

/**
 * This function will enable the TWI and only needs to be called once in the setup.
 */
void enableTWI ();

/**
 * This function will disable the TWI.
 */
void disableTWI ();

/**
 * This function sets the I2C address and general call recognition for the ATMega32 microcontroller.
 * @param addr This parameter represents the 7 bit I2C address.
 * @param generalCall This parameter sets the microcontroller's response to general calls made
 * on the I2C bus where 1 means that the microcontroller will respond to general calls and 0 it will ignore them.
 */
void setDeviceAddress(char addr, char generalCall);

/**
 * This function initializes the I2C peripheral with some default settings where:
 * F_SCL = 400Khz, Device address = 0x32, and General calls are ignored.
 */
void I2CInit();

/**
 * This function will try to take control of the I2C bus and make a write request to the address specified.
 * @param addr This parameter represents the 7 bit I2C address of the target device.
 * @return Will return 1 if it was successful and 0 otherwise.
 */
char initiateWrite (char addr);

/**
 * This function will load n bytes into the TWDR serially till all the data specified has been written to the
 * target device.
 * @param data This parameter is a pointer to the start of the array of bytes that will be sent.
 * @param n This parameter represents the number of bytes to send and should be less than or equal to the
 * length of the byte array.
 * @attention This function must be preceded by a call to initiateWrite(char addr).
 * @return Will return 1 if it was successful and 0 otherwise.
 * @see initiateWrite(char addr)
 */
char burstWrite(char *data, char n);

/**
 * This function will try to take control of the I2C bus and make a read request from the address specified.
 * @param addr This parameter represents the 7 bit I2C address of the target device.
 * @return Will return 1 if it was successful and 0 otherwise.
 */
char initiateRead (char addr);

/**
 * This function will read n bytes from the TWDR serially till all the data specified has been read from the
 * target device.
 * @param data This parameter is a pointer to the start of the array of bytes that will be used to store the incoming data.
 * @param n This parameter represents the number of bytes to read and should be less than or equal to the
 * length of the byte array.
 * @attention This function must be preceded by a call to initiateRead(char addr).
 * @return Will return 1 if it was successful and 0 otherwise.
 * @see initiateRead(char addr)
 */
char burstRead(char* data, char n);

/**
 * This function is used to trigger the I2C stop signal which ends the ongoing communication and frees the I2C bus.
 */
void stopTransmission();

/** @example I2C_SetupExample.cpp
 * An example on how to initialize the TWI before starting communication.
 */
 
 /** @example I2C_CommunicationExample.cpp
  * An example of how to use the I2C driver for readings and writing bytes from and to a target device.
  */

#endif