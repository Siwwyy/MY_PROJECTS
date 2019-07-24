#include "Single_Element.h"

using namespace std;

uint8_t Single_Element::max_height = 4;		//initializing the static variable (must be only one instance of it)

Single_Element::Single_Element():
	elements(),
	element_view('o'),
	height(0)
{

}

Single_Element::Single_Element(const Single_Element & object):
	elements(object.elements),
	element_view(object.element_view),
	height(object.height)
{

}

void Single_Element::Write_Element() const
{
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD HC;
	int i = 4;
	for (typename std::vector<char>::const_iterator reverse_iter = elements.begin(); reverse_iter != elements.end(); reverse_iter++)
	{
		HC.X = max_height;
		HC.Y = i;
		SetConsoleCursorPosition(H, HC);
		std::cout << *reverse_iter << '\n';
		i++;
	}
	max_height++;
}

void Single_Element::Fill_Vector()
{
	for (int i = 0; i < height; i++)
	{
		elements.emplace_back(element_view);
	}
}

void Single_Element::Set_Height(const int Y)
{
	this->height = Y;
/*	auto max_height_chart = [](const uint8_t height) { max_height < height ? max_height = height : max_height = max_height; };
	max_height_chart(height);*/
}

void Single_Element::Set_Vector_Element_View(const char element_view)
{
	this->element_view = element_view;
}

uint8_t Single_Element::get_height() const
{
	return height;
}

/*uint8_t Single_Element::get_max_height() const
{
	return max_height;
}*/

size_t Single_Element::get_vector_size() const
{
	return elements.size();
}

Single_Element & Single_Element::operator=(const Single_Element & Object)
{
	if (this != &Object)
	{
		this->elements = Object.elements;
		this->element_view = Object.element_view;
		//this->height = Object.height;
	}
	return *this;
}

Single_Element::~Single_Element()
{
	elements.clear();
	//height = 0;
}
