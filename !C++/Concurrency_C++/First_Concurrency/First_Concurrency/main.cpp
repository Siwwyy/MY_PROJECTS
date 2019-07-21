#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>

#define NEW_LINE '\n'

void show_fun(const char * to_show);
void foo();

int main(int argc, char* argv[])
{
	using std::endl;
	using std::cin;
	using std::cout;

	//_STD cout << _STD thread::hardware_concurrency() << NEW_LINE; //in my computer is 8

	const char* value = "CONCURRENCY";

	std::thread foo_thread(foo);
	foo_thread.join();

	std::thread fun_log_thread(show_fun, value);
	fun_log_thread.detach();

	//if you uncomment this three sections below you will se funny behavior
	//_STD cout << std::this_thread::get_id() << NEW_LINE;
	//_STD cout << foo_thread.get_id() << NEW_LINE;
	//_STD cout << fun_log_thread.get_id() << NEW_LINE;

	system("pause");
	return 0;
}

void show_fun(const char* to_show)
{
	printf_s("-------------------------------- \n");
	printf_s("Show fun thread\n");
	printf_s("%s \n", to_show);
	__int64 value = 1;
	for (size_t i = 0; i < 10; ++i)	//set this 10 value to other value to purpose of checking behavior multithread program
	{
		value *= 2;
	}
	printf_s("%d \n", value);
	printf_s("-------------------------------- \n");
}

void foo()
{
	printf_s("-------------------------------- \n");
	printf_s("foo thread\n");
	_STD cout << "HELLO WORLD" << NEW_LINE;
	printf_s("-------------------------------- \n");
}
