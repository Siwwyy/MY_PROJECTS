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
	enum TYPE_OF_SORTING
	{
		BUBBLE_SORT = 0,
		QUICK_SORT = 0,
		MERGE_SORT = 0
	};
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
	__forceinline void choose_type_of_sorting(enum Sorting_Template::TYPE_OF_SORTING SORTING_TYPE);
	__forceinline void bubble_sort();
	__forceinline void tymczasowa();
	//__forceinline void quick_sort(const Type & array_type, const Type & left, const Type & right);
	__forceinline void quick_sort(std::vector<int> & array_type, int left, int right);
	__forceinline void merge_sort(std::vector<int> & array_type, int begin, int end);
	__forceinline void merge(std::vector<int> & array_type, int begin, int center, int end);
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
	//Chart_Object.Fill_Vector();
	//Chart_Object.Write_The_Chart();
}

template<typename Type>
__forceinline void Sorting_Template<Type>::choose_type_of_sorting(enum Sorting_Template::TYPE_OF_SORTING SORTING_TYPE)
{
	Chart_Object.Fill_Vector();
	Chart_Object.Write_The_Chart();
	START_STOPWATCH
	if (SORTING_TYPE == Sorting_Template::TYPE_OF_SORTING::BUBBLE_SORT)
	{
		bubble_sort();
	}
	else if (SORTING_TYPE == Sorting_Template::TYPE_OF_SORTING::QUICK_SORT)
	{
		std::vector<int> temp_vec;
		for (int i = 0; i < static_cast<int>(Chart_Object.get_vector_width()); i++)
		{
			temp_vec.emplace_back(Chart_Object.get_vector_height(i));
		}
		quick_sort(temp_vec, 0, static_cast<int>(temp_vec.size() - 1));
		temp_vec.clear();
	}
	else if (SORTING_TYPE == Sorting_Template::TYPE_OF_SORTING::MERGE_SORT)
	{
		std::vector<int> temp_vec;
		for (int i = 0; i < static_cast<int>(Chart_Object.get_vector_width()); i++)
		{
			temp_vec.emplace_back(Chart_Object.get_vector_height(i));
		}
		merge_sort(temp_vec, 0, static_cast<int>(temp_vec.size() - 1));
		temp_vec.clear();
	}
	MyObj.STOP(StopWatch::SECOND);
	system("pause");
}

template<typename Type>
__forceinline void Sorting_Template<Type>::bubble_sort()
{
//	START_STOPWATCH
	for (int i = 0; i < static_cast<int>(Chart_Object.get_vector_width()); i++)
	{
		for (int j = 0; j < static_cast<int>(Chart_Object.get_vector_width() - 1); j++)
		{
			if (Chart_Object.get_vector_height(j) > Chart_Object.get_vector_height(j + 1))
			{
				std::swap(Chart_Object.get_vector_array(j), Chart_Object.get_vector_array(j + 1));
				Chart_Object.Write_Single_Chart(j);
				Chart_Object.Write_Single_Chart(j + 1);
			}
		}
	}
	//MyObj.STOP(StopWatch::SECOND);
}

template<typename Type>
__forceinline void Sorting_Template<Type>::tymczasowa()
{
	Chart_Object.Fill_Vector();
	Chart_Object.Write_The_Chart();
}

template<typename Type>
__forceinline void Sorting_Template<Type>::quick_sort(std::vector<int> & array_type, int left, int right)
{
	int v = array_type[(left + right) / 2];
	int i, j, x;
	i = left;
	j = right;
	Chart_Object.Write_Single_Chart(i);
//	Chart_Object.Write_Single_Chart(j);
	do
	{
		while (array_type[i] < v)
		{
			i++;
		}
		while (array_type[j] > v)
		{
			j--;
		}
		if (i <= j)
		{
			x = array_type[i];
			array_type[i] = array_type[j];
			array_type[j] = x;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > left)
	{
		quick_sort(array_type, left, j);
	}
	if (i < right)
	{
		quick_sort(array_type, i, right);
	}
}

template<typename Type>
__forceinline void Sorting_Template<Type>::merge_sort(std::vector<int>& array_type, int begin, int end)
{
	int srodek;

	if (begin != end)
	{
		srodek = (begin + end) / 2;
		merge_sort(array_type, begin, srodek);
		merge_sort(array_type, srodek + 1, end);
		merge(array_type, begin, srodek, end);
	}
}

template<typename Type>
__forceinline void Sorting_Template<Type>::merge(std::vector<int> & array_type, int begin, int center, int end)
{
	int *tab_pom = new int[(end - begin)]; // utworzenie tablicy pomocniczej
	int i = begin, j = center + 1, k = 0; // zmienne pomocnicze
	Chart_Object.Write_Single_Chart(i);
	//Chart_Object.Write_Single_Chart(j);
	while (i <= center && j <= end)
	{
		if (array_type[j] < array_type[i])
		{
			tab_pom[k] = array_type[j];
			j++;
		}
		else
		{
			tab_pom[k] = array_type[i];
			i++;
		}
		k++;
	}

	if (i <= center)
	{
		while (i <= center)
		{
			tab_pom[k] = array_type[i];
			i++;
			k++;
		}
	}
	else
	{
		while (j <= end)
		{
			tab_pom[k] = array_type[j];
			j++;
			k++;
		}
	}

	for (i = 0; i <= end - begin; i++)
	{
		array_type[begin + i] = tab_pom[i];
	}
}

template<typename Type>
__forceinline Sorting_Template<Type>::~Sorting_Template()
{

}

#endif /* _SORTING_TEMPLATE_H_ */