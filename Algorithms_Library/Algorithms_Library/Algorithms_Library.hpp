/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *							Greetings for everyone!
*/
#pragma once
#ifndef _ALGORITHMS_LIBRARY_HPP_
#define _ALGORITHMS_LIBRARY_HPP_

#include <iostream>
#include <windows.h>
#include <string>

/*
	LIBRARY CONNECTED HEADERS
*/
#include "Hash_Table.hpp"
#include "Heap_Sort.hpp"
#include "MST.hpp"
//////////////////////////////////////////////

namespace Algorithms
{
	
	using ::std::cerr;
	using ::std::cout;
	using ::std::endl;

	using namespace Algorithms_Hash_Table;
	using namespace Algorithms_Heap_Sort;
	using namespace Algorithms_MST;

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
					//if (compare_function_operator((const void*)(&array[j]), (const void *)(&array[j + 1])) == true)
					if (compare_function_operator(static_cast<const void*>(&array[j]), static_cast<const void*>(&array[j + 1])) != true)
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

	template<typename _Ty>
	//sorting in self-made order
	void Shake_Sort(_Ty * array, const size_t size, const bool(*compare_function_operator)(const void *, const void *)) noexcept
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
					if (compare_function_operator(static_cast<const void*>(&array[i]), static_cast<const void*>(&array[i + 1])) != true)
					{
						Algorithms::__swap(array[i], array[i + 1]);
						replace = true;
					}
				}
				top--;
				for (size_t i = top; i > bottom; i--)
				{
					if (compare_function_operator(static_cast<const void*>(&array[i]), static_cast<const void*>(&array[i - 1])) == true)
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
	void Quick_Sort(_Ty * array , const __int64 _Left, const __int64 _Right)
	{
		_Ty v = array[(_Left + _Right) / 2];
		_Ty x = {};
		__int64 i = {}, j = {};
		i = _Left;
		j = _Right;
		do
		{
			while (array[i] < v)
			{
				i++;
			}
			while (array[j] > v)
			{
				j--;
			}
			if (i <= j)
			{
				x = array[i];
				array[i] = array[j];
				array[j] = x;
				i++;
				j--;
			}
		} while (i <= j);
		if (j > _Left)
		{
			Quick_Sort(array, _Left, j);
		}
		if (i < _Right)
		{
			Quick_Sort(array, i, _Right);
		}
	}

	//SELF ORDERING, less key
	template<typename _Ty>
	void Quick_Sort(_Ty * array, const __int64 _Left, const __int64 _Right, const bool(*compare_function_operator)(const void *, const void *))
	{
		_Ty v = array[(_Left + _Right) / 2], x = {};
		__int64 i = {}, j = {};
		i = _Left;
		j = _Right;
		do
		{
			while (compare_function_operator(static_cast<const void*>(&array[i]), static_cast<const void*>(&v)) == true)
			{
				i++;
			}
			while (compare_function_operator(static_cast<const void*>(&array[j]), static_cast<const void*>(&v)) != true)
			{
				j--;
			}
			if (i <= j)
			{
				x = array[i];
				array[i] = array[j];
				array[j] = x;
				i++;
				j--;
			}
		} while (i <= j);
		if (compare_function_operator(static_cast<const void*>(&j), static_cast<const void*>(&_Left)) != true)
		{
			Quick_Sort(array, _Left, j);
		}
		if (compare_function_operator(static_cast<const void*>(&i), static_cast<const void*>(&_Right)) == true)
		{
			Quick_Sort(array, i, _Right);
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
			::std::cerr << "ERROR::FIRST PARAM OR SECOND IS SMALLER OR EQUAL TO 0! A and B have to be greater than 0 ! \n";
		}
		return a;
	}

	//Linear Serach
	template<typename _Ty>
	constexpr size_t Linear_Serach(_Ty * array, const size_t size, const _Ty && _to_serach)
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
	template<typename _Ty>
	constexpr size_t Binary_Serach(_Ty * array, const size_t size, const _Ty && _to_serach)
	{
		Quick_Sort(const_cast<char *>(array), 0, size - 1);
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

#endif /* _ALGORITHMS_LIBRARY_HPP_ */