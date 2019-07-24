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
#include <iostream>
#include <windows.h>
///////////////////////////
//User files
#include "Single_Element.h"
///////////////////////////

class Write_Chart
{
private:
	/*
		PRIVATE VARIABLES
	*/
	std::vector<Single_Element> Chart;
	COORD CORD;										//Obiekt struktury COORD, w ktorym znajduja sie koordynaty X i Y do ustawienia kursora
	HANDLE H_OUT, H_IN;								//Zmienna przechowujace uchywyt do outputu oraz inputu okna
	uint8_t max_height;
	uint16_t max_width;
	//uint8_t height;
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
	uint8_t get_max_height() const;
	uint16_t get_max_width() const;
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
