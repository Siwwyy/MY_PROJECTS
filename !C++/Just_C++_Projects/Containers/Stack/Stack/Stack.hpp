// _STACK_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
*/

#ifndef _STACK_H_
#define _STACK_H_
#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <xmemory>
#include <stdexcept>
#include <typeinfo>

namespace MyStack	//namspace 
{
	template<typename _Ty>
	class Stack
	{
		//Contained class
		class _Elem
		{
		public:
			/*
				VARIABLES PRIVATE
			*/
			_Elem * next;
			_Ty value;
			//////////////////////////////////////////////////////
		public:
			/*
				KONSTRUKTORY PUBLIC
			*/
			explicit _Elem()
			{
				this->next = nullptr;
				this->value = NULL;
			}

			explicit _Elem(const _Ty & value)
			{
				this->next = nullptr;
				this->value = value;
			}

			explicit _Elem(const _Elem & _Ty_Object) :
				next(_Ty_Object.next),
				value(_Ty_Object.value)
			{
				//nothing here
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
					delete next;
					this->next = _Right.next;
					this->value = _Right.value;
				}
				return *this;
			}

			//////////////////////////////////////////////////////
			/*
				DESTRUCTOR
			*/
			virtual ~_Elem()
			{
				this->next = nullptr;
				this->value = NULL;
				delete next;
			}
			//////////////////////////////////////////////////////
		};
		//////////////////////////////////////////////////////
	private:
		/*
			VARIABLES PRIVATE
		*/
		_Elem * top;
		_Elem * current;
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
		/*static_assert(!_STD is_const_v<_Ty>, "Standard C++ nie pozwala na aloakacje stalego typu kontenera (bledny format std::allocator<const T>");*/
		//////////////////////////////////////////////////////
		/*
			KONSTRUKTORY PUBLIC
		*/
		Stack();
		Stack(const Stack & Object);
		//////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/
		__forceinline void push(const _Ty & value);
		__forceinline void Clear_Stack();
		__forceinline _Ty pop();
		//////////////////////////////////////////////////////
		/*
			SETTERY PUBLIC
		*/

		//////////////////////////////////////////////////////
		/*
			GETTERY PUBLIC
		*/
		size_t get_size() const;
		//////////////////////////////////////////////////////
		/*
			OPERATORY PUBLIC
		*/
		Stack & operator=(const Stack<_Ty> & _Right);
		//////////////////////////////////////////////////////
		/*
			DESTRUKTOR
		*/
		virtual ~Stack();
		//////////////////////////////////////////////////////
	};

	
	template<typename _Ty>
	__forceinline Stack<_Ty>::Stack():
		top(nullptr)
	{

	}

	template<typename _Ty>
	__forceinline Stack<_Ty>::Stack(const Stack & Object):
		top(Object.top)
	{

	}

	template<typename _Ty>
	__forceinline void Stack<_Ty>::push(const _Ty & value)
	{
		this->current = (new _Elem(value));
		this->current->next = this->top;
		this->top = this->current;
		++size;
	}

	template<typename _Ty>
	__forceinline void Stack<_Ty>::Clear_Stack()
	{
		for (size_t i = 0; i < size; ++i)
		{
			this->current = this->top->next;
			delete top;
			this->top = this->current;
		}
		size = 0;
	}

	template<typename _Ty>
	__forceinline _Ty Stack<_Ty>::pop()
	{
	/*	if (size == 0)
		{
			return _Ty;
		}
		else
		{*/
			--size;
			_Ty temporary = top->value;//		std::cout << top->value << std::endl;
			this->current = this->top->next;
			delete top;
			this->top = this->current;
			return temporary;
		//}
	}

	template<typename _Ty>
	__forceinline size_t Stack<_Ty>::get_size() const
	{
		return this->size;
	}

	template<typename _Ty>
	__forceinline Stack<_Ty> & Stack<_Ty>::operator=(const Stack<_Ty> & _Right)
	{
		if (this != _STD addressof(_Right))
		{
			//for (size_t i = 0; i < size; ++i)
			//{
			//	if (i == 0)
			//	{

			//	}
			//}
			//this->beginning = _Right.beginning;
			this->top = _Right.top;
			//this->top = _Right->top;
		}
		return *this;
	}

	template<typename _Ty>
	__forceinline Stack<_Ty>::~Stack()
	{
		top = nullptr;
		current = nullptr;
	}

}

#endif /* _STACK_H_ */