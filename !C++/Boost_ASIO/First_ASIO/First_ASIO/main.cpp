#include <iostream>
#include <string>
#include <windows.h>

#define NEW_LINE { '\n' }
#define BOLD { '\e' }

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	system("pause");
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