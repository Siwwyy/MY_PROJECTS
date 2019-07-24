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
	Write_Chart(const Write_Chart & object);					//konstruktor kopiujacy
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void Write_The_Chart() const;
	void Fill_Vector();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY
	*/
	
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
