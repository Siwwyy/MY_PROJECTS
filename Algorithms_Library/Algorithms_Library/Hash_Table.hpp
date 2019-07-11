/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
 *					I hope that alghoritm will make right work
 *							Greetings for everyone!
 *						Hash_Table organized array by Key
*/
#pragma once
#ifndef _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_
#define _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_

#include <iostream>
#include <windows.h>
#include <string>

namespace Algorithms_Hash_Table
{
	using std::cerr;
	using std::endl;
	using std::cout;

	//template<typename _Ty_Left, typename _Ty_Right>
	//void __stdcall __swap(_Ty_Left & _Left, _Ty_Right & _Right) noexcept
	//{
	//	/*
	//		int x = 10, y = 5;
	//		// Code to swap 'x' (1010) and 'y' (0101)
	//		x = x ^ y; // x now becomes 15 (1111)
	//		y = x ^ y; // y becomes 10 (1010)
	//		x = x ^ y; // x becomes 5 (0101)
	//	*/
	//	//Swapping without the temporary variable
	//	_Left = _Left ^ _Right;
	//	_Right = _Left ^ _Right;
	//	_Left = _Left ^ _Right;
	//}


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
			__int64 Key;
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
			_Hash_Element(const _Ty & Value, _CRT_GUARDOVERFLOW const __int64 Key);
			_Hash_Element(const _Hash_Element & Object);
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				SETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			void Set_Key(const __int64 Key);
			void Set_Value(const _Ty & Value);
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				GETTERS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			constexpr __int64 Get_Key() const;
			constexpr size_t Get_Index(const size_t & array_length) const;
			constexpr _Ty Get_Value() const;
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				OPERATORS
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////
			_Hash_Element & operator=(const _Hash_Element & Object);
			constexpr bool operator<(const _Hash_Element & Object) const; // to compare(if the key is smaller)
			constexpr bool operator>(const _Hash_Element & Object) const; // to compare(if the key is bigger)
			constexpr bool operator==(const _Hash_Element & Object) const; // to compare(if the key is the same)
			constexpr bool operator!=(const _Hash_Element & Object) const; // to compare(if the key isn't the same)
			friend std::ostream & operator<<(std::ostream & lhs, const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element & rhs)
			{
				if (rhs.Get_Key() >= 0)
				{
					lhs << "[ " << rhs.Get_Value() << ' ' << rhs.Get_Key() << " ]\n";
				}
				return lhs;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			/*
				DESTRUCTOR
			*/
			virtual ~_Hash_Element();
			/////////////////////////////////////////////////////////////////////////////////////////////
		};
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			PRIVATE FUNCTIONS
		*/
		void hash_table_organizer(const size_t deleted_element_index, const __int64 deleted_key);
		//const bool operator()(const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element & lhs, const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element & rhs) const;
		const bool operator()(const size_t & index) const;
		const bool if_same_value_exist(const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element * Object) const;
		/////////////////////////////////////////////////////////////////////////////////////////////
	private:
		/*
			PRIVATE VARIABLES
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		_Hash_Element * Hash_Table_Array;
		size_t Hash_Table_Size;
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
		Hash_Table(const Hash_Table & Object);
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			PUBLIC FUNCTIONS
		*/
		void __fastcall push(const _Ty & Value, const __int64 Key);
		void delete_element(const __int64 Key);
		void show_elements() const;
		void resize_array(const size_t new_size);
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
		constexpr size_t Get_Hash_Table_Size() const;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORS
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Hash_Table & operator=(const Hash_Table & Object);

		template<size_t _Other>
		Hash_Table & operator=(const Hash_Table<_Ty, _Other> & Object);

		template<typename _Left_Ty>
		Hash_Table & operator=(const Hash_Table<_Left_Ty, _Size> & Object);

		template<typename _Left_Ty, size_t _Other>
		Hash_Table & operator=(const Hash_Table<_Left_Ty, _Other> & Object);
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

	/*
		FRIEND METHOD's SPACE
	*/



	/////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::_Hash_Element():
		Key(-1)
	{
		//
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::_Hash_Element(const _Ty & Value, const __int64 Key) :
		Value(Value),
		Key(Key)
	{
		//
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::_Hash_Element(const _Hash_Element & Object) :
		Value(Object.Value),
		Key(Object.Key)
	{
		//
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::_Hash_Element::Set_Key(const __int64 Key)
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
	__forceinline constexpr __int64 Hash_Table<_Ty, _Size>::_Hash_Element::Get_Key() const
	{
		return this->Key;
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr size_t Hash_Table<_Ty, _Size>::_Hash_Element::Get_Index(const size_t & array_length) const
	{
		//return (this->Key % array_length) % array_length;
		return (this->Key % array_length);
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr _Ty Hash_Table<_Ty, _Size>::_Hash_Element::Get_Value() const
	{
		return this->Value;
	}

	template<typename _Ty, size_t _Size>
	__forceinline typename Hash_Table<_Ty, _Size>::_Hash_Element & Hash_Table<_Ty, _Size>::template _Hash_Element::operator=(const _Hash_Element & Object)
	//__forceinline typename Hash_Table<_Ty, _Size>::_Hash_Element & Hash_Table<_Ty, _Size> _Hash_Element::operator=(const _Hash_Element & Object)
	{
		if (this != _STD addressof(Object))
		{
			this->Value = Object.Value;
			this->Key = Object.Key;
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
		return _STD tie(this->Value, this->Key) == _STD tie(Object.Value, Object.Key);
		//return !(*this < Object) && !(Object < *this);
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr bool Hash_Table<_Ty, _Size>::_Hash_Element::operator!=(const _Hash_Element & Object) const
	{
		return !(*this == Object);
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::_Hash_Element::~_Hash_Element()
	{
		/*std::cout << "Destruct" << std::endl;*/
		Key = -1;
	}


	////////////////////////////////////////////////////
	////////////////////////////////////////////////////
	/*
		_Hash_Table CLASS METHOD'S BODIES
	*/
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////


	/*template<typename _Ty, size_t _Size>
	__forceinline const bool Hash_Table<_Ty, _Size>::operator()(const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element & lhs, const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element & rhs) const
	{
		return _STD tie(rhs) == _STD tie(lhs);
	}*/

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::hash_table_organizer(const size_t deleted_element_index, const __int64 deleted_key)
	{
		for (size_t i{}; i < this->Hash_Table_Size; ++i)
		{	
			if (Hash_Table_Array[i].Get_Index(Hash_Table_Size) != i && Hash_Table_Array[i].Get_Key() >= 0 /*&& Hash_Table_Array[Hash_Table_Array[i].Get_Index(Hash_Table_Size)].Get_Key() == -1*/)
			{
				if (i >= Hash_Table_Array[i].Get_Index(Hash_Table_Size))
				{
					//std::cout << Hash_Table_Array[i] << i << '\n';
				//	bool found_place = false;
					for (__int32 j{ static_cast<__int32>(i) }; j >= 0; --j)
					{
						if (Hash_Table_Array[j].Get_Key() == -1)
						{
						//	found_place = true;
							std::swap(Hash_Table_Array[static_cast<size_t>(j)], Hash_Table_Array[i]);
							break;
						}
					}
					//if(found_place)
				}
				else if(i < Hash_Table_Array[i].Get_Index(Hash_Table_Size))
				{
					for (size_t j{}; j <= Hash_Table_Array[i].Get_Index(Hash_Table_Size); ++j)
					{
						if (Hash_Table_Array[j].Get_Key() == -1)
						{
							//	found_place = true;
							std::swap(Hash_Table_Array[static_cast<size_t>(j)], Hash_Table_Array[i]);
							break;
						}
					}
				}
			}
		}
		//issue with indexing 230 % 11 isn't equal to 0, but my algorithm says different

		//for (size_t i{}; i < this->Hash_Table_Size; ++i)
		//{
		//	if (Hash_Table_Array[i].Get_Index(Hash_Table_Size) != i && Hash_Table_Array[i].Get_Key() >= 0 /*&& Hash_Table_Array[Hash_Table_Array[i].Get_Index(Hash_Table_Size)].Get_Key() == -1*/)
		//	{
		//		if (i >= Hash_Table_Array[i].Get_Index(Hash_Table_Size))
		//		{
		//			//std::cout << Hash_Table_Array[i] << i << '\n';
		//		//	bool found_place = false;
		//			for (__int32 j{ static_cast<__int32>(i) }; j >= 0; --j)
		//			{
		//				if (Hash_Table_Array[j].Get_Key() == -1)
		//				{
		//					//	found_place = true;
		//					std::swap(Hash_Table_Array[static_cast<size_t>(j)], Hash_Table_Array[i]);
		//					break;
		//				}
		//			}
		//			//if(found_place)
		//		}
		//		else if (i < Hash_Table_Array[i].Get_Index(Hash_Table_Size))
		//		{
		//			for (size_t j{}; j <= Hash_Table_Array[i].Get_Index(Hash_Table_Size); ++j)
		//			{
		//				if (Hash_Table_Array[j].Get_Key() == -1)
		//				{
		//					//	found_place = true;
		//					std::swap(Hash_Table_Array[static_cast<size_t>(j)], Hash_Table_Array[i]);
		//					break;
		//				}
		//			}
		//		}
		//	}
		//}
	}

	template<typename _Ty, size_t _Size>
	__forceinline const bool Hash_Table<_Ty, _Size>::operator()(const size_t & index) const
	{
		//if (Hash_Table_Array[position] == nullptr)
		if (Hash_Table_Array[index].Get_Key() == -1)
		{
			return true;
		}
		return false;
	}

	template<typename _Ty, size_t _Size>
	__forceinline const bool Hash_Table<_Ty, _Size>::if_same_value_exist(const typename Algorithms_Hash_Table::Hash_Table<_Ty, _Size>::_Hash_Element * Object) const
	{
		for (size_t i{}; i < this->Hash_Table_Size; ++i)
		{
			if ((this->Hash_Table_Array[i]) == *(Object))
			{
				return true;
			}
		}
		return false;
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::Hash_Table()
	{
		this->Hash_Table_Size = _Size;
		this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::Hash_Table(const Hash_Table & Object)
	{
		this->Hash_Table_Size = Object.Hash_Table_Size;
		this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
		for (size_t i{}; i < this->Hash_Table_Size; ++i)
		{
			this->Hash_Table_Array[i] = Object.Hash_Table_Array[i];
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void __fastcall Hash_Table<_Ty, _Size>::push(const _Ty & Value, const __int64 Key)
	{
		_Hash_Element temporary(Value, Key);
		if (if_same_value_exist(&temporary) == true || operator()(temporary.Get_Index(this->Hash_Table_Size)) == true)
		{
			Hash_Table_Array[temporary.Get_Index(this->Hash_Table_Size)] = temporary;
		}
		else
		{
			bool found_slot = false;
			for (size_t i{ temporary.Get_Index(this->Hash_Table_Size) }; i < this->Hash_Table_Size; ++i)
			{
				if (operator()(i) == true)
				{
					Hash_Table_Array[i] = temporary;
					found_slot = true;
					break;
				}
			}
			if (found_slot == false)
			{
				for (size_t i{}; i < this->Hash_Table_Size; ++i)
				{
					if (operator()(i) == true)
					{
						Hash_Table_Array[i] = temporary;
						break;
					}
				}
			}
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::delete_element(const __int64 Key)
	{
		for (size_t i{}; i < this->Hash_Table_Size; ++i)
		{
			if (Hash_Table_Array[i].Get_Key() == Key)
			{
				const size_t deleted_element_index = i;
				const __int64 deleted_key = Hash_Table_Array[i].Get_Key();
				Hash_Table_Array[i].~_Hash_Element();
				hash_table_organizer(deleted_element_index, deleted_key);
				break;
			}
		}
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::show_elements() const
	{
		for (size_t i{}; i < this->Hash_Table_Size; ++i)
		{
			//operator<<(std::cout, Hash_Table_Array[i]);
			if (Hash_Table_Array[i].Get_Key() >= 0)
			{
				std::cout << (i) << ' ' << Hash_Table_Array[i];
			}
		}
		//std::cout << "--------------------------------------------- \n";
		std::cout << '\n';
	}

	template<typename _Ty, size_t _Size>
	__forceinline void Hash_Table<_Ty, _Size>::resize_array(const size_t new_size)
	{
		delete[] this->Hash_Table_Array;
		this->Hash_Table_Size = new_size;
		this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
	}

	template<typename _Ty, size_t _Size>
	__forceinline constexpr size_t Hash_Table<_Ty, _Size>::Get_Hash_Table_Size() const
	{
		return this->Hash_Table_Size;
	}

	template<typename _Ty, size_t _Size>
	__forceinline typename Hash_Table<_Ty, _Size> & Hash_Table<_Ty, _Size>::operator=(const Hash_Table & Object)
	{
		if (this != _STD addressof(Object))
		{
			delete[] Hash_Table_Array;
			this->Hash_Table_Size = Object.Hash_Table_Size;
			this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
			for (size_t i{}; i < this->Hash_Table_Size; ++i)
			{
				this->Hash_Table_Array[i] = Object.Hash_Table_Array[i];
			}
		}
		return *this;
	}

	template<typename _Ty, size_t _Size>
	template<size_t _Other>
	__forceinline typename Hash_Table<_Ty, _Size> & Hash_Table<_Ty, _Size>::operator=(const Hash_Table<_Ty, _Other> & Object)
	{
		delete[] Hash_Table_Array;
		this->Hash_Table_Size = Object.Get_Hash_Table_Size();
		this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
		return *this;
	}

	template<typename _Ty, size_t _Size>
	template<typename _Left_Ty>
	__forceinline typename Hash_Table<_Ty, _Size> & Hash_Table<_Ty, _Size>::operator=(const Hash_Table<_Left_Ty, _Size> & Object)
	{
		delete[] Hash_Table_Array;
		this->Hash_Table_Size = Object.Get_Hash_Table_Size();
		this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
		return *this;
	}

	template<typename _Ty, size_t _Size>
	template<typename _Left_Ty, size_t _Other>
	__forceinline typename Hash_Table<_Ty, _Size> & Hash_Table<_Ty, _Size>::operator=(const Hash_Table<_Left_Ty, _Other> & Object)
	{
		delete[] Hash_Table_Array;
		this->Hash_Table_Size = Object.Get_Hash_Table_Size();
		this->Hash_Table_Array = new _Hash_Element[this->Hash_Table_Size];
		return *this;
	}

	template<typename _Ty, size_t _Size>
	inline Hash_Table<_Ty, _Size>::~Hash_Table()
	{
		//std::cout << "Destruct" << std::endl;
		delete[] Hash_Table_Array;
		Hash_Table_Size = NULL;
	}

}

//PREDEFINED Objects

typedef Algorithms_Hash_Table::Hash_Table<int, 10> int_10;
typedef Algorithms_Hash_Table::Hash_Table<int, 20> int_20;
typedef Algorithms_Hash_Table::Hash_Table<int, 30> int_30;
typedef Algorithms_Hash_Table::Hash_Table<int, 40> int_40;

typedef Algorithms_Hash_Table::Hash_Table<float, 10> float_10;
typedef Algorithms_Hash_Table::Hash_Table<float, 20> float_20;
typedef Algorithms_Hash_Table::Hash_Table<float, 30> float_30;
typedef Algorithms_Hash_Table::Hash_Table<float, 40> float_40;

typedef Algorithms_Hash_Table::Hash_Table<char, 10> char_10;
typedef Algorithms_Hash_Table::Hash_Table<char, 20> char_20;
typedef Algorithms_Hash_Table::Hash_Table<char, 30> char_30;
typedef Algorithms_Hash_Table::Hash_Table<char, 40> char_40;

typedef Algorithms_Hash_Table::Hash_Table<const char, 10> const_char_10;
typedef Algorithms_Hash_Table::Hash_Table<const char, 20> const_char_20;
typedef Algorithms_Hash_Table::Hash_Table<const char, 30> const_char_30;
typedef Algorithms_Hash_Table::Hash_Table<const char, 40> const_char_40;

typedef Algorithms_Hash_Table::Hash_Table<const char *, 10> const_char_astrix_10;
typedef Algorithms_Hash_Table::Hash_Table<const char *, 20> const_char_astrix_20;
typedef Algorithms_Hash_Table::Hash_Table<const char *, 30> const_char_astrix_30;
typedef Algorithms_Hash_Table::Hash_Table<const char *, 40> const_char_astrix_40;

typedef Algorithms_Hash_Table::Hash_Table<std::string, 10> string_10;
typedef Algorithms_Hash_Table::Hash_Table<std::string, 20> string_20;
typedef Algorithms_Hash_Table::Hash_Table<std::string, 30> string_30;
typedef Algorithms_Hash_Table::Hash_Table<std::string, 40> string_40;

#endif /* _ALGORITHMS_LIBRARY_HASH_TABLE_HPP_ */