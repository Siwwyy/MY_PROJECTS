#include "Write_Chart.h"

using namespace std;

void Write_Chart::SetCursorPosition(const short _X_AXIS, const short _Y_AXIS)
{
	CORD.X = _X_AXIS;
	CORD.Y = _Y_AXIS;
	SetConsoleCursorPosition(H_OUT, CORD);
}

Write_Chart::Write_Chart():
	Chart()
{

}

Write_Chart::Write_Chart(const Write_Chart & object):
	Chart()
{

}

void Write_Chart::Write_The_Chart() const
{
	for (typename std::vector<Single_Element>::const_iterator iter = Chart.begin(); iter != Chart.end(); iter++)
	{
		iter->Write_Element();
	}
}

void Write_Chart::Fill_Vector()
{
	for(int i = 0; i < )
}

Write_Chart::~Write_Chart()
{
	Chart.clear();
}
