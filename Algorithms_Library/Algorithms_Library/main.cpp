#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

#include "Algorithms_Library.hpp"

using namespace std;

const bool comparator(const void * left, const void * right)
{
	int l = *(const int *)left;
	int r = *(const int *)right;
	if (l < r)
	{
		return true;
	}
	return false;
}

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
	using Algorithms::Euqlides_Algorithm;
	using Algorithms::Quick_Sort;
	using Algorithms::Linear_Serach;
	using Algorithms::Binary_Serach;
	/*const size_t size = 8;
	int tab[size] = { 5,7,2,3,8,20,-2,4 };
	Shake_Sort(tab, size, comparator);
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << tab[i] << ' ';
	}*/
	//std::cout << endl;
	//std::cout << a << ' ' << b << endl;
	//__int64 a = 12, b = 18;
	//std::cout << a << ' ' << b << endl;
	//std::cout << Euqlides_Algorithm(a,b) << endl;
	char  name[] = "Damian";
	//std::cout << name[4];
	//std::cout << Linear_Serach(name, 7, 'n');
	std::cout << Binary_Serach(name, 6, 'n');
	system("pause");
	return 0;
}