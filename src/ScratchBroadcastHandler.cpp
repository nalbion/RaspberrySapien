/*
 * ScratchBroadcastHandler.cpp
 *
 *  Created on: 15/02/2013
 *      Author: Nick
 */

#include "ScratchBroadcastHandler.h"

#include <fcntl.h>      /* For O_* constants */
#include <sys/stat.h>   /* For mode constants */
#include <mqueue.h>     /* message queue stuff */
#include <string.h>
#include <errno.h>

#include <iostream>
using namespace std;


const char* ScratchBroadcastHandler::BROADCAST_QUEUE_NAME = "/broadcast";

// we want to handle variable received messages first - then again, probably in the same order
const unsigned int ScratchBroadcastHandler::BROADCAST_PRIORITY = 1;
const unsigned int ScratchBroadcastHandler::SENSOR_PRIORITY = 1;
const unsigned int ScratchBroadcastHandler::BUFFER_SIZE = 512;

ScratchBroadcastHandler::ScratchBroadcastHandler() {
	pthread_mutex_init( &wait_mutex, NULL );
	pthread_attr_t *attr = NULL;
	int result = pthread_create( &thread, attr, ScratchBroadcastHandler::startThread, this);
	if( result != 0 ) {
		cerr << "Error creating ScratchBroadcastHandler thread" << endl;
		//::exit(result);
	}
}

ScratchBroadcastHandler::~ScratchBroadcastHandler() {
	pthread_join( thread, 0 );
	pthread_mutex_destroy( &wait_mutex );
}


/**
 * From the ScratchClient's socket listener thread, issue messages to any ScratchBroadcastHandler
 * broadcastThreadLoop threads that are interested
 */
void ScratchBroadcastHandler::onBroadcastReceivedInternal( const char* broadcastName ) {
	cout << "onBroadcastReceivedInternal: '" << broadcastName << "'" << endl;
	mqd_t queue_handle;

	if( isInterestedInBroadcast( broadcastName ) ) {
		// have the listener deal with the broadcast
		pthread_mutex_lock( &wait_mutex );

		queue_handle = mq_open( BROADCAST_QUEUE_NAME, O_WRONLY );
		if( queue_handle == -1 ) {
			cerr << "Error opening message queue" << endl;
			return;
		}

		if( 0 != mq_send( queue_handle, broadcastName, strlen(broadcastName) + 1, BROADCAST_PRIORITY ) ) {
			cerr << "Failed to post message for received broadcast: " << broadcastName << endl;
			mq_close( queue_handle );
			pthread_mutex_unlock( &wait_mutex );
			return;
		}

		pthread_mutex_unlock( &wait_mutex );
		mq_close( queue_handle );
	}
}

void* ScratchBroadcastHandler::startThread( void* pThis ) {
	ScratchBroadcastHandler* handler = reinterpret_cast<ScratchBroadcastHandler*>(pThis);
	handler->broadcastThreadLoop();
	return NULL;
}

/**
 * Executes in a thread, listing for messages from onBroadcastReceivedInternal
 */
void ScratchBroadcastHandler::broadcastThreadLoop() {
	cout << "ScratchBroadcastHandler::broadcastThreadLoop starting up" << endl;
	mqd_t queue_handle;
	struct mq_attr msgq_attr;
	char buffer[BUFFER_SIZE];
	unsigned int sender;

	// ...not sure what these lines are for...
	pthread_mutex_lock( &wait_mutex );
	memset( buffer, 0, BUFFER_SIZE );
	msgq_attr.mq_curmsgs = 0;
	msgq_attr.mq_flags = 0;
	msgq_attr.mq_maxmsg = 100;
	msgq_attr.mq_msgsize = BUFFER_SIZE;
	pthread_detach( pthread_self() );

	// unlink the queue if it exists
	mq_unlink( BROADCAST_QUEUE_NAME );

	queue_handle = mq_open( BROADCAST_QUEUE_NAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, &msgq_attr );
	if( queue_handle == -1 ) {
		cerr << "Error opening message queue: " << errno << endl;
		return;
	}

	mq_getattr( queue_handle, &msgq_attr );

	cout << "Waiting for messages on " << BROADCAST_QUEUE_NAME
			<< ", max message size: " << msgq_attr.mq_msgsize << endl;

	pthread_mutex_unlock( &wait_mutex );
	while( true ) {
		int bytes_read = mq_receive( queue_handle, buffer, BUFFER_SIZE, &sender );
		if( bytes_read == -1 ) {
			cerr << "Failed to receive message from queue: " << errno << endl;
			return;
		} else {
			cout << "ScratchBroadcastHandler received broadcast message: " << buffer << endl;
			// msgq_attr.mq_curmsgs
			onBroadcastReceived( buffer );
		}

		memset( buffer, 0, BUFFER_SIZE );
		sleep( 5 );
	}
}

/** Called in the ScratchClient's socket listener thread - should return quickly */
bool ScratchBroadcastHandler::isInterestedInBroadcast( const char* broadcastName ) {
	// default implementation - loop on an array of acceptable broadcast names
//	for( ) {
//		if( strcmp( broadcastName, broadcastNames[i] ) == 0 ) {
//			return true;
//		}
//	}
	return true;
}

