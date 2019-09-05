#include <iostream>
#include <windows.h>
#include <string>
#include <List>
#include <vector>
//#define _DEBUG
//#include <corecrt_malloc.h>

//using namespace std;

//#include "List.hpp"
#include "Stack.hpp"

int main(int argc, char * argv[])
{
	
	MyStack::Stack<int> Stack;
	
	for (size_t i = 0; i <= 9; ++i)
	{
		Stack.push(i);
	}
	//MyStack::Stack<int> Stack1(Stack);
	//Stack.Clear_Stack();
	//std::cout << Stack.get_size();
	//std::cin.get();
	for (size_t i = 0; i < 9; ++i)
	{
		std::cout << Stack.pop() << ' ';
		//std::cout << Stack1.pop() << ' ';
	}
	system("pause");
	return EXIT_SUCCESS;
}