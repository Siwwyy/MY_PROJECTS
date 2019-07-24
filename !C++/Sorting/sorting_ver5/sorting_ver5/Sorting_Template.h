// _SORTING_TEMPLATE_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							*** WERSJA FINALNA ***
 *						   *** Koniec: //2018 ***
 *							Klasa ma za zadanie:
 *	1.
*/
#ifndef _SORTING_TEMPLATE_H_
#define _SORTING_TEMPLATE_H_
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>

/*
	OUTSIDE FILES .h/.hpp
*/
#include "Write_Chart.h"
#define STOPWATCH_ON		//defined for turn on the stop watch
#include "StopWatch.h"

template<typename Type>
class Sorting_Template
{
private:
	/*
		ZMIENNE PRIVATE
	*/
	Write_Chart Chart_Object;
	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PRIVATE
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PRIVATE
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PRIVATE
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY PRIVATE
	*/
	//JEDNOARGUMENTOWE

	//////////////////////////////////////////////////////////////////////////////
protected:
	/*
		ZMIENNE PROTECTED
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PROTECTED
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC PROTECTED
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PROTECTED
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PROTECTED
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY PROTECTED
	*/
	//JEDNOARGUMENTOWE

	//////////////////////////////////////////////////////////////////////////////
public:
	/*
		ZMIENNE PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		KONSTRUKTORY PUBLIC
	*/
	Sorting_Template();
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	__forceinline void bubble_sort();
	__forceinline void tymczasowa();
	//__forceinline void quick_sort(const Type & array_type, const Type & left, const Type & right);
	__forceinline void quick_sort();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY PUBLIC
	*/
	//JEDNOARGUMENTOWE

	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	virtual ~Sorting_Template();		//wirtualny destruktor
	//////////////////////////////////////////////////////////////////////////////
};

//////////////////////////////////////////////////////////////////////////////////
/*
				BODY OF FUNCTIONS
*/
//////////////////////////////////////////////////////////////////////////////////

template<typename Type>
__forceinline Sorting_Template<Type>::Sorting_Template()
{

}

template<typename Type>
__forceinline void Sorting_Template<Type>::bubble_sort()
{
	Chart_Object.Fill_Vector();
	Chart_Object.Write_The_Chart();
	system("pause");
	START_STOPWATCH
	for (int i = 0; i < Chart_Object.get_vector_width(); i++)
	{
		for (int j = 0; j < Chart_Object.get_vector_width() - 1; j++)
		{
			if (Chart_Object.get_vector_height(j) > Chart_Object.get_vector_height(j + 1))
			{
				std::swap(Chart_Object.get_vector_array(j), Chart_Object.get_vector_array(j + 1));
				Chart_Object.Write_Single_Chart(j);
				Chart_Object.Write_Single_Chart(j + 1);
			}
		}
		
	}
	MyObj.STOP(StopWatch::SECOND);
}

template<typename Type>
__forceinline void Sorting_Template<Type>::tymczasowa()
{
	Chart_Object.Fill_Vector();
	Chart_Object.Write_The_Chart();
}

template<typename Type>
__forceinline void Sorting_Template<Type>::quick_sort()
{
	Chart_Object.Fill_Vector();
	Chart_Object.Write_The_Chart();
	START_STOPWATCH

	auto quicksort = [](const Type * array_type, const Type & left, const Type & right)
	{

	};

	MyObj.STOP(StopWatch::SECOND);
}

template<typename Type>
__forceinline Sorting_Template<Type>::~Sorting_Template()
{

}

#endif /* _SORTING_TEMPLATE_H_ */