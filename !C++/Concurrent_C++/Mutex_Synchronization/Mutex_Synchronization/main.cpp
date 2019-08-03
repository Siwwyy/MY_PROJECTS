#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <thread>
#include <mutex>

#define NEW_LINE '\n'

_STD mutex mu;
//_STD unique_lock<_STD mutex> unique_mu(mu);

template<typename _Ty>
void printer(const _Ty & to_print);
void counter(int& value);
//void counter(int value);

int main(int argc, char* argv[])
{
	using std::endl;
	using std::cin;
	using std::cout;

	int count{-100};
	std::thread counter_thread(counter, _STD reference_wrapper<int>(count));

	//1* you can join counter thread here or
	if (counter_thread.joinable() == true)
	{
		counter_thread.join();
	}

	for (size_t i = 0; i < 100; ++i)
	{
		_STD lock_guard<_STD mutex> locker(mu);
		//mu.lock();
		printer(_STD string("From main -> "));
		printer(_STD reference_wrapper<size_t>(i));	//if u want increase 'i' in printer, you can do it
		//printer(i);
		printer("\n");
		//mu.unlock();
	}

	//1* or here you can join. this in this partucalr case doesn't matter
	//if (counter_thread.joinable() == true)
	//{
	//	counter_thread.join();
	//}

	_STD cout << typeid(count).name() << " count after multithreading counting upper -> " << count << NEW_LINE;

	system("pause");
	return 0;
}

template<typename _Ty>
void printer(const _Ty & to_print)
{
	//HERE IS A GOOD PLACE THO, BUT IF WE HAVE MORE PRINTS AT ONCE, WE NEED ADD LOCK MUTEX BEFORE FUNCTION IS INVOKED
	_STD cout << to_print;
}

void counter(int & value)
{
	for (size_t i = 0; i < 100; ++i)
	{
		//in this particular case when the exception will be thrown we are secure (ensure that when you are locking a mutex, maybe is a better possibility)
		_STD lock_guard<_STD mutex> locker(mu);
		//mu.lock(); //mu lock is good but in the case when functions below will throw an exception we will have a an eternal lock
		printer(_STD string("from counter -> "));
		printer(_STD reference_wrapper<int>(++value));//if u want increase 'value' additionally in printer, you can do it
		//printer(++value);
		printer("\n");
		//mu.unlock();
	}
}