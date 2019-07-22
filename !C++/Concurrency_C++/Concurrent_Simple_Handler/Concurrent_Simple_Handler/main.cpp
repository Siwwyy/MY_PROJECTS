#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>

#include "_HANDLER.hpp"

void fun();

int main(int argc, char* argv[])
{
	using std::endl;
	using std::cin;
	using std::cout;
	using MY_HANDLE::_HANDLER;

	//	  Address of fun	Address of pointer to fun	Address of fun
	//_STD cout << ptr_fun << ' ' << &ptr_fun << ' ' << *ptr_fun << NEW_LINE;
	_HANDLER<void(*)()> Test(fun);
	Test.Join_Synchronously();
	//_HANDLER<void(*)()> Test1(std::move(Test));
	//_HANDLER<void> Test(fun);
	//_HANDLER<void()> Test(&fun);
	//_STD cout << Test.Get_Pointer_To_Handler() << NEW_LINE;
	_STD cout << Test.Get_Reference_To_Handler() << NEW_LINE;
	//_STD cout << Test1.Get_Reference_To_Handler() << NEW_LINE;
	//(Test.Get_Reference_To_Handler())();
	//void(*ptr_fun)() = Test.Get_Reference_To_Handler();
	//_STD cout << ptr_fun << ' ' << &ptr_fun << ' ' << *ptr_fun << NEW_LINE;
	_STD cout << &fun << NEW_LINE;
	//(*ptr_fun)();
	system("pause");
	return 0;
}

void fun()
{
	//__int64 a = 0;
	//for (size_t i = 0; i < 1000000000; ++i)
	//{
	//	a += 1;
	//}
	//_STD cout << NEW_LINE;
	_STD cout << "HELLO WORD" << NEW_LINE;
	//return 0;
}
