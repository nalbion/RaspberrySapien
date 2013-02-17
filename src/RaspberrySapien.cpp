//============================================================================
// Name        : RaspberrySapien.cpp
// Author      : Nicholas Albion
//============================================================================

#include "ScratchClient.h"
#include "RoboSapienScratchHandler.h"

#include <iostream>
using namespace std;


int main() {
	cout << "RaspberrySapien Starting up" << endl;

//	RoboSapien robot;
//	robot.sendCommand( RoboSapien::dance );

	RoboSapienScratchHandler robot;

	ScratchClient scratch;
	scratch.subscribe( robot );
	scratch.connect();

	return 0;
}
