#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#define NEW_LINE '\n'
#define VECTOR_TYPE __int32

_STD vector<VECTOR_TYPE> my_vector;
_STD mutex mu_locker;
_STD condition_variable cond_variable;

void add_to_vector();
void print_value_from_vector();
//void print_value_from_vector(const size_t begin_index, const size_t end_index);

int main(int argc, char* argv[])
{
	using std::endl;
	using std::cin;
	using std::cout;

	std::thread add_to_vector_thread(add_to_vector);
	std::thread print_value_from_vector_thread(print_value_from_vector);
	add_to_vector_thread.join();
	print_value_from_vector_thread.join();

	system("pause");
	return 0;
}

void add_to_vector()
{
	__int32 counter{10};
	while (counter >= 0)
	{
		std::unique_lock<_STD mutex> locker(mu_locker);
		_STD cout << "Add To Vector" << NEW_LINE;
		my_vector.emplace_back(counter);
		locker.unlock();
		cond_variable.notify_one();  // Notify one waiting thread, if there is one.
		_STD this_thread::sleep_for(_STD chrono::seconds(1));
		--counter;
	}
}

void print_value_from_vector()
{
	__int32 value_from_vec{};
	while (value_from_vec != 1)
	{
		std::unique_lock<_STD mutex> locker(mu_locker);
		cond_variable.wait(locker, []() { return !my_vector.empty(); });  // Unlock mu and wait to be notified
		value_from_vec = my_vector.back();
		my_vector.pop_back();
		_STD cout << "Print value from Vector: " << value_from_vec << NEW_LINE;
		locker.unlock();
	}
	_STD cout << "\nEND" << NEW_LINE;
}