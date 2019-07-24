#include "Write_Chart.h"

using namespace std;

void Write_Chart::SetCursorPosition(const short _X_AXIS, const short _Y_AXIS)
{
	CORD.X = _X_AXIS;
	CORD.Y = _Y_AXIS;
	SetConsoleCursorPosition(H_OUT, CORD);
}

Write_Chart::Write_Chart():
	height(30),
	max_height(0),
	Cursor_X(0),
	Cursor_Y(0),
	width(100)
{
	this->H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
}

Write_Chart::Write_Chart(const Write_Chart & Object):
	height(Object.height),
	max_height(Object.max_height),
	Cursor_X(Object.Cursor_X),
	Cursor_Y(Object.Cursor_Y),
	CORD(Object.CORD),
	width(Object.width)
{
	this->H_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Write_Chart::Write_The_Chart()
{
	system("cls");
	SetCursorPosition(0, 0);	//zamien te +2 itp itd na current position of cursor !!!!
	for (int i = 0; i < static_cast<int>(Chart_XY.size()); i++)
	{
		int drawing_chart = max_height;					//zmienna do rysowania wykresu w gore, zaczyna od dolu i idzie w gore
		//poniewaz punkt 0,0 jest w lewym gornym rogu. A wiec dodajac 20 do np. osi Y kursor idzie o 20 pozycji w dol
		SetCursorPosition(i, drawing_chart);			//zamien te +2 itp itd na current position of cursor !!!!	
		for (int j = 0; j < static_cast<int>(Chart_XY[i].size()); j++)
		{
			std::cout << Chart_XY[i][j];
			SetCursorPosition(i, drawing_chart);
			drawing_chart--;
		}
	}
	SetCursorPosition(0, Console_Info.dwCursorPosition.Y + max_height + 1);
	for (int i = 0; i < static_cast<int>(Chart_XY.size()); i++)
	{	
		std::cout << static_cast<int>(Chart_XY[i].size()) << ' ';
	}
	SetCursorPosition(0, Console_Info.dwCursorPosition.Y + max_height + 2);
}

void Write_Chart::Write_Single_Chart(const int i)
{
	SetCursorPosition(0, 0);	//zamien te +2 itp itd na current position of cursor !!!!
	int drawing_chart = max_height;					//zmienna do rysowania wykresu w gore, zaczyna od dolu i idzie w gore
	//poniewaz punkt 0,0 jest w lewym gornym rogu. A wiec dodajac 20 do np. osi Y kursor idzie o 20 pozycji w dol
	SetCursorPosition(i, drawing_chart);			//zamien te +2 itp itd na current position of cursor !!!!
	Clear_Column(i);
	SetCursorPosition(i, drawing_chart);
	for (int j = 0; j < static_cast<int>(Chart_XY[i].size()); j++)
	{
		std::cout << Chart_XY[i][j];
		SetCursorPosition(i, drawing_chart);
		drawing_chart--;
	}
	SetCursorPosition(0, Console_Info.dwCursorPosition.Y + max_height + 1);
	for (int i = 0; i < static_cast<int>(Chart_XY.size()); i++)
	{
		std::cout << static_cast<int>(Chart_XY[i].size()) << ' ';
	}
	SetCursorPosition(0, Console_Info.dwCursorPosition.Y + max_height + 2);
}

void Write_Chart::Clear_Column(const int a)
{
	int drawing_chart = max_height;
	for (int i = 0; i < max_height; i++)
	{
		std::cout << ' ';
		SetCursorPosition(a, drawing_chart);
		drawing_chart--;
	}
}

void Write_Chart::Fill_Vector()
{
	Chart_XY.clear();
	std::random_device rand;								//do odpalenia silnika
	std::mt19937 generator(rand());							//standardowy generator (mersenne_twister_engine)
	std::uniform_int_distribution<> dis(1, height);			//zakres naszego losowania
	std::vector<char> temp;
	for (int i = 0; i < width; i++)
	{
		int high = dis(generator);
		auto max_height_chart = [&](const uint16_t height) -> void { max_height < height ? max_height = height : max_height = max_height; };		//zwracany typ pusty defaultowo
		max_height_chart(high);
		for (int j = 0; j < high; j++)
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

size_t Write_Chart::get_vector_width() const
{
	return Chart_XY.size();
}

size_t Write_Chart::get_vector_height(const int i) const
{
	return Chart_XY[i].size();
}

std::vector<char> & Write_Chart::get_vector_array(const int i)
{
	return Chart_XY[i];
}

Write_Chart & Write_Chart::operator=(const Write_Chart & Object)
{
	if (this != &Object)
	{
		this->max_height = Object.max_height;
		this->height = Object.height;
		this->width = Object.width;
		this->CORD.X = Object.CORD.X;
		this->CORD.Y= Object.CORD.Y;
	}
	return *this;
}

uint16_t Write_Chart::get_width() const
{
	return width;
}

Write_Chart::~Write_Chart()
{
	Chart_XY.~vector();
}
