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
		/*if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << NEW_LINE;
			return 1;
		}
*/
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query("localhost", "13");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		for (;;)
		{
			int option{};
			_STD cout << "MAIN MENU" << endl;
			_STD cout << "-----------------------------------" << endl;
			_STD cout << "1. Send a message to the server" << NEW_LINE;
			_STD cout << "4. Exit" << NEW_LINE;
			cout << "Choose: " << endl;
			std::cin >> option;
			if (option == 1)
			{
				_STD cout << "Type a message (then press enter): " << NEW_LINE;
				std::string message{};
				//std::getline(_STD cin, message);
				cin >> message;
				std::cin.get();
				message += '\0';
				std::cout << "Your message: " << message << NEW_LINE;
				boost::asio::connect(socket, endpoint_iterator);

				socket.write_some(boost::asio::buffer(message));
				//socket.send(boost::asio::buffer(message));
				socket.close();
			}
			else if (option == 4)
			{
				break;
			}
			else
			{
				break;
			}
		}
		// The connection is open.
	/*	for (;;)
		{
			std::string message{};
			std::getline(_STD cin, message);
			boost::system::error_code error;
			socket.write_some(boost::asio::buffer(message));
		}*/
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