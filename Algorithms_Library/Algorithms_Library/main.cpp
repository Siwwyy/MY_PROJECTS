#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>


#include "Algorithms_Library.hpp"
#include "Hash_Table.hpp"

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

void inserter(const std::string & file_in_path);

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
	Algorithms_Hash_Table::Hash_Table<std::string, 10> HT;
	inserter("hashtable.in");
	//system("pause");
	//std::string a = "dasd";
	//const_char_astrix_10 hehe;
	//hehe.push("ddswd", 12);
	/*HT.push("ddswd",12);
	HT.push("ddsd",13);
	HT.push("ddwssdd",14);
	HT.push("ddds",11);
	HT.push("ddsdasddd",10);
	HT.push("de123dd",25);
	HT.push("dddqwed",36);
	HT.push("ddd13d",37);
	HT.push("ddcgg57765rgd",138);
	HT.push("ddcggrgd",69);
	HT.show_object();
	system("pause");*/
	//Algorithms_Hash_Table::Hash_Table<int, 20> HT3;
	///*HT3.push(1, 12);
	//HT3.push(2, 142);
	//HT3.push(3, 32);
	//HT3.push(3, 382);
	//HT3.push(2, 128);
	//HT3.push(3, 4472);
	//HT3.push(4, 172);
	//HT3.push(5, 152);
	//HT3.push(6, 162332);
	//HT3.push(7, 162);
	//HT3.push(1, 12);
	//HT3.push(2, 142);
	//HT3.push(3, 32);
	//HT3.push(3, 382);
	//HT3.push(2, 128);
	//HT3.push(3, 4472);
	//HT3.push(4, 172);
	//HT3.push(5, 152);
	//HT3.push(6, 162332);
	//HT3.push(7, 162);
	//HT3.show_object();*/
	//Algorithms_Hash_Table::Hash_Table<std::string, 20> HT1;
	//Algorithms_Hash_Table::Hash_Table<int, 20> HT2(HT3);
	/*HT = HT2;
	std::cout << HT.Get_Hash_Table_Size();*/
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
	//const char  name[] = "Damian";
	////std::cout << name[4];
	////std::cout << Linear_Serach(name, 7, 'n');
	//std::cout << Binary_Serach(const_cast<char *>(name), 6, 'n');
	system("pause");
	return 0;
}


void inserter(const std::string & file_in_path)
{
	std::fstream file_in;
	std::string data_reader = "";		//czyta dane z pliku
	std::string Value = "";
	__int64 Element_Key = 0;
	size_t Element_Key_Delete = 0;
	file_in.open(file_in_path.c_str(), std::ios_base::in);
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
				unsigned int object_array_size = static_cast<unsigned int>(stoi(data_reader));
				string_10 Object;
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
						Object.show_elements(); //uncomment
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
	}
}