/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *					I hope that alghoritm will make right work
 *							Greetings for everyone!
 *						Hash_Table organized array by Key
*/
#pragma once
#ifndef _ALGORITHMS_LIBRARY_HEAP_SORT_HPP_
#define _ALGORITHMS_LIBRARY_HEAP_SORT_HPP_

#include <iostream>
#include <windows.h>
#include <string>

namespace Algorithms_Heap_Sort
{

	using std::cerr;
	using std::endl;
	using std::cout;

	template<typename _Ty, size_t _Size>
	class Heap_Sort
	{
	private:

		class _Heap_Element final
		{
		private:
			/*
				PRIVATE VARIABLES
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Ty Value;
			/////////////////////////////////////////////////////////////////////////////////////////////
		protected:
			/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////
		public:
			/*
				PUBLIC CONSTRUCTORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Heap_Element();
			_Heap_Element(const _Ty & Value);
			_Heap_Element(const _Heap_Element & Object);
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				SETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			void Set_Value(const _Ty & Value);
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				GETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			constexpr _Ty Get_Value() const;
			constexpr size_t Get_Parent(const size_t & i) const;
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				OPERATORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Heap_Element & operator=(const _Heap_Element & Object);
			constexpr bool operator<(const _Heap_Element & Object) const; // to compare(if the key is smaller)
			constexpr bool operator==(const _Heap_Element & Object) const; // to compare(if the key is the same)
			friend std::ostream & operator<<(std::ostream & lhs, const typename Algorithms_Heap_Sort::Heap_Sort<_Ty, _Size>::_Heap_Element & rhs)
			{
				if (rhs.Get_Value() != 0)
				{
					lhs << rhs.Get_Value() << ' ';
				}
				//lhs << rhs.Get_Value() << ' ';
				return lhs;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				DESTRUCTOR
			*/
			virtual ~_Heap_Element();
			/////////////////////////////////////////////////////////////////////////////////////////////
		};
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			PRIVATE FUNCTIONS
		*/
		void Heap_Sorting();
		const size_t Distance_Between(const _Heap_Element * _Left, const _Heap_Element * _Right);
		/////////////////////////////////////////////////////////////////////////////////////////////
	private:
		/*
			PRIVATE VARIABLES
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		_Heap_Element * Heap_Array;
		_Heap_Element * Heap_Sorted;
		size_t Array_Size;
		size_t counter;
		/////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		/////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////
	public:
		/*
			PUBLIC CONSTRUCTORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Heap_Sort();
		Heap_Sort(const size_t & Array_Size);
		Heap_Sort(const Heap_Sort & Object);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			PUBLIC FUNCTIONS
		*/
		void __fastcall push(const _Ty & Value);
		void Start_Sorting();
		void End_Sorting();
		void End_Sorting(std::ostream& out);
		void Show_Heap_Sorted() const;
		void Show_Heap_Sorted(std::ostream & out) const;
		void Show_Heap_Array() const;
		void Show_Heap_Array(std::ostream& out) const;
		void Resize_Arrays(const size_t & size);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			SETTERS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			GETTERS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		constexpr size_t Get_Array_Size() const;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Heap_Sort & operator=(const Heap_Sort & Object);

		template<size_t _Other>
		Heap_Sort & operator=(const Heap_Sort<_Ty, _Other> & Object);

		template<typename _Left_Ty>
		Heap_Sort & operator=(const Heap_Sort<_Left_Ty, _Size> & Object);

		template<typename _Left_Ty, size_t _Other>
		Heap_Sort & operator=(const Heap_Sort<_Left_Ty, _Other> & Object);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUCTOR
		*/
		virtual ~Heap_Sort();
		/////////////////////////////////////////////////////////////////////////////////////////////
	};

	//////////////////////////////////////////////////////
	/*
					BODY OF FUNCTIONS
	*/
	//////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	/*
		_Hash_Element CLASS METHOD'S BODIES
	*/
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::_Heap_Element::_Heap_Element()
	{
		//
		this->Value = {};
	}

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::_Heap_Element::_Heap_Element(const _Ty & Value):
		Value(Value)
	{

	}
	
	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::_Heap_Element::_Heap_Element(const _Heap_Element & Object) :
		Value(Object.Value)
	{

	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::_Heap_Element::Set_Value(const _Ty & Value)
	{
		this->Value = Value;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr _Ty Heap_Sort<_Ty, _Size>::_Heap_Element::Get_Value() const
	{
		return this->Value;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr size_t Heap_Sort<_Ty, _Size>::_Heap_Element::Get_Parent(const size_t & i) const
	{
		return ((i - 1) >> 1);
	}

	template<typename _Ty, size_t _Size>
	__forceinline typename Heap_Sort<_Ty, _Size>::_Heap_Element & Algorithms_Heap_Sort::Heap_Sort<_Ty, _Size>::_Heap_Element::operator=(const _Heap_Element & Object)
	{
		if (this != _STD addressof(Object))
		{
			this->Value = Object.Value;
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Heap_Sort<_Ty, _Size>::_Heap_Element::operator<(const _Heap_Element & Object) const
	{
		return _STD tie(this->Value) < _STD tie(Object.Value);
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Heap_Sort<_Ty, _Size>::_Heap_Element::operator==(const _Heap_Element & Object) const
	{
		return _STD tie(this->Value) == _STD tie(Object.Value);
	}

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::_Heap_Element::~_Heap_Element()
	{
		Value = {};
	}


	////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	/*
		_Hash_Table CLASS METHOD'S BODIES
	*/
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////


	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Heap_Sorting() 
	{
		for (size_t i{}; i < this->Array_Size; ++i)
		{
			if (Heap_Array[i].Get_Value() == NULL)
			{
				continue;
			}
			else
			{
				unsigned int distance = static_cast<unsigned int>(i);
				while (distance != 0)
				{
					if (Heap_Array[distance].Get_Value() >= Heap_Array[Heap_Array[distance].Get_Parent(distance)].Get_Value())
					{
						std::swap(Heap_Array[Heap_Array[distance].Get_Parent(distance)], Heap_Array[distance]);
					}
					else
					{
						break;
					}
					distance = ((distance - 1) >> 1);
				}
			}
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline const size_t Heap_Sort<_Ty, _Size>::Distance_Between(const _Heap_Element * _Left, const _Heap_Element * _Right)
	{
		return static_cast<size_t>(abs(_Left - _Right));
	}

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::Heap_Sort():
		Array_Size(0),
		counter(0)
	{
		this->Heap_Array = new _Heap_Element[this->Array_Size];
		this->Heap_Sorted = new _Heap_Element[this->Array_Size];
	}

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::Heap_Sort(const size_t & Array_Size):
		Array_Size(Array_Size),
		counter(0)
	{
		this->Heap_Array = new _Heap_Element[this->Array_Size];
		this->Heap_Sorted = new _Heap_Element[this->Array_Size];
	}

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::Heap_Sort(const Heap_Sort & Object):
		Array_Size(Object.Array_Size),
		counter(0)
	{
		for (size_t i{}; i < this->Array_Size; ++i)
		{
			this->Heap_Array[i] = Object.Heap_Array[i];
			this->Heap_Sorted[i] = Object.Heap_Sorted[i];
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void __fastcall Heap_Sort<_Ty, _Size>::push(const _Ty & Value)
	{
		//static size_t counter = 0;
		if (counter < this->Array_Size)
		{
			Heap_Array[counter].Set_Value(Value);
		}
		++counter;
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Start_Sorting()
	{
		for (size_t i{}; i < this->Array_Size; ++i)
		{
			Heap_Sorting();
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::End_Sorting()
	{
		for (size_t i{}; i < this->Array_Size; ++i)
		{
			if (Distance_Between(&Heap_Array[0], &Heap_Array[(this->Array_Size - i) - 1]) > 1)
			{
				Heap_Sorted[(this->Array_Size - i) - 1] = Heap_Array[0];
				Heap_Array[0].~_Heap_Element();
				std::swap(Heap_Array[0], Heap_Array[((this->Array_Size - 1) - i)]);
				Heap_Sorting();
				Show_Heap_Array();
			}
			else
			{
				Heap_Sorted[(this->Array_Size - i) - 1] = Heap_Array[0];
				Heap_Array[0].~_Heap_Element();
				std::swap(Heap_Array[0], Heap_Array[((this->Array_Size - 1) - i)]);
				Heap_Sorting();
			}
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::End_Sorting(std::ostream& out)
	{
		for (size_t i{}; i < this->Array_Size; ++i)
		{
			if (Distance_Between(&Heap_Array[0], &Heap_Array[(this->Array_Size - i) - 1]) > 1)
			{
				Heap_Sorted[(this->Array_Size - i) - 1] = Heap_Array[0];
				Heap_Array[0].~_Heap_Element();
				std::swap(Heap_Array[0], Heap_Array[((this->Array_Size - 1) - i)]);
				Heap_Sorting();
				Show_Heap_Array(out);
			}
			else
			{
				Heap_Sorted[(this->Array_Size - i) - 1] = Heap_Array[0];
				Heap_Array[0].~_Heap_Element();
				std::swap(Heap_Array[0], Heap_Array[((this->Array_Size - 1) - i)]);
				Heap_Sorting();
			}
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Show_Heap_Sorted() const
	{
		if (this->Array_Size > 1)
		{
			for (size_t i{}; i < this->Array_Size; ++i)
			{
				std::cout << this->Heap_Sorted[i];
			}
			std::cout << '\n';
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Show_Heap_Sorted(std::ostream& out) const
	{
		if (this->Array_Size > 1)
		{
			for (size_t i{}; i < this->Array_Size; ++i)
			{
				out << this->Heap_Sorted[i];
			}
			out << '\n';
			out << '\n';
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Show_Heap_Array() const
	{
		size_t counter = {};
		if (this->Array_Size > 1)
		{
			for (size_t i{}; i < this->Array_Size; ++i)
			{
				std::cout << this->Heap_Array[i];
				if (Heap_Array[i].Get_Value() == 0)
				{
					++counter;
				}
			}
		}
		if (counter < this->Array_Size - 1)
		{
			std::cout << '\n';
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Show_Heap_Array(std::ostream& out) const
	{
		size_t counter = {};
		if (this->Array_Size > 1)
		{
			for (size_t i{}; i < this->Array_Size; ++i)
			{
				out << this->Heap_Array[i];
				if (Heap_Array[i].Get_Value() == 0)
				{
					++counter;
				}
			}
		}
		if (counter < this->Array_Size - 1)
		{
			out << '\n';
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Heap_Sort<_Ty, _Size>::Resize_Arrays(const size_t & size)
	{
		delete[] Heap_Array;
		delete[] Heap_Sorted;
		this->Array_Size = size;
		this->Heap_Array = new _Heap_Element[this->Array_Size];
		this->Heap_Sorted = new _Heap_Element[this->Array_Size];
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr size_t Heap_Sort<_Ty, _Size>::Get_Array_Size() const
	{
		return this->Array_Size;
	}

	template<typename _Ty, size_t _Size>
	__forceinline typename Heap_Sort<_Ty, _Size> & Heap_Sort<_Ty, _Size>::operator=(const Heap_Sort & Object)
	{
		if (this != _STD addressof(Object))
		{
			delete[] Heap_Array;
			delete[] Heap_Sorted;
			this->Array_Size = Object.Array_Size;
			this->Heap_Array = new _Heap_Element[this->Array_Size];
			this->Heap_Sorted = new _Heap_Element[this->Array_Size];
			for (size_t i{}; i < this->Array_Size; ++i)
			{
				this->Heap_Array[i] = Object.Heap_Array[i];
				this->Heap_Sorted[i] = Object.Heap_Sorted[i];
			}
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	template<size_t _Other>
	__forceinline typename Heap_Sort<_Ty, _Size> & Heap_Sort<_Ty, _Size>::operator=(const Heap_Sort<_Ty, _Other> & Object)
	{
		if (this != _STD addressof(Object))
		{
			delete[] Heap_Array;
			delete[] Heap_Sorted;
			this->Array_Size = Object.Array_Size;
			this->Heap_Array = new _Heap_Element[this->Array_Size];
			this->Heap_Sorted = new _Heap_Element[this->Array_Size];
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	template<typename _Left_Ty>
	__forceinline typename Heap_Sort<_Ty, _Size> & Heap_Sort<_Ty, _Size>::operator=(const Heap_Sort<_Left_Ty, _Size> & Object)
	{
		if (this != _STD addressof(Object))
		{
			delete[] Heap_Array;
			delete[] Heap_Sorted;
			this->Array_Size = Object.Array_Size;
			this->Heap_Array = new _Heap_Element[this->Array_Size];
			this->Heap_Sorted = new _Heap_Element[this->Array_Size];
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	template<typename _Left_Ty, size_t _Other>
	__forceinline typename Heap_Sort<_Ty, _Size> & Heap_Sort<_Ty, _Size>::operator=(const Heap_Sort<_Left_Ty, _Other> & Object)
	{
		if (this != _STD addressof(Object))
		{
			delete[] Heap_Array;
			delete[] Heap_Sorted;
			this->Array_Size = Object.Array_Size;
			this->Heap_Array = new _Heap_Element[this->Array_Size];
			this->Heap_Sorted = new _Heap_Element[this->Array_Size];
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	inline Heap_Sort<_Ty, _Size>::~Heap_Sort()
	{
		//delete[] Heap_Array;
		delete[] Heap_Sorted;
		this->Array_Size = 0;
	}

}

//PREDEFINED Objects



#endif /* _ALGORITHMS_LIBRARY_HEAP_SORT_HPP_ */
