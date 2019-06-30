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



	/*
		HELPFUL FUNCTIONS
	*/
	template<typename _Ty_Left, typename _Ty_Right>
	void __stdcall __swap(_Ty_Left & _Left, _Ty_Right & _Right) noexcept
	{
		_Ty_Left temporary_left = _Left;
		_Left = _Right;
		_Right = temporary_left;
	}
}


#endif /* _ALGORITHMS_LIBRARY */