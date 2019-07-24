// _SINGLE_ELEMENT_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							*** WERSJA FINALNA ***
 *						  *** Koniec: 2/12/2018 ***
 *							Klasa ma za zadanie:
 *	1.
*/
#ifndef _SINGLE_ELEMENT_H_
#define _SINGLE_ELEMENT_H_
#pragma once

/*
	SPACE FOR INCLUDING
*/
//Compiler files
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>
///////////////////////////
//User files

///////////////////////////

class Single_Element
{
private:
	/*
		PRIVATE VARIABLES
	*/
	std::vector<char> elements;
	uint8_t height;
	char element_view;
	static uint8_t max_height;
	//////////////////////////////////////////////////////////////////////////////
protected:
	/*
		PROTECTED VARIABLES
	*/

	//////////////////////////////////////////////////////////////////////////////
public:
	/*
		KONSTRUKTORY
	*/
	Single_Element();												//konstruktor bezparametrowy
	Single_Element(const Single_Element & object);					//konstruktor kopiujacy
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void Write_Element() const;
	void Fill_Vector();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY
	*/
	void Set_Height(const int Y);
	void Set_Vector_Element_View(const char element_view);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY
	*/
	uint8_t get_height() const;
	uint8_t get_max_height() const;
	size_t get_vector_size() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY
	*/
	//JEDNOARGUMENTOWE
	Single_Element & operator=(const Single_Element & Object);
	//DWUARGUMENTOWE

	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	~Single_Element();				//destruktor wirtualny na wypadek dziedziczenia 
	//////////////////////////////////////////////////////////////////////////////
};

#endif /* _SINGLE_ELEMENT_H_ */
