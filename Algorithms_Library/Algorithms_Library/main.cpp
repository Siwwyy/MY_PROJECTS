#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

#include "Algorithms_Library.hpp"

using namespace std;
using namespace Algorithms;
using namespace Algorithms::Algorithms_Hash_Table;
using namespace Algorithms::Algorithms_Heap_Sort;
//using namespace Algorithms::

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
void inserter_MST(const std::string & file_in_path);

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
	//inserter_HEAP_SORT("heapsort.in");
	inserter_MST("heapsort.in");
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
	file_out.open("temp_Hash_Table.out", std::ios_base::out);
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
						//Object.show_elements(); //uncomment
						Object.show_elements(file_out); //uncomment
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
	std::fstream file_out;
	__int64 N = 0;
	__int64 number_amount = 0;
	__int32 data_reader = 0;
	file_in.open(file_in_path.c_str(), std::ios_base::in);
	file_out.open("temp_Heap_Sort.out", std::ios_base::out);
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
			Algorithms::Algorithms_Heap_Sort::Heap_Sort<int, NULL> * Object = new Algorithms::Algorithms_Heap_Sort::Heap_Sort<int, NULL>(number_amount);
			while (number_amount > 0)
			{
				file_in >> data_reader;
				Object->push(data_reader);
				data_reader = 0;
				number_amount--;
			}
			Object->Start_Sorting();
			//Three types of Out
			//To file
			Object->Show_Heap_Array(file_out);
			Object->End_Sorting(file_out);
			Object->Show_Heap_Sorted(file_out);
			//To console out
			//Object->Show_Heap_Array(std::cout);
			//Object->End_Sorting(std::cout);
			//Object->Show_Heap_Sorted(std::cout);
			//To typical out console
			//Object->Show_Heap_Array(std::cout);
			//Object->End_Sorting(std::cout);
			//Object->Show_Heap_Sorted(std::cout);
			delete Object;
			N--;
			number_amount = 0;
		}
	}
	file_in.close();
	file_out.close();
}

void inserter_MST(const std::string& file_in_path)
{
	std::fstream file_in;
	std::fstream file_out;
	__int16 m = 0;			//amount of cities
	__int16 d = 0;			//amount of ways
	__int32 c1 = 0;			//number of city
	__int32 c2 = 0;			//number of city
	__int32 p = 0;			//amount of max passengers between one course
	__int32 s = 0;			//the beginning of way
	__int32 e = 0;			//the end of way
	__int32 t = 0;			//amount of max passengers to move by bus
	file_in.open(file_in_path.c_str(), std::ios_base::in);
	file_in.open("temp_MST.out", std::ios_base::out);
	if (file_in.good() == false)
	{
		exit(0);
	}
	else
	{
		while (true)
		{
			file_in >> m;
			file_in >> d;
			MST * MST_Object = new MST(m);
			while (d > 0)
			{
				file_in >> c1;
				file_in >> c2;
				file_in >> p;
				//both times cause each road is in both ways
				MST_Object->push(c1, c2, (-1) * p);
				MST_Object->push(c2, c1, (-1) * p);
				--d;
				c1 = 0;
				c2 = 0;
				p = 0;
			}
			while (true)
			{
				file_in >> s;
				file_in >> e;
				if (s != 0 && e != 0)
				{
					file_in >> t;
					MST_Object->push_directions(s, e, t);
				}
				else
				{
					//here call all needed functions for solve the problem cause if s and e will be equal to 0 problem will be stopped immediately
					///////////////////////////////////////////////
					MST_Object->get_results();
					///////////////////////////////////////////////
					delete MST_Object;
					system("pause");
					exit(0);
				}
				s = 0;
				e = 0;
				t = 0;
			}
			d = 0;
			m = 0;
		}
	}
	file_in.close();
	file_out.close();
}
