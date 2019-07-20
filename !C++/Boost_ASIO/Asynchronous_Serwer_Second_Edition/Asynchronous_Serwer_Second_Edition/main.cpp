#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

#define NEW_LINE '\n'
//#define _CRT_SECURE_NO_WARNINGS 1 


using boost::asio::ip::tcp;

std::string make_daytime_string();

class con_handler : public boost::enable_shared_from_this<con_handler>
{
private:
	tcp::socket sock;
	std::string message = "Hello From Server!";
	enum { max_length = 1024 };
	char data[max_length];

public:
	typedef boost::shared_ptr<con_handler> pointer;

	con_handler(boost::asio::io_service& io_service) :
		sock(io_service)
	{

	}
	// creating the pointer
	static pointer create(boost::asio::io_context& io_context)
	{
		return pointer(new con_handler(io_context));
	}
	//socket creation
	tcp::socket& socket()
	{
		return sock;
	}

	void start()
	{
		sock.async_read_some(	boost::asio::buffer(data, max_length),boost::bind(&con_handler::handle_read,shared_from_this(),boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));

		sock.async_write_some(boost::asio::buffer(message, max_length),boost::bind(&con_handler::handle_write,shared_from_this(),boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& err, size_t bytes_transferred)
	{
		if (!err)
		{
			std::cout << data << NEW_LINE;
		}
		else {
			std::cerr << "error: " << err.message() << std::endl;
			sock.close();
		}
	}
	void handle_write(const boost::system::error_code& err, size_t bytes_transferred)
	{
		if (!err) 
		{
			std::cout << "Server sent Hello message!" << NEW_LINE;
		}
		else 
		{
			std::cerr << "error: " << err.message() << NEW_LINE;
			sock.close();
		}
	}
};

class Server
{
private:
	tcp::acceptor acceptor_;
	boost::asio::io_context& io_context_;

	void start_accept()
	{
		// socket
		con_handler::pointer connection = con_handler::create(io_context_);

		// asynchronous accept operation and wait for a new connection.
		acceptor_.async_accept(connection->socket(),boost::bind(&Server::handle_accept, this, connection,boost::asio::placeholders::error));
	}
public:
	//constructor for accepting connection from client
	Server(boost::asio::io_context& io_context) :
		acceptor_(io_context, tcp::endpoint(tcp::v4(), 13)),
		io_context_(io_context)
	{
		start_accept();
	}
	void handle_accept(con_handler::pointer connection, const boost::system::error_code& err)
	{
		if (!err) 
		{
			connection->start();
		}
		start_accept();
	}
};

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;
	using boost::asio::ip::tcp;	//namespace for tcp


//	std::cout << argv[0] << ' ' << argv[1] << NEW_LINE;

	try
	{
		boost::asio::io_context io_context;
		Server server(io_context);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << endl;
	}



	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}
