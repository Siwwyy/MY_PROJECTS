//STEADY TIMER!

#include <iostream>
#include <string>
//#include <windows.h>	//struggle between asio and windows dot h
#include <boost/asio.hpp>

#define NEW_LINE '\n'
#define BOLD_LINE '\e'

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;


	boost::asio::io_context io;

	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
	t.wait();
	std::cout << "Hello, world!" << NEW_LINE;
	//system("pause");
	std::cout << "Press space to close the window..." << NEW_LINE;
	cin.get();
	return 0;
}

/*
For example, in Window's console, there's no way to write a text in bold.
If you're using Linux/Unix, then, in most terminal emulators and in virtual 
console, you can write your string in bold, and even choose the color for it,
just by adding \e[1m before your string, and \e[0m after your string to make 
sure that the other strings will be not bold.

char esc_char = 27; // the decimal code for escape character is 27
cout << esc_char << "[1m" << "Hello Bold!" << esc_char << "[0m" << endl;

*/