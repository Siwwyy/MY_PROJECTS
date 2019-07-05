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

		template<typename _Ty>
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

		public:
			/*
				PUBLIC CONSTRUCTORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Hash_Element():
				Value(NULL),
				Key(NULL)
			{
				//
			}

			_Hash_Element(const _Ty Value, _CRT_GUARDOVERFLOW const size_t Key)
			{
				//
			}

			_Hash_Element(const _Hash_Element & _Object):
				Value(_Object.Value),
				Key(_Object.Key)
			{
				//
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				SETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			void Set_Key(const size_t Key)
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

			void Set_Value(const _Ty & Value)
			{
				this->Value = Value;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				GETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				OPERATORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Hash_Element & operator=(const _Hash_Element & _Object)
			{
				if (this != _STD addressof(_Object))
				{
					this->Value = _Object.Value;
					this->Key = _Object.Key;
				}
				return *this;
			}

			constexpr bool operator<(const _Hash_Element & Object) const
			{
				return _STD tie(this->Key) < _STD tie(Object.Key);
			} // to compare(if the key is smaller)

			constexpr bool operator>(const _Hash_Element & Object) const
			{
				return !(*this < Object) && (*this != Object);
			} // to compare(if the key is bigger)

			constexpr bool operator==(const _Hash_Element & Object) const
			{
				return !(*this < Object) && !(Object < *this);
			} // to compare(if the key is the same)

			constexpr bool operator!=(const _Hash_Element & Object) const
			{
				return !(*this == Object);
			} // to compare(if the key isn't the same)
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				DESTRUCTOR
			*/
			virtual ~_Hash_Element() { Value = NULL; Key = NULL; };
			/////////////////////////////////////////////////////////////////////////////////////////////
		};

	private:

	protected:

	public:
	};

}

#endif /* _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_ */