/*
 * ScratchBroadcastHandler.h
 *
 *  Created on: 15/02/2013
 *      Author: Nick
 */

#ifndef SCRATCHBROADCASTHANDLER_H_
#define SCRATCHBROADCASTHANDLER_H_

#include <pthread.h>

class ScratchClient;

class ScratchBroadcastHandler {
public:
	ScratchBroadcastHandler();
	virtual ~ScratchBroadcastHandler();

public:


protected:
	virtual bool isInterestedInBroadcast( const char* broadcastName );
	/** Called in the broadcastThreadLoop thread - subclasses to implement */
	virtual void onBroadcastReceived( const char* broadcastName ) = 0;

private:
	void onBroadcastReceivedInternal( const char* broadcastName );
	static void* startThread( void* pThis );
	void broadcastThreadLoop();

	pthread_t thread;
	pthread_mutex_t wait_mutex;

	static const unsigned int BROADCAST_PRIORITY;
	static const unsigned int SENSOR_PRIORITY;
	static const char* BROADCAST_QUEUE_NAME;
	static const unsigned int BUFFER_SIZE;

	friend class ScratchClient;
};

#endif /* SCRATCHBROADCASTHANDLER_H_ */
