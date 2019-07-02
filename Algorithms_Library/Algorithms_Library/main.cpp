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
	using Algorithms::Linear_Serach;
	using Algorithms::Quick_Sort;
	const size_t size = 5;
	int tab[size] = { 5,7,2,3,8 };
	Quick_Sort(tab, 0, size - 1,&comparator);
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << tab[i] << ' ';
	}
	//std::cout << endl;
	//std::cout << a << ' ' << b << endl;
	//__int64 a = 12, b = 18;
	//std::cout << a << ' ' << b << endl;
	//std::cout << Euqlides_Algorithm(a,b) << endl;
	//std::string name = "Damian";
	//std::cout << Linear_Serach(name, name.size(), 'n');
	system("pause");
	return 0;
}