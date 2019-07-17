#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define NEW_LINE '\n'
#define BOLD_LINE_ON "\e[1m"
#define BOLD_LINE_OFF "\e[0m"

class Printer
{
private:
	boost::asio::io_context::strand strand_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	int count_;
public:
	Printer(boost::asio::io_context& io);
	void print1();
	void print2();
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
	strand_(io),
	timer1_(io, boost::posix_time::seconds(1)),
	timer2_(io, boost::posix_time::seconds(1)),
	count_(0)
{
	timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print1, this)));

	timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print2, this)));
}

void Printer::print1()
{
	if (count_ < 10)
	{
		std::cout << "Timer 1: " << count_ << std::endl;
		++count_;

		timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));

		timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print1, this)));
	}
}

void Printer::print2()
{
	if (count_ < 10)
	{
		std::cout << "Timer 2: " << count_ << std::endl;
		++count_;

		timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));

		timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print2, this)));
	}
}

Printer::~Printer()
{
	std::cout << "Final count is " << count_ << std::endl;
}