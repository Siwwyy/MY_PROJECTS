#include <iostream>
#include <windows.h>
#include <string>

#define NEW_LINE '\n'

int main(int argc, char* argv[])
{
	using _STD cout;
	using _STD cin;
	using _STD cerr;

	if (argc > 1)
	{
		return 1;
	}

	cout << "Hello Cmake Cross Platform Builder !" << NEW_LINE;

	system("pause");
	return 0;
}