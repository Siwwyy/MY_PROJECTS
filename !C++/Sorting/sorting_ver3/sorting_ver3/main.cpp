#include <random>
#include <string>
#include <iostream>
#include <windows.h>
#include "Write_Chart.h"

using namespace std;

int main(int argc, char * argv[])
{
	//Prosze odkomentowac ktora opcje sie wybiera
	system("pause");
	for (;;)
	{
		char wybor;
		cin >> wybor;
		switch (wybor)
		{
			case '1':
			{
				Write_Chart Object;
				Object.Fill_Vector();
				Object.Write_The_Chart();
				//Sleep(300);
				system("pause");
			}
			break;
			case '2':
			{
				cout << "THATS THE END :))))" << endl;
				exit(0);
			}
			break;
			default: std::cout << "Brak takiej opcji!" << std::endl; break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}
