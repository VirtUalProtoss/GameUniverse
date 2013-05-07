#include "cNet.h"

cNet::cNet() {
	cout << "cNet();" << endl;
	sAddr.sin_family=AF_INET;    // Семейство адресов, AF_xxx
	sAddr.sin_addr.s_addr = htonl( INADDR_ANY );
	sAddr.sin_port=htons( 5555 ); //порт

	sock[0] = socket (AF_INET, SOCK_STREAM, 0);
	bind(sock[0], ( struct sockaddr * )&sAddr, sizeof( sAddr ) );
	listen( sock[0], 8 );
	createServer();

}

cNet::cNet( char *mode ) {
	dbg=true;
	int iMode = *mode;
																								if ( dbg ) cout << "cNet(int mode[" << iMode << "]);"  << endl;
	if ( iMode == 1 ) {
																								if ( dbg ) cout << "mode 1" << endl;
		createServer();
	}
	if ( iMode == 2 ) {
		char str[20] = "Hello, World!!!";
		conn( ( char * )"" );
		sendData( str );
	}
}

void cNet::sendData( char *str ) {
	;
}

void cNet::conn( char *str ) {
	struct sockaddr_in addr;
	int csock = socket ( AF_INET, SOCK_STREAM, 0 );
	addr.sin_family = AF_INET;
	// TODO: remove hardcoded port value
	addr.sin_port = htons( 3425 );
	addr.sin_addr.s_addr = INADDR_ANY;
	if ( connect( csock, ( struct sockaddr * )&addr, sizeof( addr ) ) < 0 ) {
		perror( "connect" );
		exit( 2 );
	}
}

void cNet::acceptConnection( int *listener ) {
	struct sockaddr_in cAddr;
	int cAddrLen;
	// Поступил новый запрос на соединение, используем accept
	int sock = accept( *listener, (sockaddr *)&cAddr, (socklen_t *)&cAddrLen );
	if ( sock < 0 ) {
		perror( "accept" );
		exit( 3 );
	}
	//cout << "Client #" << (char *)sock << " with address: " << (char *)&cAddr << " connected." << endl;
	fcntl( sock, F_SETFL, O_NONBLOCK );
	clients[sock] = (char *)&cAddr;
}

int cNet::bindAddress( int *address, int *port ) {
	struct sockaddr_in addr;
	int listener;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = INADDR_ANY;
	listener = socket( AF_INET, SOCK_STREAM, 0 );
	if ( listener < 0 ) {
		perror( "socket" );
		exit( 1 );
	}
	if ( bind( listener, ( struct sockaddr * )&addr, sizeof( addr ) ) < 0 ) {
		perror( "bind" );
		exit( 2 );
	}
	return listener;
}

void cNet::createServer() {
	int address = 0;
	int port = 3425;
	int listener = bindAddress( &address, &port );
	char buf[1024];
	int bytes_read;

	fcntl( listener, F_SETFL, O_NONBLOCK );
	listen( listener, 2 );

	clients.clear();

	// Задаём таймаут
	timeval timeout;
	timeout.tv_sec = 150000;
	timeout.tv_usec = 0;

	while ( 1 ) {
		// Заполняем множество сокетов
		fd_set readset;
		FD_ZERO( &readset );
		FD_SET( listener, &readset );

		for ( map<int, char*>::iterator it = clients.begin(); it != clients.end(); it++ )
			FD_SET( (*it).first, &readset );

		// Ждём события в одном из сокетов
		int mx = max( listener, (*max_element( clients.begin(), clients.end() )).first );

		if ( select( mx + 1, &readset, NULL, NULL, &timeout ) <= 0 ) {
			perror( "select" );
			exit( 3 );
		}

		// Определяем тип события и выполняем соответствующие действия
		if ( FD_ISSET( listener, &readset ) )
			acceptConnection( &listener );

		for ( map<int, char*>::iterator it = clients.begin(); it != clients.end(); it++ ) {
			if ( FD_ISSET( (*it).first, &readset ) ) {

				// Поступили данные от клиента, читаем их
				bytes_read = recv( (*it).first, buf, 1024, 0 );

				if ( bytes_read <= 0 )	{
					// Соединение разорвано, удаляем сокет из множества
					close( (*it).first );
					clients.erase( it );
					cout << "Closing connection: " << (*it).first << endl;
					continue;
				}

				checkCommand( buf, it );

				// Отправляем данные обратно клиенту
				send( (*it).first, buf, bytes_read, 0 );
			}
		}
	}
}

void cNet::checkCommand( char *str, map<int, char*>::iterator itc ) {
	cout << "str: " << str << endl;

	//for ( map<int, char*>::iterator it = clients.begin(); it != clients.end(); it++ ) {

		if ( !strcmp( str, "quit\r\n" ) ) exit( 0 );
		if ( !strcmp( str, "whoame\r\n" ) )	cout << "client is: " << (*itc).second << endl;

		if ( !strcmp( str, "get\r\n" ) ) {
			cout << (*itc).first << endl;
			send( (*itc).first, str, strlen( str ), 0 );
		}

		if ( !strcmp( &str[0], "/" ) ) {
			cout << "command is: " << str << endl;
			send( (*itc).first, (*itc).second, strlen( str ), 0 );
		}

	//}
}
