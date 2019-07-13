#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

#include "Algorithms_Library.hpp"
#include "Algorithms_Library.hpp"

using namespace std;
using namespace Algorithms;
using namespace Algorithms::Algorithms_Hash_Table;
using namespace Algorithms::Algorithms_Heap_Sort;

//const bool comparator(const void * left, const void * right)
//{
//	int l = *(const int *)left;
//	int r = *(const int *)right;
//	if (l < r)
//	{
//		return true;
//	}
//	return false;
//}

void inserter_HASH_TABLE(const std::string & file_in_path);
void inserter_HEAP_SORT(const std::string & file_in_path);

int main(int argc, char * argv[])
{
	//std::vector<int> a();
	//int a = 5;
	//int b = 5;
	//decltype(b) c = 5;
	//std::cout << typeid(c).name() << endl;
	////a ^= b;
	////b ^= a;
	////b = a;
	////a = b;
	//std::cout << std::boolalpha << (a == b) << std::endl;
	using Algorithms::Bubble_Sort;
	using Algorithms::Shake_Sort;
	using Algorithms::Euqlides_Algorithm;
	using Algorithms::Quick_Sort;
	using Algorithms::Linear_Serach;
	using Algorithms::Binary_Serach;
	//inserter_HASH_TABLE("hashtable.in");
	inserter_HEAP_SORT("heapsort.in");
	system("pause");
	return 0;
}


void inserter_HASH_TABLE(const std::string & file_in_path)
{
	std::fstream file_in;
	std::fstream file_out;
	std::string data_reader = "";		//czyta dane z pliku
	std::string Value = "";
	__int64 Element_Key = 0;
	size_t Element_Key_Delete = 0;
	file_in.open(file_in_path.c_str(), std::ios_base::in);
	file_out.open("temp.out", std::ios_base::out);
	if (file_in.good() == false)
	{
		exit(0);
	}
	else
	{
		file_in >> data_reader;
		unsigned int loop_range = static_cast<unsigned int>(stoi(data_reader));
		for (unsigned int i = 0; i < loop_range; ++i)
		{
			file_in >> data_reader;
			if (data_reader == "size")
			{
				file_in >> data_reader;
				const unsigned int object_array_size = static_cast<unsigned int>(stoi(data_reader));
				Algorithms::Algorithms_Hash_Table::Hash_Table<std::string, NULL> Object;
				Object.resize_array(object_array_size);
				while (true)
				{
					file_in >> data_reader;
					if (data_reader == "add")
					{
						file_in >> Element_Key;
						file_in >> Value;
						Object.push(Value, Element_Key);
					}
					else if (data_reader == "print")	//print
					{
						//three types of out
						Object.show_elements(); //uncomment
						//Object.show_elements(file_out); //uncomment
						//Object.show_elements(std::cout); //uncomment
					}
					else if (data_reader == "delete")	//delete
					{
						file_in >> Element_Key_Delete;
						Object.delete_element(Element_Key_Delete);
					}
					else if (data_reader == "stop")		//stop
					{
						break;
					}
					data_reader = "";
					Value = "";
					Element_Key = 0;
				}
			}
		}
		file_in.close();
		file_out.close();
	}
}

void inserter_HEAP_SORT(const std::string & file_in_path)
{
	std::fstream file_in;
	__int64 N = 0;
	__int64 number_amount = 0;
	__int32 data_reader = 0;
	file_in.open(file_in_path.c_str(), std::ios_base::in);
	if (file_in.good() == false)
	{
		exit(0);
	}
	else
	{
		file_in >> N;
		while (N > 0)
		{
			file_in >> number_amount;
			//std::cout << &number_amount << endl;
			Algorithms::Algorithms_Heap_Sort::Heap_Sort<int, NULL> * Object = new Algorithms::Algorithms_Heap_Sort::Heap_Sort<int, NULL>(number_amount);
			while (number_amount > 0)
			{
				file_in >> data_reader;
				Object->push(data_reader);
				data_reader = 0;
				number_amount--;
			}
			Object->Show_Heap_Array();
			Object->Start_Sorting();
			Object->Show_Heap_Array();
			Object->End_Sorting();
			Object->Show_Heap_Sorted();
			delete Object;
			N--;
			number_amount = 0;
		}
	}
	file_in.close();
}
