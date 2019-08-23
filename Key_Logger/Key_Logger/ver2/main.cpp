




//#include "Email_Server.hpp"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>

void Send_Emailll(const char* server, const char* to, const char* from, const  char* subject, const char* message);


int main(int argc, char* argv[])
{
	const char * line = "WITAM";
	Send_Emailll("gmail-smtp-in.l.google.com", "andrydamian@gmail.com", "andrydamian@gmail.com", "logzz", line);

	system("pause");
	return 0;
}

void Send_Emailll(const char* server, const char* to, const char* from, const char* subject, const char* message)
{
	SOCKET sock{};
	WSADATA wsa_DATA{};
	hostent* host{};
	sockaddr_in destination{};
	int sent{};
	char line[200]{};

	//if (WSAStartup(0x202, &wsa_DATA) != SOCKET_ERROR)
	//{
	//	if ((host = gethostbyname(server)) != NULL)
	//	{
	//		//setting up the memory
	//		memset(&destination, 0, sizeof(destination));
	//		memset(&destination.sin_addr, host->h_addrtype, host->h_length);


	//		//preparing the destination
	//		destination.sin_family = host->h_addrtype;
	//		destination.sin_port = htons(25);

	//		//getting the socket
	//		sock = socket(AF_INET, SOCK_STREAM, 0);

	//		//connection
	//		connect(sock, (struct sockaddr*) & destination, sizeof(destination));

	//		//send command lines
	//		strcpy_s(line, 5, "NULL");
	//		sent = send(sock, line, strlen(line), 0);
	//		Sleep(500);
	//	}
	//}

	/*closesocket(sock);
	WSACleanup();*/
}
