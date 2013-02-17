/*
 * RoboSapienScratchHandler.cpp
 *
 *  Created on: 16/02/2013
 *      Author: Nick
 */

#include "RoboSapienScratchHandler.h"
#include <string.h>

#include <iostream>
using namespace std;


RoboSapienScratchHandler::RoboSapienScratchHandler() {
	commands.insert( CommandMapping("turnRight", RoboSapien::turnRight) );
	commands.insert( CommandMapping("rightArmUp", RoboSapien::rightArmUp) );
	commands.insert( CommandMapping("rightArmOut", RoboSapien::rightArmOut) );
	commands.insert( CommandMapping("tiltBodyRight", RoboSapien::tiltBodyRight) );
	commands.insert( CommandMapping("rightArmDown", RoboSapien::rightArmDown) );
	commands.insert( CommandMapping("rightArmIn", RoboSapien::rightArmIn) );
	commands.insert( CommandMapping("walkForward", RoboSapien::walkForward) );
	commands.insert( CommandMapping("walkBackward", RoboSapien::walkBackward) );
	commands.insert( CommandMapping("turnLeft", RoboSapien::turnLeft) );
	commands.insert( CommandMapping("leftArmUp", RoboSapien::leftArmUp) );
	commands.insert( CommandMapping("leftArmOut", RoboSapien::leftArmOut) );
	commands.insert( CommandMapping("tiltBodyLeft", RoboSapien::tiltBodyLeft) );
	commands.insert( CommandMapping("leftArmDown", RoboSapien::leftArmDown) );
	commands.insert( CommandMapping("leftArmIn", RoboSapien::leftArmIn) );
	commands.insert( CommandMapping("stopMoving", RoboSapien::stopMoving) );

	// Programming Commands (no shift)
	commands.insert( CommandMapping("masterCommandProgram", RoboSapien::masterCommandProgram) ); 	// P
	commands.insert( CommandMapping("playProgram", RoboSapien::playProgram) );			// P>> (the one on the bottom)
	commands.insert( CommandMapping("quietPlayProgramWithSubroutines", RoboSapien::quietPlayProgramWithSubroutines) );
	commands.insert( CommandMapping("rightSensorProgram", RoboSapien::rightSensorProgram) ); 	// R>>
	commands.insert( CommandMapping("leftSensorProgram", RoboSapien::leftSensorProgram) ); 	// L>>
	commands.insert( CommandMapping("sonicSensorProgram", RoboSapien::sonicSensorProgram) );	// S>>

	// GREEN shift commands
	commands.insert( CommandMapping("rightTurnStep", RoboSapien::rightTurnStep) );
	commands.insert( CommandMapping("rightHandThump", RoboSapien::rightHandThump) );
	commands.insert( CommandMapping("rightHandThrow", RoboSapien::rightHandThrow) );
	commands.insert( CommandMapping("sleep", RoboSapien::sleep) );
	commands.insert( CommandMapping("rightHandPickup", RoboSapien::rightHandPickup) );
	commands.insert( CommandMapping("leanBackward", RoboSapien::leanBackward) );
	commands.insert( CommandMapping("forwardStep", RoboSapien::forwardStep) );
	commands.insert( CommandMapping("backwardStep", RoboSapien::backwardStep) );
	commands.insert( CommandMapping("leftTurnStep", RoboSapien::leftTurnStep) );
	commands.insert( CommandMapping("leftHandThump", RoboSapien::leftHandThump) );
	commands.insert( CommandMapping("leftHandThrow", RoboSapien::leftHandThrow) );
	commands.insert( CommandMapping("listen", RoboSapien::listen) );
	commands.insert( CommandMapping("leftHandPickup", RoboSapien::leftHandPickup) );
	commands.insert( CommandMapping("leanForward", RoboSapien::leanForward) );
	commands.insert( CommandMapping("reset", RoboSapien::reset) );
	commands.insert( CommandMapping("uhuhExecute", RoboSapien::uhuhExecute) );	// (master command program execute)
	commands.insert( CommandMapping("quietExecute", RoboSapien::quietExecute) );
	commands.insert( CommandMapping("wakeup", RoboSapien::wakeup) );
	commands.insert( CommandMapping("right", RoboSapien::right) );		// (right sensor program execute)
	commands.insert( CommandMapping("left", RoboSapien::left) );
	commands.insert( CommandMapping("sonic", RoboSapien::sonic) );		// (sonic sensor program execute)

	// ORANGE shift commands
	commands.insert( CommandMapping("rightHandStrike3", RoboSapien::rightHandStrike3) );
	commands.insert( CommandMapping("rightHandSweep", RoboSapien::rightHandSweep) );
	commands.insert( CommandMapping("burp", RoboSapien::burp) );
	commands.insert( CommandMapping("rightHandStrike2", RoboSapien::rightHandStrike2) );
	commands.insert( CommandMapping("highFive", RoboSapien::highFive) );
	commands.insert( CommandMapping("rightHandStrike1", RoboSapien::rightHandStrike1) );
	commands.insert( CommandMapping("bulldozer", RoboSapien::bulldozer) );
	commands.insert( CommandMapping("oops_fart", RoboSapien::oops_fart) );
	commands.insert( CommandMapping("leftHandStrike3", RoboSapien::leftHandStrike3) );
	commands.insert( CommandMapping("leftHandSweep", RoboSapien::leftHandSweep) );
	commands.insert( CommandMapping("whistle", RoboSapien::whistle) );
	commands.insert( CommandMapping("leftHandStrike2", RoboSapien::leftHandStrike2) );
	commands.insert( CommandMapping("talkback", RoboSapien::talkback) );
	commands.insert( CommandMapping("leftHandStrike1", RoboSapien::leftHandStrike1) );
	commands.insert( CommandMapping("roar", RoboSapien::roar) );
	commands.insert( CommandMapping("allDemo", RoboSapien::allDemo) );
	commands.insert( CommandMapping("powerOff", RoboSapien::powerOff) );
	commands.insert( CommandMapping("demo1", RoboSapien::demo1) );	// (Karate skits)
	commands.insert( CommandMapping("demo2", RoboSapien::demo2) );	// (Rude skits)
	commands.insert( CommandMapping("dance", RoboSapien::dance) );

	commands.insert( CommandMapping("feetShuffle", RoboSapien::feetShuffle) );
	commands.insert( CommandMapping("noOp", RoboSapien::noOp) );
	commands.insert( CommandMapping("raiseArmThrow", RoboSapien::raiseArmThrow) );
	commands.insert( CommandMapping("karateChop", RoboSapien::karateChop) );
}

RoboSapienScratchHandler::~RoboSapienScratchHandler() {
	// TODO Auto-generated destructor stub
}

/** Called in the ScratchClient's socket listener thread - should return quickly */
bool RoboSapienScratchHandler::isInterestedInBroadcast( const char* broadcastName ) {
//	return commands.count( broadcastName ) != 0;
	// TODO: check that broadcastName is in the commands map.
	return true;
}


/** Called in the broadcastThreadLoop thread */
void RoboSapienScratchHandler::onBroadcastReceived( const char* broadcastName ) {
	cout << "RoboSapienScratchHandler received broadcast: " << broadcastName << endl;

	CommandMap::iterator itr = commands.find( broadcastName );

	RoboSapien::RoboCommand command = itr->second;
	robot.sendCommand( command );

/*	if( strcmp( "left", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::left );
	} else if( strcmp( "allDemo", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::allDemo );
	} if( strcmp( "backwardStep", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::backwardStep );
	} if( strcmp( "bulldozer", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::bulldozer);
	} if( strcmp( "burb", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::burp );
	} if( strcmp( "dance", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::dance );
	} if( strcmp( "demo1", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::demo1 );
	} if( strcmp( "demo2", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::demo2 );
	} if( strcmp( "feetShuffle", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::feetShuffle );
	} if( strcmp( "forwardStep", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::forwardStep );
	} if( strcmp( "highFive", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::highFive );
	} if( strcmp( "karateChop", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::karateChop );
	} if( strcmp( "leanBackward", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leanBackward );
	} if( strcmp( "leanForward", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leanForward );
	} if( strcmp( "leftArmDown", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leftArmDown );
	} if( strcmp( "leftArmIn", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leftArmIn );
	} if( strcmp( "leftArmOut", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leftArmOut );
	} if( strcmp( "leftArmUp", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leftArmUp );
	} if( strcmp( "leftHandPickup", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leftHandPickup );
	} if( strcmp( "leftHandStrike1", broadcastName ) == 0 ) {
		robot.sendCommand( RoboSapien::leftHandStrike1 );
	}*/
}
