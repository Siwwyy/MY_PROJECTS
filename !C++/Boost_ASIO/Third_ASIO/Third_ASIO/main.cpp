#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define NEW_LINE '\n'
#define BOLD_LINE_ON "\e[1m"
#define BOLD_LINE_OFF "\e[0m"

																	//const pointer to not const int, with reference to avoid creating next instances of that pointer
void print(const boost::system::error_code& value, boost::asio::steady_timer* t, int *& const count)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);

		t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
		t->async_wait(boost::bind(print,boost::asio::placeholders::error, t, count));
	}
	else
	{
		constexpr __int16 seconds = 2;
		std::cout << BOLD_LINE_ON << "Prints function finished her work finally "<< BOLD_LINE_OFF << " Now timer waits " << seconds << NEW_LINE;
		t->expires_at(t->expiry() + boost::asio::chrono::seconds(seconds));
		t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
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

	std::cout << "Final count is " << count << NEW_LINE;
	std::cout << "Press enter to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}

//#include <iostream>
//#include <windows.h>
//
//std::ostream& bold_on(std::ostream& os)
//{
//	return os << "\e[1m";
//}
//
//std::ostream& bold_off(std::ostream& os)
//{
//	return os << "\e[0m";
//}
//
//
//int main()
//{
//	std::cout << bold_on << "bold" << bold_off << " non-bold" << std::endl;
//
//	system("pause");
//	return 0;
//}