
#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#pragma once

#include <iostream>
#include <windows.h>
#include <string>

#define NEW_LINE '\n'


namespace Window
{
	using _STD endl;
	using _STD cout;
	using _STD cerr;



	class Window
	{
	private:
		/*
			ZMIENNE PRIVATE
		*/

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
		__int32 width;
		__int32 height;
		char * window_name;
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
		/*
			ZMIENNE PUBLIC
		*/

		//////////////////////////////////////////////////////////////////////////////
		/*
			KONSTRUKTORY PUBLIC
		*/
		Window();
		//////////////////////////////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/

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
		virtual ~Window();		//wirtualny destruktor
		//////////////////////////////////////////////////////////////////////////////
	};

}

#endif /* WINDOW_HPP_ */