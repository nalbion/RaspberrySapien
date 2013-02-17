/*
 * ScratchClient.h
 *
 *  Created on: 13/02/2013
 *      Author: Nick
 */

#ifndef SCRATCHCLIENT_H_
#define SCRATCHCLIENT_H_

//#include <rpi-hw/thread.hpp>
#include <list>

#include "ScratchBroadcastHandler.h"

class ScratchClient {
public:
	ScratchClient();
	virtual ~ScratchClient();

	void connect();
	void disconnect();
	/** Infinite loop waiting for broadcast messages from Scratch */
	void run();

	void subscribe( ScratchBroadcastHandler& listener );
	void onVariableUpdated( const char* varName, const char* value );
	void onBroadcastReceived( const char* broadcastName );

	void sendBroadcast( const char* message );
	void sendSensorUpdate( const char* varName, const char* value );

private:
	void error(const char *msg);
	bool is_valid() const { return sockfd != -1; }

	void receiveMessage( const char* message );
	void receiveMessage( const char* message, int length );

	/**
	 * @param messageType - eg: "broadcast", "sensor-update"
	 * @param message - eg: "MyBroadCast", "\"myVar\" 42"
	 */
	void sendScratchMessage( const char* messageType, const char* message );
	void sendScratchMessage( const char* message );

private:
	int sockfd;
	std::list<ScratchBroadcastHandler*> listeners;
//	rpihw::thread<ScratchClient> *pThread;
};

#endif /* SCRATCHCLIENT_H_ */
