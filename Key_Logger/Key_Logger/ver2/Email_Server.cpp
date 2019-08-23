//#include "Email_Server.hpp"
//
//
//
//void Server::Email_Server::Send_Email()
//{
//	int sent{};
//	char line[200]{};
//
//	if (WSAStartup(0x202, &this->wsa_DATA) != SOCKET_ERROR)
//	{
//		if ((host = gethostbyname(this->server)) != NULL)
//		{
//			//setting up the memory
//			memset(&this->destination, 0, sizeof(this->destination));
//			memset(&this->destination.sin_addr, this->host->h_addrtype, this->host->h_length);
//
//
//			//preparing the destination
//			this->destination.sin_family = this->host->h_addrtype;
//			this->destination.sin_port = htons(25);
//
//			//getting the socket
//			this->sock = socket(AF_INET, SOCK_STREAM, 0);
//
//			//connection
//			connect(this->sock, (struct sockaddr*)&this->destination, sizeof(this->destination));
//
//			//send command lines
//			strcpy_s(line, 5, "NULL");
//			sent = send(this->sock, line, strlen(line), 0);
//			Sleep(500);
//		}
//	}
//
//	closesocket(this->sock);
//	WSACleanup();
//}
//
//Server::Email_Server::Email_Server() :
//	message("NOTHING HERE")
//{
//	this->server = new char[5];
//	strcpy_s(server, 5, "NULL");
//}
//
//Server::Email_Server::Email_Server(const::std::string& message):
//	message(message)
//{
//
//}
//
//Server::Email_Server::~Email_Server()
//{
//	delete[] this->server;
//}