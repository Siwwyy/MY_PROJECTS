#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#define NEW_LINE '\n'

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(socket_ptr sock)
{
	try
	{
		for (;;)
		{
			char data[max_length];

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(data), error);
			if (error == boost::asio::error::eof)
			{
				_STD cout << "Connection complete" << NEW_LINE;
				break; // Connection closed cleanly by peer.
			}
			else if (error)
			{
				throw boost::system::system_error(error); // Some other error.
			}
			boost::asio::write(*sock, boost::asio::buffer(data, length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(session, sock));
	}
}


int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;
	using boost::asio::ip::tcp;	//namespace for tcp

	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
			std::cin.get();
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		server(io_service, atoi(argv[1]));
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}


	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}