#include "Window.hpp"

Window::Window::Window():
	width(0),
	height(0)
{
	this->window_name = new char[5];
	strcpy_s(window_name,5, "NULL");
	_STD cout << window_name;
	_STD cin.get();
}

Window::Window::~Window()
{
	this->width = 0;
	this->height = 0;
	delete[] this->window_name;
}