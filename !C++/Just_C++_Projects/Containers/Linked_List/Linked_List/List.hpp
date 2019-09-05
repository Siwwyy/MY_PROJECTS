// _LIST_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
*/

#ifndef _LIST_H_
#define _LIST_H_
#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <xmemory>
#include <stdexcept>
#include <typeinfo>

namespace MyList	//namspace 
{
	template<typename _Ty>
	class List
	{
		//Contained class
		class _Elem
		{
		public:
			/*
				VARIABLES PRIVATE
			*/
			_Elem * previous;
			_Elem * next;
			_Ty value;
			//////////////////////////////////////////////////////
		public:
			/*
				KONSTRUKTORY PUBLIC
			*/
			explicit _Elem()
			{
				this->previous = nullptr;
				this->next = nullptr;
				this->value = NULL;
			}

			explicit _Elem(const _Ty & value)
			{
				this->previous = nullptr;
				this->next = nullptr;
				this->value = value;
			}

			explicit _Elem(const _Elem & _Ty_Object):
				previous(_Ty_Object.previous),
				next(_Ty_Object.next),
				value(_Ty_Object.value)
			{
				//nothing here
			}

			explicit _Elem(const _Elem && _Ty_Object) 
			{
				this->previous = _Ty_Object.previous;
				this->next = _Ty_Object.next;
				this->value = _Ty_Object.value;
				delete _Ty_Object->previous;
				delete _Ty_Object->next;
				_Ty_Object->value = 0;
			}


			/*
				PUBLIC FUNCTIONS
			*/
			
			//////////////////////////////////////////////////////

			/*
				OPERATOR OF ASSIGNMENT
			*/
			template<typename _Ty>
			_Elem & operator=(const _Elem & _Right)
			{
				if (this != _STD addressof(_Right))
				{
					delete previous;
					delete next;
					this->previous = _Right.previous;
					this->next = _Right.next;
					this->value = _Right.value;
				}
				return *this;
			}

			/*
				OPERATOR OF MOVE SEMANTIC
			*/

			template<typename _Ty>
			_Elem & operator=(const _Elem && _Right)
			{
				if (this != _STD addressof(_Right))
				{
					this->previous = _Right.previous;
					this->next = _Right.next;
					std::swap(this->value, _Right.value);
					delete _Right->previous;
					delete _Right->next;
					_Right->value = 0;
				}
				return *this;
			}
			//////////////////////////////////////////////////////
			/*
				DESTRUCTOR
			*/
			virtual ~_Elem()
			{
				this->previous = nullptr;
				this->next = nullptr;
				this->value = NULL;
				delete previous;
				delete next;
			}
			//////////////////////////////////////////////////////
		};
		//////////////////////////////////////////////////////
	private:
		/*
			VARIABLES PRIVATE
		*/
		_Elem * beginning;
		_Elem * current;
		_Elem * end;
		size_t size;
		//////////////////////////////////////////////////////
	protected:
		/*
			VARIABLES PROTECTED
		*/

		//////////////////////////////////////////////////////
	public:
		/*
			ASSERTS
		*/
		static_assert(!_STD is_const_v<_Ty>, "Standard C++ nie pozwala na aloakacje stalego typu kontenera (bledny format std::allocator<const T>");
		//////////////////////////////////////////////////////
		/*
			KONSTRUKTORY PUBLIC
		*/
		List();
		List(const List & Object);
		//////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/
		__forceinline void push(const _Ty & value);
		__forceinline _Ty pop_front() const;
		__forceinline void pop_everything();
		__forceinline void Clear_List();
		//////////////////////////////////////////////////////
		/*
			SETTERY PUBLIC
		*/
		
		//////////////////////////////////////////////////////
		/*
			GETTERY PUBLIC
		*/
		
		//////////////////////////////////////////////////////
		/*
			OPERATORY PUBLIC
		*/
		List & operator=(const List<_Ty> & _Right);
		//////////////////////////////////////////////////////
		/*
			DESTRUKTOR
		*/
		virtual ~List();
		//////////////////////////////////////////////////////
	};

	/*
		STATIC INITIALIZATION
	*/
	/*template<typename _Ty>
	size_t List<_Ty>::size = 0;*/
	//////////////////////////////////////////////////////

	template<typename _Ty>
	__forceinline List<_Ty>::List()
	{
		this->beginning = nullptr;
		this->end = nullptr;
	}

	template<typename _Ty>
	__forceinline List<_Ty>::List(const List & Object)
	{
		if (Object.size > 0)
		{
			this->beginning = Object.beginning;
			this->current = Object.beginning->next;
			this->end = Object.end;
			this->size = Object.size;
		}
		else
		{
			std::cerr << "[WARNING::2021 " << "You cannot copy empty List<_Ty> to other List<_Ty>" << " ]" << '\n';
		}
	}

	template<typename _Ty>
	__forceinline void List<_Ty>::push(const _Ty & value)
	{
		if (this->size == 0)
		{
			this->beginning = (new _Elem(value));
		}
		else if (this->size == 1)
		{
			this->end = (new _Elem(value));
			this->beginning->next = this->end;
			this->end->previous = this->beginning;
		}
		else
		{
			this->current = this->end;
			this->end = (new _Elem(value));
			this->current->next = this->end;
			this->end->previous = this->current;
		}
		++(this->size);
	}

	template<typename _Ty>
	__forceinline _Ty List<_Ty>::pop_front() const
	{
		if (this->size == 0)
		{
			return this->beginning->value;
		}
		else
		{
			return this->end->previous->value;
		}
	}

	template<typename _Ty>
	__forceinline void List<_Ty>::pop_everything() 
	{
		//Show list from end to beginning
		if (this->size > 0)
		{
			current = this->end;
			for (size_t i = 0; i < this->size; ++i)
			{
				std::cout << this->current->value << ' ';
				current = this->current->previous;
			}

			std::cout << '\n';

			//Show list from beginning to end
			current = this->beginning;
			for (size_t i = 0; i < this->size; ++i)
			{
				std::cout << this->current->value << ' ';
				current = this->current->next;
			}
			std::cout << '\n';
		}
		else
		{
			std::cerr << "[WARNING::2022 " << "You cannot display an empty List<_Ty> when List<_Ty>::size = 0" << " ]" << '\n';
		}
	}

	template<typename _Ty>
	__forceinline void List<_Ty>::Clear_List()
	{
		_Elem * _HOOK = nullptr;
		current = this->end;
		for (size_t i = 0; i < this->size; ++i)
		{
			_HOOK = this->current->previous;
			current->~_Elem();
			current = _HOOK;
		}
		this->size = 0;
	}

	template<typename _Ty>
	__forceinline List<_Ty> & List<_Ty>::operator=(const List<_Ty> & _Right)
	{
		if (this != _STD addressof(_Right))
		{
			delete beginning;
			delete end;
			this->beginning = _Right.beginning;
			this->current = _Right.current;
			this->end = _Right.end;
			this->value = _Right.value;
			this->size = _Right.size;
		}
		return *this;
	}

	template<typename _Ty>
	__forceinline List<_Ty>::~List()
	{
		Clear_List();
		this->beginning = nullptr;
		this->current = nullptr;
		this->end = nullptr;
		this->size = 0;
	}

}

#endif /* _LIST_H_ */