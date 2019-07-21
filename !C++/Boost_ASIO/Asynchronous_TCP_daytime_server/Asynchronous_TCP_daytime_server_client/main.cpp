#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/container/list.hpp>

#define NEW_LINE '\n'
//#define _CRT_SECURE_NO_WARNINGS 1 


using boost::asio::ip::tcp;
using boost::lexical_cast;

std::string make_daytime_string();

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_context& io_context)
	{
		return pointer(new tcp_connection(io_context));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
	//	message_ = make_daytime_string();

		//boost::asio::async_write(socket_, boost::asio::buffer(message_),boost::bind(&tcp_connection::handle_write, shared_from_this(),boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
		//boost::asio::async_read(socket_, boost::asio::buffer(message_),boost::bind(&tcp_connection::handle_write, shared_from_this(),boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
		boost::asio::async_read(socket_, boost::asio::buffer(message_, message_.size()), (boost::bind(&tcp_connection::handle_read, shared_from_this(), boost::asio::placeholders::error)));
		_STD cout << "Message: " << this->message_ << NEW_LINE;
		message_ = "";
	}


	constexpr const std::string& Get_Message() const
	{
		return this->message_;
	}

private:
	tcp_connection(boost::asio::io_context& io_context)
		: socket_(io_context)
	{

	}

	void handle_write(const boost::system::error_code& e,
		size_t bytes_transferred)
	{
		//std::cout << "BYTES: " << bytes_transferred << NEW_LINE;
	}

	void handle_read(const boost::system::error_code& error)
	{
		//std::cout << "BYTES: " << bytes_transferred << NEW_LINE;

		if (!error)
		{
			boost::asio::async_read(socket_, boost::asio::buffer(message_, message_.size()), (boost::bind(&tcp_connection::handle_read, shared_from_this(), boost::asio::placeholders::error)));
		}
	}

	tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_context& io_context)
		: io_context_(io_context),
		acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
	{
		//static int a;
		std::cout << "WELCOME TO THE SIWY's SERVER!!" << NEW_LINE;
		start_accept();
	}

	~tcp_server()
	{
		Clients.clear();
	}

private:
	boost::container::list<tcp_connection::pointer> Clients;

	void start_accept()
	{
		tcp_connection::pointer new_connection = tcp_connection::create(io_context_);
		//Clients.push_back(new_connection);
		//_STD cout << "IP address: " << new_connection->Get_Message() << NEW_LINE;
		/*char a{};
		std::cin >> a;
		if (a == '1')
		{
			std::cout << "HEY SERWER" << NEW_LINE;
		}*/
		acceptor_.async_accept(new_connection->socket(),boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
			std::cout << "Welcome on the Serwer" << NEW_LINE;
			
		}

		start_accept();
	}

	boost::asio::io_context& io_context_;
	tcp::acceptor acceptor_;
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
		tcp_server server(io_context);
		io_context.run();
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
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}
