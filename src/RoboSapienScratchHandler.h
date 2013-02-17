/*
 * RoboSapienScratchHandler.h
 *
 *  Created on: 16/02/2013
 *      Author: Nick
 */

#ifndef ROBOSAPIENSCRATCHHANDLER_H_
#define ROBOSAPIENSCRATCHHANDLER_H_



#include "ScratchBroadcastHandler.h"
#include "RoboSapien.h"

#include <map>
#include <string.h>


struct cmp_str {
	bool operator()(char const *a, char const *b) {
		return ::strcmp(a, b) < 0;
	}
};


typedef std::map<const char *, RoboSapien::RoboCommand, cmp_str> CommandMap;
typedef std::pair<const char*, RoboSapien::RoboCommand> CommandMapping;


class RoboSapienScratchHandler: public ScratchBroadcastHandler {
public:
	RoboSapienScratchHandler();
	virtual ~RoboSapienScratchHandler();

protected:
	virtual bool isInterestedInBroadcast( const char* broadcastName );
	/** Called in the broadcastThreadLoop thread */
	virtual void onBroadcastReceived( const char* broadcastName );

private:
	RoboSapien robot;
	CommandMap commands;
};

#endif /* ROBOSAPIENSCRATCHHANDLER_H_ */
