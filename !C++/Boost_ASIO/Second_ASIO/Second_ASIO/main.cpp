#include <iostream>
#include <string>
#include <boost/asio.hpp>

#define NEW_LINE '\n'
#define BOLD '\e'

void print(const boost::system::error_code& value)
{
	std::cout << "Hello, world!" << NEW_LINE;
}

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;


	boost::asio::io_context io;

	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
	t.async_wait(&print);
	//t.wait();
	//print(boost::system::error_code());
	io.run();
	//system("pause");
	std::cout << "Press space to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}