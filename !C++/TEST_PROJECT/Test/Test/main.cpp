#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#define NEW_LINE '\n'


//class myclass {
//public:
//	constexpr size_t i;
//    myclass() :
//		i(2)
//    {        
//        int arr1[i] = { 1, 2 };
//
//        const size_t idx = 2;
//        int arr2[idx] { 1, 2 };
//    };
//
//	
//};


//GENERATOR LICZB PSEUDOLOSOWYCH
//
//unsigned long long m{};
//unsigned long long a{};
//unsigned long long c{};
//unsigned long long x{};

//void enigne(int a, int c);

//unsigned long long mult(unsigned long long a, unsigned long long  x, unsigned long long m)
//{
//	unsigned long long b, n, r;
//
//	r = 0;
//	n = 1;
//	b = 1;
//	while (n <= 64)
//	{
//		if ((a & b) != 0)
//		{
//			r = (r + x) % m;
//		}
//		x = (x + x) % m;
//		b *= 2;
//		n++;
//	}
//
//	return r;
//}
//
//unsigned long long genRand()
//{
//	x = (mult(a, x, m) + c) % m;
//	return x;
//}

class Generator
{
private:

	unsigned long long m;
	unsigned long long a;
	unsigned long long c;
	unsigned long long xi;
public:
	Generator():
		xi(0),
		m(4294967296),
		a(22695477),
		c(1)
	{

	}

	Generator(const int i):
		xi(i),
		m(4294967296),
		a(22695477),
		c(1)
	{

	}

	const float Get_Rand()
	{
		xi = (a * xi + c) % m;
		return float(xi) /(m - 1);
	}

	~Generator()
	{
		m = NULL;
		a = NULL;
		c = NULL;
		xi = NULL;
	}
};


class Histogram
{
private:
	int* Class_Amount;
	size_t counter;
	size_t array_size;
	float fClassWidth;
public:
	Histogram():
		counter(0),
		array_size(10),
		fClassWidth(1.0f/array_size)
	{
		Class_Amount = new int[10];
		for (size_t i = 0; i < array_size; ++i)
		{
			Class_Amount[i] = NULL;
		}
	}

	Histogram(const int amount):
		counter(0),
		array_size(amount),
		fClassWidth(1.0f / array_size)
	{
		Class_Amount = new int[amount];
		for (size_t i = 0; i < array_size; ++i)
		{
			Class_Amount[i] = NULL;
		}
	}

	void Add_Value(const float value)
	{
		int a = int(value / fClassWidth);
		//Class_Amount[counter] = a;
		//++counter;
		Class_Amount[a]++;
	}

	void Show_Graph()
	{
		for (size_t i = 0; i < array_size; ++i)
		{
			_STD cout << fClassWidth * i << " - " << fClassWidth * (i + 1) << " : ";
			/*for (int j = 0; j < Class_Amount[i]; ++j)
			{
				_STD cout << '#';
			}*/
			_STD cout << (int)Class_Amount[i] << NEW_LINE;
		}
	}

	~Histogram()
	{
		counter = NULL;
		array_size = NULL;
		delete[] Class_Amount;
	}
};

int main(int argc, char* argv[])
{/*
	const char str[] = { 'H','e','l','l','o', '\0' };
	const int nums[] = { 1,2,3,4,5 };
	_STD cout << &str << " | " << &nums << NEW_LINE;

	printf("%s | %p \n", str, nums);*/

	/*char c = 'a';
	char c1 = 'a';
	char c2 = c + c1;

	_STD cout << (int)c2 << _STD endl;
*/
	
	const size_t range{ 1000 };
	_STD vector<float> vec;
	Generator Obj;
	Histogram Object(10);
	for (size_t i = 0; i < range; ++i)
	{
		//_STD cout << Obj.Get_Rand() << ' ';
		float a = Obj.Get_Rand();
		vec.push_back(a);
		Object.Add_Value(a);
		//_STD cout << NEW_LINE;
	}
	Object.Show_Graph();

	float suma{};
	for (int i = 0; i < range; ++i)
	{
		suma += vec[i];
	}
	float y1 = suma / range;
	_STD cout << y1 << NEW_LINE;
	suma = 0;

	for (int i = 0; i < range; ++i)
	{
		suma += (vec[i]*vec[i]);
	}
	float y2 = suma / range;
	_STD cout << y2 << NEW_LINE;
	suma = 0;

	for (int i = 0; i < range; ++i)
	{
		suma += (vec[i] * vec[i] * vec[i]);
	}
	float y3 = suma / range;
	_STD cout << y3 << NEW_LINE;
	suma = 0;

	
	//_STD cout << Obj.Get_Rand() << NEW_LINE;
	system("pause");
	return 0;
}

//void enigne(int a, int c)
//{
//	int c{};
//
//	//c = 
//}
