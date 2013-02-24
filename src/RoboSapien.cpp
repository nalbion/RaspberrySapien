/*
 * RoboSapien.cpp
 *
 *  Created on: 12/02/2013
 *      Author: Nick
 */

#include "RoboSapien.h"




RoboSapien::RoboSapien() {
	ir.init();
}

RoboSapien::~RoboSapien() {
}

void RoboSapien::sendCommand( RoboCommand command ) {
	ir.writeCommand( command );
}
//
//
////void RoboSapien::loop() {
////	if( !rsUsed ) {
////		if( rsCommand == rsStop && last == rsStop ) rsEcho =! rsEcho;
////	    last = rsCommand;
////	    if( !rsEcho ){
//////	      io.write(10, stdio::HIGH);  // Turn on LED let us know
//////	                              //  we have control our wedge
//////	    	ir.writeCommand(RSRightArmOut);
//////	    	ir.writeCommand(RSTiltBodyRight);
//////	    	ir.writeCommand(RSRightArmDown);
//////
//////	    	ir.writeCommand(RSLeftArmOut);
//////	    	ir.writeCommand(RSTiltBodyLeft);
//////	    	ir.writeCommand(RSLeftArmDown);
//////
//////	    	ir.writeCommand(RSWalkForward);
////
////	    } else {
//////	      digitalWrite(10,LOW);   // No longer in control
////	    	ir.writeCommand(rsCommand);
////	    }
////	    rsUsed = true;
////	}
////}
