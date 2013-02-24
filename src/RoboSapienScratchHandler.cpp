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
	commands.insert( CommandMapping("rs_turnRight", RoboSapien::turnRight) );
	commands.insert( CommandMapping("rs_rightArmUp", RoboSapien::rightArmUp) );
	commands.insert( CommandMapping("rs_rightArmOut", RoboSapien::rightArmOut) );
	commands.insert( CommandMapping("rs_tiltBodyRight", RoboSapien::tiltBodyRight) );
	commands.insert( CommandMapping("rs_rightArmDown", RoboSapien::rightArmDown) );
	commands.insert( CommandMapping("rs_rightArmIn", RoboSapien::rightArmIn) );
	commands.insert( CommandMapping("rs_walkForward", RoboSapien::walkForward) );
	commands.insert( CommandMapping("rs_walkBackward", RoboSapien::walkBackward) );
	commands.insert( CommandMapping("rs_turnLeft", RoboSapien::turnLeft) );
	commands.insert( CommandMapping("rs_leftArmUp", RoboSapien::leftArmUp) );
	commands.insert( CommandMapping("rs_leftArmOut", RoboSapien::leftArmOut) );
	commands.insert( CommandMapping("rs_tiltBodyLeft", RoboSapien::tiltBodyLeft) );
	commands.insert( CommandMapping("rs_leftArmDown", RoboSapien::leftArmDown) );
	commands.insert( CommandMapping("rs_leftArmIn", RoboSapien::leftArmIn) );
	commands.insert( CommandMapping("rs_stopMoving", RoboSapien::stopMoving) );

	// Programming Commands (no shift)
	commands.insert( CommandMapping("rs_masterCommandProgram", RoboSapien::masterCommandProgram) ); 	// P
	commands.insert( CommandMapping("rs_playProgram", RoboSapien::playProgram) );			// P>> (the one on the bottom)
	commands.insert( CommandMapping("rs_quietPlayProgramWithSubroutines", RoboSapien::quietPlayProgramWithSubroutines) );
	commands.insert( CommandMapping("rs_rightSensorProgram", RoboSapien::rightSensorProgram) ); 	// R>>
	commands.insert( CommandMapping("rs_leftSensorProgram", RoboSapien::leftSensorProgram) ); 	// L>>
	commands.insert( CommandMapping("rs_sonicSensorProgram", RoboSapien::sonicSensorProgram) );	// S>>

	// GREEN shift commands
	commands.insert( CommandMapping("rs_rightTurnStep", RoboSapien::rightTurnStep) );
	commands.insert( CommandMapping("rs_rightHandThump", RoboSapien::rightHandThump) );
	commands.insert( CommandMapping("rs_rightHandThrow", RoboSapien::rightHandThrow) );
	commands.insert( CommandMapping("rs_sleep", RoboSapien::sleep) );
	commands.insert( CommandMapping("rs_rightHandPickup", RoboSapien::rightHandPickup) );
	commands.insert( CommandMapping("rs_leanBackward", RoboSapien::leanBackward) );
	commands.insert( CommandMapping("rs_forwardStep", RoboSapien::forwardStep) );
	commands.insert( CommandMapping("rs_backwardStep", RoboSapien::backwardStep) );
	commands.insert( CommandMapping("rs_leftTurnStep", RoboSapien::leftTurnStep) );
	commands.insert( CommandMapping("rs_leftHandThump", RoboSapien::leftHandThump) );
	commands.insert( CommandMapping("rs_leftHandThrow", RoboSapien::leftHandThrow) );
	commands.insert( CommandMapping("rs_listen", RoboSapien::listen) );
	commands.insert( CommandMapping("rs_leftHandPickup", RoboSapien::leftHandPickup) );
	commands.insert( CommandMapping("rs_leanForward", RoboSapien::leanForward) );
	commands.insert( CommandMapping("rs_reset", RoboSapien::reset) );
	commands.insert( CommandMapping("rs_uhuhExecute", RoboSapien::uhuhExecute) );	// (master command program execute)
	commands.insert( CommandMapping("rs_quietExecute", RoboSapien::quietExecute) );
	commands.insert( CommandMapping("rs_wakeup", RoboSapien::wakeup) );
	commands.insert( CommandMapping("rs_right", RoboSapien::right) );		// (right sensor program execute)
	commands.insert( CommandMapping("rs_left", RoboSapien::left) );
	commands.insert( CommandMapping("rs_sonic", RoboSapien::sonic) );		// (sonic sensor program execute)

	// ORANGE shift commands
	commands.insert( CommandMapping("rs_rightHandStrike3", RoboSapien::rightHandStrike3) );
	commands.insert( CommandMapping("rs_rightHandSweep", RoboSapien::rightHandSweep) );
	commands.insert( CommandMapping("rs_burp", RoboSapien::burp) );
	commands.insert( CommandMapping("rs_rightHandStrike2", RoboSapien::rightHandStrike2) );
	commands.insert( CommandMapping("rs_highFive", RoboSapien::highFive) );
	commands.insert( CommandMapping("rs_rightHandStrike1", RoboSapien::rightHandStrike1) );
	commands.insert( CommandMapping("rs_bulldozer", RoboSapien::bulldozer) );
	commands.insert( CommandMapping("rs_oops_fart", RoboSapien::oops_fart) );
	commands.insert( CommandMapping("rs_leftHandStrike3", RoboSapien::leftHandStrike3) );
	commands.insert( CommandMapping("rs_leftHandSweep", RoboSapien::leftHandSweep) );
	commands.insert( CommandMapping("rs_whistle", RoboSapien::whistle) );
	commands.insert( CommandMapping("rs_leftHandStrike2", RoboSapien::leftHandStrike2) );
	commands.insert( CommandMapping("rs_talkback", RoboSapien::talkback) );
	commands.insert( CommandMapping("rs_leftHandStrike1", RoboSapien::leftHandStrike1) );
	commands.insert( CommandMapping("rs_roar", RoboSapien::roar) );
	commands.insert( CommandMapping("rs_allDemo", RoboSapien::allDemo) );
	commands.insert( CommandMapping("rs_powerOff", RoboSapien::powerOff) );
	commands.insert( CommandMapping("rs_demo1", RoboSapien::demo1) );	// (Karate skits)
	commands.insert( CommandMapping("rs_demo2", RoboSapien::demo2) );	// (Rude skits)
	commands.insert( CommandMapping("rs_dance", RoboSapien::dance) );

	commands.insert( CommandMapping("rs_feetShuffle", RoboSapien::feetShuffle) );
	commands.insert( CommandMapping("rs_noOp", RoboSapien::noOp) );
	commands.insert( CommandMapping("rs_raiseArmThrow", RoboSapien::raiseArmThrow) );
	commands.insert( CommandMapping("rs_karateChop", RoboSapien::karateChop) );
}

RoboSapienScratchHandler::~RoboSapienScratchHandler() {
	// TODO Auto-generated destructor stub
}

/** Called in the ScratchClient's socket listener thread - should return quickly */
bool RoboSapienScratchHandler::isInterestedInBroadcast( const char* broadcastName ) {
//	return commands.count( broadcastName ) != 0;
	// TODO: check that broadcastName is in the commands map.
//	return true;
	return strncmp( "rs_", broadcastName, 3 ) == 0;
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
