#include <random>
#include <string>
#include <iostream>
#include <windows.h>
#include "Write_Chart.h"
#include "Single_Element.h"

using namespace std;

int main(int argc, char * argv[])
{
	//Prosze odkomentowac ktora opcje sie wybiera
	/*HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD HC;
	HC.X = 4;
	HC.Y = 2;
	SetConsoleCursorPosition(H, HC);*/
	Single_Element A;
	A.Set_Height(20);
	A.Fill_Vector();
	A.Write_Element();
	//std::cout << ' ';
	cin.get();
	/*HC.X = 2;
	HC.Y = 3;
	SetConsoleCursorPosition(H, HC);*/
	Single_Element B;
	B.Set_Height(15);
	B.Fill_Vector();
	B.Write_Element();
	Single_Element C;
	B.Set_Height(18);
	B.Fill_Vector();
	B.Write_Element();
	Single_Element D;
	B.Set_Height(4);
	B.Fill_Vector();
	B.Write_Element();
//	std::cout << static_cast<int>(A.get_max_height()) << endl;	//trybi
	/*Single_Element A;
	A.Set_Height(20);
	A.Fill_Vector();
	A.Write_Element();
	system("pause");*/
/*	Write_Chart Object;
	Object.Fill_Vector();
	Object.Write_The_Chart();*/
	cout << "THATS THE END :))))" << endl;
	system("pause");
	return 0;
}
