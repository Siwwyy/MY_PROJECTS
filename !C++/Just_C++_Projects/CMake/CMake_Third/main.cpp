#include <iostream>
#include <windows.h>
#include <string>
#include <typeinfo>

#define NEW_LINE '\n'

template<typename T, std::size_t N> 
constexpr std::size_t arraySize(T(&)[N]) noexcept;

template<typename Ty>
void foo(Ty& param);

int main(int argc, char* argv[])
{
	using _STD cout;
	using _STD cin;
	using _STD cerr;

	/*if (argc > 1)
	{
		return 1;
	}
*/
	//cout << "Hello Cmake Cross Platform Builder !" << NEW_LINE;
	int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };

	foo(keyVals);
	//cout << arraySize(keyVals) << NEW_LINE;

	system("pause");
	return 0;
}

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{
	return N;
}

template<typename Ty>
void foo(Ty& param)
{
	_STD cout << typeid(Ty).name() << NEW_LINE;
}