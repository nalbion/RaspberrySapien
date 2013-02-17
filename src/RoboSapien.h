/*
 * RoboSapien.h
 *
 * IR codes from http://www.aibohack.com/robosap/ir_codes.htm
 *
 *  Created on: 12/02/2013
 *      Author: Nick
 */

#ifndef ROBOSAPIEN_H_
#define ROBOSAPIEN_H_

#include "RoboSapienIR.h"

class RoboSapien {
public:
	RoboSapien();
	virtual ~RoboSapien();

	enum RoboCommand {
	  // only a very small subset of commands
	  turnRight = 0x80,
	  rightArmUp = 0x81,
	  rightArmOut = 0x82,
	  tiltBodyRight = 0x83,
	  rightArmDown = 0x84,
	  rightArmIn = 0x85,
	  walkForward = 0x86,
	  walkBackward = 0x87,
	  turnLeft = 0x88,
	  leftArmUp = 0x89,
	  leftArmOut = 0x8A,
	  tiltBodyLeft = 0x8B,
	  leftArmDown = 0x8C,
	  leftArmIn = 0x8D,
	  stopMoving = 0x8E,

	  // Programming Commands (no shift)
	  masterCommandProgram = 0x90, 	// P
	  playProgram = 0x91,			// P>> (the one on the bottom)
	  quietPlayProgramWithSubroutines = 0x9A,
	  rightSensorProgram = 0x92, 	// R>>
	  leftSensorProgram = 0x93, 	// L>>
	  sonicSensorProgram = 0x94,	// S>>

	  // GREEN shift commands
	  rightTurnStep = 0xA0,
	  rightHandThump = 0xA1,
	  rightHandThrow = 0xA2,
	  sleep = 0xA3,
	  rightHandPickup = 0xA4,
	  leanBackward = 0xA5,
	  forwardStep = 0xA6,
	  backwardStep = 0xA7,
	  leftTurnStep = 0xA8,
	  leftHandThump = 0xA9,
	  leftHandThrow = 0xAA,
	  listen = 0xAB,
	  leftHandPickup = 0xAC,
	  leanForward = 0xAD,
	  reset = 0xAE,
	  uhuhExecute = 0xB0,	// (master command program execute)
	  quietExecute = 0x97,
	  wakeup = 0xB1,
	  right = 0xB2,		// (right sensor program execute)
	  left  = 0xB3,		// (left sensor program execute)
	  sonic = 0xB4,		// (sonic sensor program execute)

	  // ORANGE shift commands
	  rightHandStrike3 = 0xC0,
	  rightHandSweep = 0xC1,
	  burp = 0xC2,
	  rightHandStrike2 = 0xC3,
	  highFive = 0xC4,
	  rightHandStrike1 = 0xC5,
	  bulldozer = 0xC6,
	  oops_fart = 0xC7,
	  leftHandStrike3 = 0xC8,
	  leftHandSweep = 0xC9,
	  whistle = 0xCA,
	  leftHandStrike2 = 0xCB,
	  talkback = 0xCC,
	  leftHandStrike1 = 0xCD,
	  roar = 0xCE,
	  allDemo = 0xD0,
	  powerOff = 0xD1,
	  demo1 = 0xD2,	// (Karate skits)
	  demo2 = 0xD3,	// (Rude skits)
	  dance = 0xD4,

	  // NOTES:
//	  add 0x08 to go from right-side commands to left-side commands.
//	  add 0x20 to command bytes for the GREEN shift (ie. $Ax and $Bx range)
//	  add 0x40 to command bytes for the ORANGE shift (ie. $Cx and $Dx range)

	  feetShuffle = 0xF6,
	  noOp = 0xFB,
	  raiseArmThrow = 0xFC,
	  karateChop = 0xD6

	  // noises
//	  whistle = 0xCA,
//	  roar = 0xCE,
//	  burp = 0xC2
	};

//	void init();
	void sendCommand( RoboCommand command );

private:
	RoboSapienIR ir;
};

#endif /* ROBOSAPIEN_H_ */
