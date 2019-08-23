
#include <iostream>
#include <functional>
#include <windows.h>

int main(int argc, char * argv[])
{
	
	[out = _STD ref(_STD cout << "Hello")](){ out.get() << " World\n";}();

	system("pause");
	return 0;
}