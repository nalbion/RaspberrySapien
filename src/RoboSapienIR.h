/*
 * RoboSapienIR.h
 *
 *  Created on: 12/02/2013
 *      Author: Nick
 */

#ifndef ROBOSAPIENIR_H_
#define ROBOSAPIENIR_H_

#include <rpi-hw.hpp>
//#include <rpi-hw/gpio.hpp>


class RoboSapienIR {
public:
	RoboSapienIR();
	virtual ~RoboSapienIR();

	void init();
	void writeCommand(unsigned char cmd);
//	void readCommand();

private:
	void delayTs(unsigned int slices);

private:
	static const uint8_t IR_IN = 17;	// white wire from the head
	static const uint8_t IR_OUT = 27;	// white wire to the body
	rpihw::gpio io;

	static const int bitTime = 516; 	// Bit time (Theoretically 833 but 516)
										// works for transmission and is faster
	volatile int rsCommand; 			// Single byte command from IR
	volatile int rsBit; 				// Total bits of data
	bool rsEcho; 						// Should we echo RS commands
	bool rsUsed; 						// Has the last command been used

	int last; 							// Previous command from IR
};

#endif /* ROBOSAPIENIR_H_ */
