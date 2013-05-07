#ifndef _C_NET_H_
#define _C_NET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include <algorithm>
//#include <set>
#include <map>

#include <iostream>
#include <cstring>

using namespace std;


class cNet {
	public:
		cNet();
		cNet( char* mode );
	protected:

	private:
		int sock[8];
		bool dbg;
		//set<int> clients;
		map<int, char*> clients;
		void createServer();
		void conn(char *str);
		void sendData(char *str);
		struct sockaddr_in sAddr;
		void checkCommand(char *str, map<int, char*>::iterator itc);
		void acceptConnection( int *listener );
		int bindAddress( int *address, int *port );
};

#endif // _C_NET_H_
