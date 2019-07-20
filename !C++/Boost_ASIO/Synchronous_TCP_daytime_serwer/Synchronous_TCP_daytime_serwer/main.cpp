#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>

#define NEW_LINE '\n'
//#define _CRT_SECURE_NO_WARNINGS 1 

std::string make_daytime_string();

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;
	using boost::asio::ip::tcp;	//namespace for tcp


//	std::cout << argv[0] << ' ' << argv[1] << NEW_LINE;

	try
	{
		// Any program that uses asio need to have at least one io_service object
		boost::asio::io_service io_service;

		// acceptor object needs to be created to listen for new connections
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		for (;;)
		{
			// creates a socket
			tcp::socket socket(io_service);

			// wait and listen
			acceptor.accept(socket);

			// prepare message to send back to client
			std::string message = make_daytime_string();

			boost::system::error_code ignored_error;

			// writing the message for current time
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}
			std::cout << 'D' << NEW_LINE;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}

std::string make_daytime_string()
{
	std::time_t now = std::time(0);
	return std::ctime(&now);
}
