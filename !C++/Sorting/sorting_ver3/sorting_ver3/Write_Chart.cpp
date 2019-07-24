#include "Write_Chart.h"

using namespace std;

void Write_Chart::SetCursorPosition(const short _X_AXIS, const short _Y_AXIS)
{
	CORD.X = _X_AXIS;
	CORD.Y = _Y_AXIS;
	SetConsoleCursorPosition(H_OUT, CORD);
}

Write_Chart::Write_Chart():
	height(20),
	max_height(0),
	Cursor_X(0),
	Cursor_Y(0),
	width(30)
	//Chart(0)
{
	this->H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
}

Write_Chart::Write_Chart(const Write_Chart & Object):
	height(Object.height),
	max_height(Object.max_height),
	Cursor_X(Object.Cursor_X),
	Cursor_Y(Object.Cursor_Y),
	width(Object.width)
	//Chart(0)
{
	this->H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Write_Chart::Write_The_Chart()
{
	system("cls");
	std::cout << max_height;
	std::cout << max_height;
	std::cout << max_height;
	std::cout << max_height;
	std::cout << max_height;
	//SetCursorPosition(0, 0);
	/*POINT pt;	//to do myszki
	GetCursorPos(&pt);
	std::cout << pt.y << endl;
	system("pause");*/
	//max_height += static_cast<uint16_t>(pt.y);
	//max_height += static_cast<uint16_t>(pt.y);
	for (int i = 0; i < static_cast<int>(Chart_XY.size()); i++)
	{
		SetCursorPosition(i, Console_Info.dwCursorPosition.Y + max_height + 1);	//zamien te +2 itp itd na current position of cursor !!!!
		int a = Console_Info.dwCursorPosition.Y + max_height + 1;					//zmienna do rysowania wykresu w gore, zaczyna od dolu i idzie w gore
		//std::cout << static_cast<int>(Chart_XY[i].size());
		//SetCursorPosition(i, max_height);				
		for (int j = 0; j < static_cast<int>(Chart_XY[i].size()); j++)
		{
			std::cout << Chart_XY[i][j];
			SetCursorPosition(i, a);
			a--;
		}
		//std::cout << '\n';
	}
	//std::cout << '\n';
	SetCursorPosition(0, Console_Info.dwCursorPosition.Y + max_height + 1);
}

void Write_Chart::Fill_Vector()
{
	std::random_device rand;								//do odpalenia silnika
	std::mt19937 generator(rand());							//standardowy generator (mersenne_twister_engine)
	std::uniform_int_distribution<> dis(1, height);			//zakres naszego losowania
	std::vector<char> temp;
	for (int i = 0; i < width; i++)
	{
		int high = dis(generator);
		//std::cout << high << ' ';
		auto max_height_chart = [=](const uint16_t height) -> void { max_height < height ? max_height = height : max_height = max_height; };		//zwracany typ pusty defaultowo
		max_height_chart(high);
		for (int j = 0; j <= high; j++)
		{
			temp.emplace_back('o');
		}
		Chart_XY.emplace_back(temp);
		temp.clear();
	}
}

uint16_t Write_Chart::get_max_height() const
{
	return max_height;
}

uint16_t Write_Chart::get_height() const
{
	return height;
}

uint16_t Write_Chart::get_width() const
{
	return width;
}

Write_Chart::~Write_Chart()
{
	Chart_XY.~vector();
}
