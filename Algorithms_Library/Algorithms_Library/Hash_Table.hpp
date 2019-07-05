/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *					I hope that alghoritm will make right work
 *							Greetings for everyone!
 *						Hash_Table organized array by Key
*/
#pragma once
#ifndef _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_
#define _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_

namespace Algorithms_Hash_Table
{
	#include <iostream>
	#include <windows.h>
	#include <string>
	#include <vector>

	template<typename _Ty, size_t _Size>
	class Hash_Table
	{
	private:

		class _Hash_Element final
		{
		private:
			/*
				PRIVATE VARIABLES
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Ty Value;
			size_t Key;
			/////////////////////////////////////////////////////////////////////////////////////////////
		protected:
			/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////
		public:
			/*
				PUBLIC CONSTRUCTORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Hash_Element();
			_Hash_Element(const _Ty & Value, _CRT_GUARDOVERFLOW const size_t Key);
			_Hash_Element(const _Hash_Element & _Object);
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				SETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			void Set_Key(const size_t Key);
			void Set_Value(const _Ty & Value);
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				GETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			constexpr size_t Get_Key() const;
			constexpr _Ty & Get_Value() const;
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				OPERATORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Hash_Element & operator=(const _Hash_Element & _Object);
			constexpr bool operator<(const _Hash_Element & Object) const; // to compare(if the key is smaller)
			constexpr bool operator>(const _Hash_Element & Object) const; // to compare(if the key is bigger)
			constexpr bool operator==(const _Hash_Element & Object) const; // to compare(if the key is the same)
			constexpr bool operator!=(const _Hash_Element & Object) const; // to compare(if the key isn't the same)
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				DESTRUCTOR
			*/
			virtual ~_Hash_Element();
			/////////////////////////////////////////////////////////////////////////////////////////////
		};

	private:
		/*
			PRIVATE VARIABLES
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		_Ty * Hash_Table_Array;
		/////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		/////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////
	public:
		/*
			PUBLIC CONSTRUCTORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Hash_Table();
	/*	Hash_Table(const _Ty & Value, _CRT_GUARDOVERFLOW const size_t Key);*/
		Hash_Table(const Hash_Table & _Object);
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
	/*	constexpr size_t Get_Key() const;
		constexpr _Ty & Get_Value() const;*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Hash_Table & operator=(const Hash_Table & _Object);
		//constexpr bool operator<(const _Hash_Element & Object) const; // to compare(if the key is smaller)
		//constexpr bool operator>(const _Hash_Element & Object) const; // to compare(if the key is bigger)
		//constexpr bool operator==(const _Hash_Element & Object) const; // to compare(if the key is the same)
		//constexpr bool operator!=(const _Hash_Element & Object) const; // to compare(if the key isn't the same)
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUCTOR
		*/
		virtual ~Hash_Table();
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


	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::_Hash_Element() :
		Value(NULL),
		Key(NULL)
	{
		//
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::_Hash_Element(const _Ty & Value, const size_t Key) :
		Value(Value),
		Key(NULL)
	{
		//
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::_Hash_Element(const _Hash_Element & _Object) :
		Value(_Object.Value),
		Key(_Object.Key)
	{
		//
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::_Hash_Element::Set_Key(const size_t Key)
	{
		if (Key < 0)
		{
			this->Key = ((-1) * Key);
		}
		else
		{
			this->Key = Key;
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::_Hash_Element::Set_Value(const _Ty & Value)
	{
		this->Value = Value;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr size_t Hash_Table<_Ty, _Size>::_Hash_Element::Get_Key() const
	{
		return this->Key;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr _Ty & Hash_Table<_Ty, _Size>::_Hash_Element::Get_Value() const
	{
		return this->Value;
	}

	template<typename _Ty, size_t _Size>
	__forceinline typename Hash_Table<_Ty, _Size>::_Hash_Element & Hash_Table<_Ty, _Size>::template _Hash_Element::operator=(const _Hash_Element & _Object)
	//__forceinline typename Hash_Table<_Ty, _Size>::_Hash_Element & Hash_Table<_Ty, _Size> _Hash_Element::operator=(const _Hash_Element & _Object)
	{
		if (this != _STD addressof(_Object))
		{
			this->Value = _Object.Value;
			this->Key = _Object.Key;
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Hash_Table<_Ty, _Size>::_Hash_Element::operator<(const _Hash_Element & Object) const
	{
		return _STD tie(this->Key) < _STD tie(Object.Key);
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Hash_Table<_Ty, _Size>::_Hash_Element::operator>(const _Hash_Element & Object) const
	{
		return !(*this < Object) && (*this != Object);
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Hash_Table<_Ty, _Size>::_Hash_Element::operator==(const _Hash_Element & Object) const
	{
		return !(*this < Object) && !(Object < *this);
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Hash_Table<_Ty, _Size>::_Hash_Element::operator!=(const _Hash_Element & Object) const
	{
		return !(*this == Object);
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::~_Hash_Element()
	{
		Value = NULL;
		Key = NULL;
	}


	////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	/*
		_Hash_Table CLASS METHOD'S BODIES
	*/
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////


	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::Hash_Table()
	{
		this->Hash_Table_Array = new _Ty[_Size];
		for (size_t i{}; i < _Size; ++i)
		{
			std::cout << Hash_Table_Array[i] << ' ';
		}
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::~Hash_Table()
	{
		std::cout << "Destruct" << std::endl;
		delete[] Hash_Table_Array;
		//delete Hash_Table_Array;
	}

}

#endif /* _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_ */