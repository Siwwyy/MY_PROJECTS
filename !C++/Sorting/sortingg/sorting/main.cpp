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
	Single_Element A;
	A.Set_Height(20);
	A.Fill_Vector();
	A.Write_Element();
	//std::cout << ' ';
	Single_Element B;
	B.Set_Height(30);
	B.Fill_Vector();
	B.Write_Element();
//	std::cout << static_cast<int>(A.get_max_height()) << endl;	//trybi
	cout << "THATS THE END :))))" << endl;
	system("pause");
	return 0;
}
