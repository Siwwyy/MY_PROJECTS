#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#define NEW_LINE '\n'


int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;
	using boost::asio::ip::tcp;	//namespace for tcp


//	std::cout << argv[0] << ' ' << argv[1] << NEW_LINE;

	const size_t message_size = 1024;
	
	

	/*std::cout << message << NEW_LINE;
	std::cin.get();*/

	try
	{
		// the user should specify the server - the 2nd argument
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << NEW_LINE;
			return 1;
		}

		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], "13");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		
		// The connection is open.
		for (;;)
		{
			std::string message{};
			std::getline(_STD cin, message);
			boost::system::error_code error;
			socket.send(boost::asio::buffer(message));
			//if (error == boost::asio::error::eof)
			//{
			//	break; // Connection closed cleanly by peer.
			//}
			//else if (error)
			//{
			//	throw boost::system::system_error(error); // Some other error.
			//}
		//	for(size_t i = 0; )
		}
	}
	// handle any exceptions that may have been thrown.
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}