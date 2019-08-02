// _OBRAZ_H_ standard header

/*
	Typical pixel range is from 0 to 255 (for each color palette R, G and B)	
*/

#ifndef _PIXEL_H_
#define _PIXEL_H_
#pragma once

#define NEW_LINE '\n'

#include <iostream>

namespace RGB
{


	class Pixel
	{
	private:
		/*
			PRIVATE VARIABLES
		*/
		unsigned char R;
		unsigned char G;
		unsigned char B;
		//////////////////////////////////////////////////////////////////////////////
	protected:
		/*
			PROTECTED VARIABLES
		*/

		//////////////////////////////////////////////////////////////////////////////
	public:
		/*
			KONSTRUKTORY
		*/
		Pixel();
		explicit Pixel(const unsigned char R, const unsigned char G, const unsigned char B);
		Pixel(const Pixel & Object);
		//////////////////////////////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/
		void Show_Object() const;
		//////////////////////////////////////////////////////////////////////////////
		/*
			SETTERY
		*/
		void Set_R(const unsigned char R);
		void Set_G(const unsigned char G);
		void Set_B(const unsigned char B);
		//////////////////////////////////////////////////////////////////////////////
		/*
			GETTERY
		*/
		constexpr char Get_R() const;
		constexpr char Get_G() const;
		constexpr char Get_B() const;
		//////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORY
		*/
		//JEDNOARGUMENTOWE
		Pixel& operator=(const Pixel& Object);
		//////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUKTOR
		*/
		virtual ~Pixel();	
		//////////////////////////////////////////////////////////////////////////////
	};

}

#endif /* _PIXEL_H_ */