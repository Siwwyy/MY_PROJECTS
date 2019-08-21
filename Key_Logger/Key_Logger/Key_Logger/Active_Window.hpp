
#ifndef ACTIVE_WINDOW_HPP_
#define ACTIVE_WINDOW_HPP_
#pragma once

#include <iostream>
#include <windows.h>
#include <string>

#include "Window.hpp"

#define NEW_LINE '\n'


namespace Window
{
	using _STD endl;
	using _STD cout;
	using _STD cerr;



	class Active_Window:
		public Window
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
		Active_Window();
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
		virtual ~Active_Window();		//wirtualny destruktor
		//////////////////////////////////////////////////////////////////////////////
	};

}

#endif /* ACTIVE_WINDOW_HPP_ */