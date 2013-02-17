/*
 * RoboSapienIR.cpp
 *
 * Based on http://playground.arduino.cc/Main/RoboSapienIR
 * 			http://playground.arduino.cc//Main/RoboSapienServer
 * 			http://www.markcra.com/robot/ir_codes.php
 *
 *
 * Timing based on 1/1200 second clock (~.833ms)
Signal is normally high (idle, no IR).
Start: signal goes low for 8/1200 sec.
Data bits: for each of 8 data bits, space encoded signal depending on bit value
    Sends the most significant data bit first
    If the data bit is 0: signal goes high for 1/1200 sec, and low for 1/1200 sec.
    If the data bit is 1: signal goes high for 4/1200 sec, and low for 1/1200 sec.
    BTW: The first bit (msb) is always 1 (valid codes are from $80 to $FF)
When completed, signal goes high again.
No explicit stop bit. Minimal between signals is not known.
 *
 *  Created on: 12/02/2013
 *      Author: Nick
 */

#include "RoboSapienIR.h"

//#include <ctime>
#include <rpi-hw.hpp>
using namespace rpihw;

#include <iostream>
using namespace std;


RoboSapienIR::RoboSapienIR() {
}

RoboSapienIR::~RoboSapienIR() {
}

void RoboSapienIR::init() {
	rsBit = 9;    		// Total bits of data
	rsEcho = true; 		// Should Arduino Echo RS commands
	rsUsed = true; 		// Has the last command been used

	io.setup( IR_IN, gpio::INPUT );
	io.setup( IR_OUT, gpio::OUTPUT );

	io.write( IR_OUT, gpio::HIGH );
	io.setRisingEvent( IR_IN, true );	// readCommand

	// Indicate that we have hacked into RoboSapien
	io.setup( 22, gpio::OUTPUT );
	io.write( 22, gpio::HIGH );
}

void RoboSapienIR::writeCommand(unsigned char cmd) {
	cout << "writing RoboSapien command to IR port: " << hex << (int)cmd << endl;
//	io.setup( IR_OUT, io.OUTPUT );
	// preamble is 8ts spent low, use to sync clocks
	io.write( IR_OUT, gpio::LOW );
	delayTs(8);

	for( int b = 7; b >= 0; b-- ) {
		io.write( IR_OUT, gpio::HIGH );
		delayTs( (cmd & 1<<b) ? 4 : 1 );
		io.write( IR_OUT, gpio::LOW );
		delayTs(1);
	}

	io.write( IR_OUT, gpio::HIGH );
	// io.setup( IR_IN, io.INPUT );
//	delay(250); // Give a 1/4 sec before
}

//void RoboSapienIR::readCommand() {
//	utils::usleep( 833 + 208 );  // about 1 1/4 bit times
//	int bit = io.read( IR_IN );
//	if( rsBit == 9 ) { // Must be start of new command
//	    rsCommand = 0;
//	    rsBit = 0;
//	    rsUsed = true;
//	}
//	if( rsBit < 8 ) {
//		rsCommand <<= 1;
//	    rsCommand |= bit;
//	}
//	rsBit++;
//	if( rsBit==9 ) rsUsed = false;
//}

void RoboSapienIR::delayTs(unsigned int slices) {
	utils::usleep( bitTime * slices );
}
