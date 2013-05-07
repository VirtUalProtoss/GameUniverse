#include <iostream>
#include "cNet.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


using namespace std;

bool isdown;

void * thread_server( void *arg ) {
	int loc_id = * ( int * ) arg;
	cNet netObj( ( char * )&loc_id );
	cout << ( char * )&loc_id;
	isdown=true;
	return 0;
}

int main( int argc, char** argv ) {
	isdown=false;

	int id1, result;
	pthread_t thread1;
	id1 = 1;
	result = pthread_create( &thread1, NULL, thread_server, &id1 );
	if ( result!=0 )  {
		perror( "Creating the first thread" );
		return EXIT_FAILURE;
	}
	sleep( 10 );
	cNet cliObj( (char*)"2" );

	while ( !isdown ) {
		sleep( 1 );
	}

	return 0;
}
