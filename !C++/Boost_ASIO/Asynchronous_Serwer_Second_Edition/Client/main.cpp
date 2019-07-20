#include <iostream>
#include <boost/asio.hpp>

#define NEW_LINE '\n'

using namespace boost::asio;


int main(int argc, char * argv[])
{
	using ip::tcp;
	using std::string;
	using std::cout;
	using std::endl;

	boost::asio::io_service io_service;
	//socket creation
	tcp::socket socket(io_service);
	//connection
	socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 13));
	// request/message from client

	const string msg = "Hello from Client!\n";
	boost::system::error_code error;
	boost::asio::write(socket, boost::asio::buffer(msg), error);

	if (!error) 
	{
		cout << "Client sent hello message!" << NEW_LINE;
	}
	else 
	{
		cout << "send failed: " << error.message() << NEW_LINE;
	}
	// getting response from server
	boost::asio::streambuf receive_buffer;
	boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
	if (error && error != boost::asio::error::eof) 
	{
		cout << "receive failed: " << error.message() << NEW_LINE;
	}
	else 
	{
		const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
		cout << data << NEW_LINE;
	}
	return 0;
}