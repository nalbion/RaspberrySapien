/*
 * ScratchClient.cpp
 *
 * @see http://wiki.scratch.mit.edu/wiki/Remote_Sensors_Protocol
 *
 *  Created on: 13/02/2013
 *      Author: Nick
 */

#include "ScratchClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


#include <iostream>
using namespace std;

ScratchClient::ScratchClient() {
	// TODO Auto-generated constructor stub

}

ScratchClient::~ScratchClient() {
	disconnect();
}

void ScratchClient::disconnect() {
//	delete pThread;
	if( is_valid() ) {
		cout << "Disconnecting";
		::close(sockfd);
	}
}

/**
 * Connect to the Scratch application
 * First need to to right-click on a sensor block in Scratch and
 * "enable remote sensor connections"
 *
 */
void ScratchClient::connect() {
	int portno = 42001;				// Scratch listens on 42001
	struct sockaddr_in serv_addr;
	struct hostent *server;
	const char* host = "127.0.0.1";

	cout << "Connecting..." << endl;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if( !is_valid() ) {
		error("ERROR opening socket");
	}
	server = gethostbyname(host);
	if (server == NULL) {
		error("ERROR, no such host");
		exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);

	int status = inet_pton( AF_INET, host, &serv_addr.sin_addr );
//	if( errno == EAFNOSUPPORT ) {
//		error("inet_pton failed");
//	}

	status = ::connect( sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr) );
	if( status < 0 ) {
		cout << "connect status: " << status << endl;
		error("ERROR connecting - right-click on a sensor block in Scratch and 'enable remote sensor connections'");
	}

	cout << "Connected" << endl;

//	pThread = new rpihw::thread<ScratchClient>( *this, &ScratchClient::run );
//TODO: restore thread
	run();
}

/** Add to list of listeners */
void ScratchClient::subscribe( ScratchBroadcastHandler& listener ) {\
	cout << "Adding new ScratchBroadcastHandler to the listeners list" << endl;
	listeners.push_back( &listener );
}

void ScratchClient::run() {
	while( true ) {
		int length;
		cout << "Waiting for broadcast from Scratch..." << endl;

		// Each message consists of a four-byte "size" field,
		// most-significant byte first, followed by the message itself:
		//   <size: 4 bytes><msg: size bytes>
		int status = ::recv( sockfd, &length, sizeof(length), 0 );
		length = be32toh(length);
		if( status < 0 ) {
			error("ERROR reading from socket");
		} else if( status == 0 ) {
			cout << "Received 0 byte response, quitting thread" << endl;
			break;
		}

		cout << "Receiving " << length << " byte response" << endl;
		char* message = new char[length + 1];
		status = ::recv( sockfd, message, length, 0 );
		message[length] = '\0';

		receiveMessage( message, length );

		delete[] message;
	}
}

void ScratchClient::sendBroadcast( const char* message ) {
	sendScratchMessage( "broadcast", message );
}

void ScratchClient::sendSensorUpdate( const char* varName, const char* value ) {
	char* scratchMessage = new char[strlen(varName) + strlen(value) + 18];
	sprintf( scratchMessage, "sensor-update \"%s\" %s", varName, value);
	sendScratchMessage( scratchMessage );
	delete[] scratchMessage;
}

void ScratchClient::sendScratchMessage( const char* messageType, const char* message ) {
	char* scratchMessage = new char[strlen(messageType) + strlen(message) + 4];
	sprintf( scratchMessage, "%s \"%s\"", messageType, message);
	sendScratchMessage( scratchMessage );
	delete[] scratchMessage;
}

/**
 * Send a string message to Scratch
 */
void ScratchClient::sendScratchMessage( const char* message ) {
	// Each message consists of a four-byte "size" field,
	// most-significant byte first, followed by the message itself:
	//   <size: 4 bytes><msg: size bytes>
	int length = strlen(message);
	char* toSend = new char[4 + length + 1];
	toSend[0] = (length >> 24) & 0x0FF;
	toSend[1] = (length >> 16) & 0x0FF;
	toSend[2] = (length >> 8) & 0x0FF;
	toSend[3] = length & 0x0FF;

	cout << "Sending: " << message << endl;

	// The message up to the first whitespace character (any byte <= 32)
	// is a case-insensitive message type string that is used to decide
	// how to handle the message.
	memcpy( toSend + 4, message, length + 1 );

	int n = ::write( sockfd, toSend, length + 4 );
	delete[] toSend;

	if( n < 0 ) {
		error("ERROR writing to socket");
	}
}

void ScratchClient::receiveMessage( const char* message ) {
	// Each message consists of a four-byte "size" field,
	// most-significant byte first, followed by the message itself:
	//   <size: 4 bytes><msg: size bytes>
	const int length = (message[0] << 24) | (message[1] << 16) | (message[2] << 8) | message[3];

	receiveMessage( message + 4, length );
}

void ScratchClient::receiveMessage( const char* message, int length ) {
	int i = 0;
	// Create a copy of the original message so that we can inject \0 terminators
	char* messageCopy = new char[length + 1];
	memcpy( (void*)messageCopy, (const void*)message, length );
	messageCopy[length] = '\0';

	// The message up to the first whitespace character (any byte <= 32)
	// is a case-insensitive message type string that is used to decide
	// how to handle the message.
	for( int end = length; end-- != 0; i++ ) {
		if( messageCopy[i] <= 32 ) {
			break;
		}
	}
	// Split the received message using a \0 terminator
	messageCopy[i++] = '\0';
	const char* messageType = messageCopy;
	cout << " << Received a '" << messageType << "' message" << endl; // with length: " << length;

	char* messageParams;
	if( i < length ) {
		messageParams = messageCopy + i;
		// Trim trailing space
		char* end = messageParams + strlen(messageParams) - 1;
		while(end > messageParams && isspace(*end)) end--;
		// Write new null terminator
		*(end+1) = '\0';
		cout << "messageParams: '" << messageParams << "'" << endl;
	} else {
		messageParams = NULL;
		cout << "no params";
	}

	if( strcmp(messageType, "sensor-update") == 0 ) {
		// Global variable updated in Scratch - eg (with quotes): "myvar" 0
		messageParams++;
		char* value = strchr( messageParams, '"' );
		*value = '\0';
		value += 2;
		onVariableUpdated( messageParams, value );
	} else if( strcmp(messageType, "broadcast") == 0 ) {
		// messageParams = the string in the Scratch broadcast box
		//char* broadcastName = strndup( messageParams + 1,  )
		messageParams++;
		messageCopy[length-1] = '\0';
		onBroadcastReceived( messageParams );
	}

	delete[] messageCopy;
}


void ScratchClient::onVariableUpdated( const char* varName, const char* value ) {
	cout << "variable updated: '" << varName << "' = '" << value << "'" << endl;
}

void ScratchClient::onBroadcastReceived( const char* broadcastName ) {
	cout << "broadcast received: '" << broadcastName << "'" << endl;

	// iterate through list of listeners, looking for all listeners subscribed to this messageType
	list<ScratchBroadcastHandler*>::iterator itr;
	for( itr = listeners.begin(); itr != listeners.end(); ++itr ) {
		//cout << *i << " ";
		//ScratchBroadcastHandler listener = *itr;
		/*if( listener.isInterestedInBroadcast( messageType ) ) {
			// have the listener deal with the broadcast
			pthread_mutex_lock( &wait_mutex );
			queue_handle = mq_open( BROADCAST_QUEUE

			mq_send( listener
		}*/
		cout << "notifying listener" << endl;
		(*itr)->onBroadcastReceivedInternal( broadcastName );
//		ScratchBroadcastHandler* listener = itr;
//		listener->onBroadcastReceivedInternal( broadcastName );
	}

}

void ScratchClient::error(const char *msg) {
    //perror(msg);
	cerr << msg << endl;
    ::exit(0);
}

