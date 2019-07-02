#pragma once
#ifndef _ALGORITHMS_LIBRARY
#define _ALGORITHMS_LIBRARY

namespace Algorithms
{
	#include <iostream>
	#include <windows.h>
	#include <string>
	#include <vector>

	/*
		FUNCTIONS CASE
	*/

	//BUBBLE SORT
	//sorting in increasing order
	template<typename _Ty>
	void Bubble_Sort(_Ty * array, const size_t size) noexcept
	{
		if (size <= 1)
		{
			std::cerr << "ERROR::SIZE IS TOO SMALL \n";
		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				for (size_t j = 0; j < size - 1; ++j)
				{
					if (array[j] > array[j + 1])
					{
						Algorithms::__swap(array[j], array[j + 1]);
					}
				}
			}
		}
	}

	template<typename _Ty>
	//sorting in self-made order
	void Bubble_Sort(_Ty * array, const size_t size, const bool (*compare_function_operator)(const void * , const void * )) noexcept
	{
		if (size <= 1)
		{
			std::cerr << "ERROR::SIZE IS TOO SMALL \n";
		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				for (size_t j = 0; j < size - 1; ++j)
				{
					/*const void * ptr_left = &array[j];
					const void * ptr_right = &array[j + 1];*/
					//std::cout << &array[j] << ' '<< ptr << std::endl;
					if (compare_function_operator((const void*)(&array[j]), (const void *)(&array[j + 1])) == true)
					{
						Algorithms::__swap(array[j], array[j + 1]);
					}
				}
			}
		}
	}

	//SHAKE SORT
	template<typename _Ty>
	void Shake_Sort(_Ty * array, const size_t size) noexcept
	{
		if (size <= 1)
		{
			std::cerr << "ERROR::SIZE IS TOO SMALL \n";
		}
		else
		{
			size_t bottom = 0, top = size - 1;
			bool replace = true;

			while (replace == true)
			{
				replace = false;
				for (size_t i = 0; i < top; ++i)
				{
					if (array[i] > array[i + 1])
					{
						Algorithms::__swap(array[i], array[i + 1]);
						replace = true;
					}
				}
				top--;
				for (size_t i = top; i > bottom; i--)
				{
					if (array[i] < array[i - 1])
					{
						Algorithms::__swap(array[i], array[i - 1]);
						replace = true;
					}
				}
				bottom++;
			}
		}
	}

	//Quick Sort
	template<typename _Ty>
	void Quick_Sort(_Ty * array, const __int64 & p, const __int64 & r) noexcept
	{
		__int64 q = {};
		if (p < r)
		{
			q = partition(array, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
			quicksort(array, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
			quicksort(array, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
		}
	}

	template<typename _Ty>
	int partition(_Ty * array, __int64 & p, __int64 & r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
	{
		__int64 x = array[p]; // obieramy x
		__int64 i = p, j = r, w; // i, j - indeksy w tabeli
		while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
		{
			while (array[j] > x)
			{
				// dopoki elementy sa wieksze od x
				j--;
			}
			while (array[i] < x)
			{// dopoki elementy sa mniejsze od x
				i++;
			}
			if (i < j) // zamieniamy miejscami gdy i < j
			{
				w = array[i];
				array[i] = array[j];
				array[j] = w;
				i++;
				j--;
			}
			else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			{
				return j;
			}
		}
	}

	//Euqlides Algorithm
	constexpr __int64 Euqlides_Algorithm(__int64 & a, __int64 & b)
	{
		if (a > 0 && b > 0)
		{
			__int64 temporary = 0;
			while (b != 0)
			{
				temporary = b;
				b = a % b;
				a = temporary;
			}
		}
		else
		{
			std::cerr << "ERROR::FIRST PARAM OR SECOND IS SMALLER OR EQUAL TO 0! A and B have to be greater than 0 ! \n";
		}
		return a;
	}

	//Linear Serach
	constexpr size_t Linear_Serach(const std::string & array, const size_t size, char && _to_serach)
	{
		size_t counter = 0;
		for (size_t i = 0; i < size; ++i)
		{
			if (_to_serach == array[i])
			{
				break;
			}
			counter++;
		}
		return counter;
	}

	//Binary Serach


	/*
		HELPFUL FUNCTIONS
	*/

	template<typename _Ty_Left, typename _Ty_Right>
	void __stdcall __swap(_Ty_Left & _Left, _Ty_Right & _Right) noexcept
	{
		/*
			int x = 10, y = 5; 
			// Code to swap 'x' (1010) and 'y' (0101) 
			x = x ^ y; // x now becomes 15 (1111) 
			y = x ^ y; // y becomes 10 (1010) 
			x = x ^ y; // x becomes 5 (0101) 
		*/
		//Swapping without the temporary variable
		_Left = _Left ^ _Right;
		_Right = _Left ^ _Right;
		_Left = _Left ^ _Right;
	}
}


#endif /* _ALGORITHMS_LIBRARY */