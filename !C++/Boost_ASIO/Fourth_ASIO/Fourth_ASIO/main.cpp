#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define NEW_LINE '\n'
#define BOLD_LINE_ON "\e[1m"
#define BOLD_LINE_OFF "\e[0m"

class Printer
{
private:
	boost::asio::deadline_timer timer_;
	int count_;
public:
	Printer(boost::asio::io_context& io);
	void print();
	~Printer();
};

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	boost::asio::io_context io;
	Printer p(io);
	io.run();

	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
/*
	PRINTER CLASS CASE
*/
//////////////////////////////////////////////////
//////////////////////////////////////////////////


Printer::Printer(boost::asio::io_context& io) :
	timer_(io, boost::posix_time::seconds(1)),
	count_(0)
{
	timer_.async_wait(boost::bind(&Printer::print, this));
}

void Printer::print()
{
	if (count_ < 5)
	{
		std::cout << count_ << std::endl;
		++count_;

		timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
		timer_.async_wait(boost::bind(&Printer::print, this));
	}
}

Printer::~Printer()
{
	std::cout << "Final count is " << count_ << std::endl;
}