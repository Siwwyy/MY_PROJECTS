#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define NEW_LINE '\n'
#define BOLD_LINE '\e'


void print(const boost::system::error_code& /*e*/, boost::asio::steady_timer* t, int* count)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);

		t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
		t->async_wait(boost::bind(print,boost::asio::placeholders::error, t, count));
	}
}

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	boost::asio::io_context io;

	int count = 0;
	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
	t.async_wait(boost::bind(print,boost::asio::placeholders::error, &t, &count));

	io.run();

	std::cout << "Final count is " << count << std::endl;

	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}