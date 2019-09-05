#include <iostream>
#include <string>
#include <windows.h>

#define NEW_LINE '\n'

int main(int argc, char* argv[])
{
	const char str[] = { 'H','e','l','l','o', '\0' };
	const int nums[] = { 1,2,3,4,5 };
	_STD cout << &str << " | " << &nums << NEW_LINE;

	printf("%s | %p \n", str, nums);

	system("pause");
	return 0;
}