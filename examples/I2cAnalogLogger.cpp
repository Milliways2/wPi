//  I2cAnalogLogger
//
//  Created by Ian Binnie on 23/01/2015.
//  Copyright (c) 2015 Ian Binnie. All rights reserved.
//	based on http://blog.oscarliang.net/raspberry-pi-arduino-connected-i2c/

#include <iostream>
#include "wiringPi.h"
#include "wiringPiI2C.h"

const int address = 0x04;	// This is the address we setup in the Arduino Program
int fd;

int writeNumber(unsigned value) {
    return wiringPiI2CWrite(fd, value);
    }

int readNumber(void) {
	return wiringPiI2CRead(fd);
    }

int main(int argc, const char * argv[]) {
	unsigned int var;
	int number;

	fd = wiringPiI2CSetup(address);	// Automatically selects i2c on GPIO

	std::cout << "Enter 1 - 255: ";
	std::cin >> var;
	while(var) {
		writeNumber(var);
		std::cout <<  "Arduino, I sent you " << var  << std::endl;
		number = readNumber();
		std::cout << "Arduino, I received a digit " << number << std::endl;
		std::cout << "Enter 1 - 255: ";
		std::cin >> var;
	}
    return 0;
}
