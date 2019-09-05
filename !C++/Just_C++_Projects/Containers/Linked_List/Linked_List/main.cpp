#include <iostream>
#include <windows.h>
#include <string>
#include <List>
#include <vector>
//#define _DEBUG
//#include <corecrt_malloc.h>

//using namespace std;

#include "List.hpp"

int main(int argc, char * argv[])
{
	
	MyList::List<int> my_own_list;
	my_own_list.push(1);
	my_own_list.push(2);
	my_own_list.push(3);
	my_own_list.push(4);
	my_own_list.push(5);
	my_own_list.push(6);
	my_own_list.push(7);
	my_own_list.push(8);
	my_own_list.push(9);	
	//my_own_list.pop_everything();

	MyList::List<int> my_own_list_copy(my_own_list);
	//my_own_list_copy.pop_everything();
	//my_own_list.Clear_List();
	//my_own_list_copy.Clear_List();

	/*my_own_list.push(1);
	my_own_list.push(2);
	my_own_list.push(3);
	my_own_list.push(4);*/
	//my_own_list.pop_everything();

	
	system("pause");
	return EXIT_SUCCESS;
}