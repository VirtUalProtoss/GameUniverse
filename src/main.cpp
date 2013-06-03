#include <iostream>
#include "ogreApplication.h"
#include <pthread.h>
#include "ClientSocket.h"
#include <string.h>

using namespace std;

void * clientSocket(void * arg) {
    // socket connection to game server
    ClientSocket* sock = new ClientSocket( "127.0.0.1", 50000 );
    string msg = "Hello server!";
    sock->send( msg );
}

void * graphicsClient(void * arg) {
    ogreApplication* ogre = new ogreApplication();
	arg = (int *) ogre->run();
}

int main(int argc, char **argv) {
    // TODO: move threads create to GameCommon library 
    // in interface for multiplatform
	pthread_t threadSocket, threadOgre;
    int resultSocket, resultOgre, threadOgreResult, threadSocketResult;
    resultOgre = pthread_create(&threadOgre, NULL, graphicsClient, &threadOgreResult);
    //resultSocket = pthread_create(&threadSocket, NULL, clientSocket, &threadSocketResult);
    
    resultOgre = pthread_join(threadOgre, NULL);
};
