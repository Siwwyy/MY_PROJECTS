#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/container/list.hpp>

#define NEW_LINE '\n'

void Show_Received_Message(const boost::system::error_code& error, const char * message, const _STD size_t & size)
{
	if (error)
	{
		_STD cout << error.message() << NEW_LINE;
	}
	else
	{
		_STD cout << message << NEW_LINE;
	}
}

//void Receive_Message(char* message, const size_t & size)
//{
//	std::cout << "HELLO" << NEW_LINE;
//	_STD cin >> message;
//}

int main(int argc, char* argv[])
{
	using _STD cout;
	using _STD endl;
	using _STD cin;
	using boost::asio::ip::tcp;

	try
	{
		boost::container::list<int> Clients;
		boost::asio::io_context io_context;
		//boost::asio::steady_timer timer(io_context, boost::asio::chrono::seconds(5));
		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));
		//io_context.run();
		for (;;)
		{
			tcp::socket socket(io_context);
			acceptor.accept(socket);

			const size_t message_size = 1024;
			char message[message_size] = {};
			//socket.read_some(boost::asio::buffer(message));
			socket.async_read_some(boost::asio::buffer(message), boost::bind(Show_Received_Message, boost::asio::placeholders::error,message, boost::ref(message_size)));
			_STD cout << "|-----------------------------------------------|" << NEW_LINE;
			Clients.push_back(socket.remote_endpoint().port());
			_STD cout << socket.remote_endpoint() << " connects to " << socket.local_endpoint() << NEW_LINE;
			_STD cout << message << NEW_LINE;
			_STD cout << "|-----------------------------------------------|" << NEW_LINE;
		}
	}
	catch (_STD exception& e)
	{
		_STD cerr << e.what() << _STD endl;
	}

	_STD cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}