#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

#include "Algorithms_Library.hpp"

using namespace std;

int main(int argc, char * argv[])
{
	//std::vector<int> a();
	//int a = 5;
	//int b = 4;
	//a ^= b;
	//b ^= a;
	//b = a;
	//a = b;
	using Algorithms::Bubble_Sort;
	using Algorithms::Shake_Sort;
	const size_t size = 5;
	int tab[size] = { 5,7,2,3,8 };
	Shake_Sort(tab, size);
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << tab[i] << ' ';
	}
	std::cout << endl;
	//std::cout << a << ' ' << b << endl;
	system("pause");
	return 0;
}