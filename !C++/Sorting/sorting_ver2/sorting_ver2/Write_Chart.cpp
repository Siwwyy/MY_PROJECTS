#include "Write_Chart.h"

using namespace std;

void Write_Chart::SetCursorPosition(const short _X_AXIS, const short _Y_AXIS)
{
	CORD.X = _X_AXIS;
	CORD.Y = _Y_AXIS;
	SetConsoleCursorPosition(H_OUT, CORD);
}

Write_Chart::Write_Chart():
	Chart(),
	max_height(5),
	max_width(20)
{
	H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
	this->Chart(max_height, std::vector<char>(max_width));
}

Write_Chart::Write_Chart(const Write_Chart & Object):
	Chart(),
	max_height(Object.max_height),
	max_width(Object.max_width)
{
	this->H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
	this->Chart(max_height, std::vector<char>(max_width));
}

void Write_Chart::Write_The_Chart()
{
	SetCursorPosition(2, 2);
	int i = 2;
	for (typename std::vector<Single_Element>::const_iterator iter = Chart.begin(); iter != Chart.end(); iter++)
	{
		iter->Write_Element();
	//	system("pause");
		cin.get();
		SetCursorPosition(2, i);
		i++;
	}
	std::cout << endl;
}

void Write_Chart::Fill_Vector()
{
	std::random_device rand;								//do odpalenia silnika
	std::mt19937 generator(rand());							//standardowy generator (mersenne_twister_engine)
	std::uniform_int_distribution<> dis(1, max_height);			//zakres naszego losowania
	for (int i = 0; i < max_width; i++)
	{
		Single_Element Obj;
		//std::cout << dis(generator);
		Obj.Set_Height(dis(generator));
		Obj.Fill_Vector();
		Chart.emplace_back(Obj);
	}
}

uint8_t Write_Chart::get_max_height() const
{
	return max_height;
}

uint16_t Write_Chart::get_max_width() const
{
	return max_width;
}

Write_Chart::~Write_Chart()
{
	Chart.clear();
}
