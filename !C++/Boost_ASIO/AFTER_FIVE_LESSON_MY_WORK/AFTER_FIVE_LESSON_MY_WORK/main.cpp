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

class My_Class
{
private:
	boost::asio::io_context::strand strand;
	boost::asio::deadline_timer timer1;
	boost::asio::deadline_timer timer2;
	boost::asio::steady_timer timer3;
	__int64 counter;
public:
	My_Class(boost::asio::io_context& io);
	
	void Multiply_Counter(const int multiply_by);
	void Divide_Counter(const int divide_by);

	void Print();

	~My_Class();
};

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	boost::asio::io_context io;
	My_Class Object(io);
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


My_Class::My_Class(boost::asio::io_context& io):
	strand(io),
	timer1(io, boost::posix_time::seconds(1)),
	timer2(io, boost::posix_time::seconds(1)),
	timer3(io, boost::asio::chrono::seconds(1)),
	counter(2)
{
	timer1.async_wait(boost::asio::bind_executor(strand, boost::bind(&My_Class::Multiply_Counter,this, counter)));
	//timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&My_Class::Divide_Counter, boost::asio::placeholders::error)));
	timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&My_Class::Divide_Counter,this ,counter)));
	//t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));
	timer3.async_wait(boost::bind(&My_Class::Print, this));
}

void My_Class::Multiply_Counter(const int multiply_by)
{
	std::cout << "MULTI " << counter << ' '  << multiply_by << NEW_LINE;
	this->counter *= multiply_by;
	if (counter > 999999)
	{
		this->counter /= multiply_by;
	}
	timer1.expires_at(timer1.expires_at() + boost::posix_time::seconds(1));
	timer1.async_wait(boost::asio::bind_executor(strand, boost::bind(&My_Class::Multiply_Counter, this, counter)));
}

void My_Class::Divide_Counter(const int divide_by)
{
	std::cout << "DIVIDI " << counter << ' ' << divide_by << NEW_LINE;
	this->counter /= divide_by; 
	//if (counter < 2)
	//{
	//	counter = 2;
	//}
//	std::cin.get();
	timer2.expires_at(timer2.expires_at() + boost::posix_time::seconds(1));
	timer2.async_wait(boost::asio::bind_executor(strand, boost::bind(&My_Class::Divide_Counter, this, counter)));
}

void My_Class::Print()
{
	//std::cout << this->counter << NEW_LINE;
	timer3.expires_at(timer3.expires_at() + boost::asio::chrono::seconds(1));
	timer3.async_wait(boost::bind(&My_Class::Print, this));
}

My_Class::~My_Class()
{
	strand.~strand();
}
