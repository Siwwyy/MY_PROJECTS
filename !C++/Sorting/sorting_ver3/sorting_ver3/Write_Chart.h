// _WRITE_CHART_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							*** WERSJA FINALNA ***
 *						  *** Koniec: 2/12/2018 ***
 *							Klasa ma za zadanie:
 *	1. 
*/
#ifndef _WRITE_CHART_H_
#define _WRITE_CHART_H_
#pragma once

/*
	SPACE FOR INCLUDING
*/
//Compiler files
#include <string>
#include <random>
#include <vector>
#include <iostream>
#include <windows.h>
///////////////////////////
//User files

///////////////////////////

class Write_Chart
{
private:
	/*
		PRIVATE VARIABLES
	*/
	/*template<typename Type>			//przygotowane do template class
	using Chart_XY = std::vector<std::vector<Type>>;*/
	CONSOLE_SCREEN_BUFFER_INFO Console_Info;
	COORD CORD;										//Obiekt struktury COORD, w ktorym znajduja sie koordynaty X i Y do ustawienia kursora
	HANDLE H_OUT, H_IN;								//Zmienna przechowujace uchywyt do outputu oraz inputu okna
	uint16_t max_height;
	uint16_t height;
	uint16_t width;
	short Cursor_X, Cursor_Y;
	//std::vector<std::vector<char>> Chart(max_height, std::vector<char>(max_width));
	std::vector<std::vector<char>> Chart_XY;
	//////////////////////////////////////////////////////////////////////////////
protected:
	/*
		PROTECTED VARIABLES
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PROTECTED
	*/
	void SetCursorPosition(const short _X_AXIS, const short _Y_AXIS);
	//////////////////////////////////////////////////////////////////////////////
public:
	/*
		KONSTRUKTORY
	*/
	Write_Chart();												//konstruktor bezparametrowy
	Write_Chart(const Write_Chart & Object);					//konstruktor kopiujacy
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void Write_The_Chart();
	void Fill_Vector();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY
	*/
	//void Set_Height(const int Y);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY
	*/
	uint16_t get_max_height() const;
	uint16_t get_width() const;
	uint16_t get_height() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY
	*/
	//JEDNOARGUMENTOWE
	
	//DWUARGUMENTOWE
	
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	~Write_Chart();				//destruktor wirtualny na wypadek dziedziczenia 
	//////////////////////////////////////////////////////////////////////////////
};

#endif /* _WRITE_CHART_H_ */
