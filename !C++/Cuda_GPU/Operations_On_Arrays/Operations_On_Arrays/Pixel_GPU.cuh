// _OBRAZ_H_ standard header

/*
	Typical pixel range is from 0 to 255 (for each color palette R, G and B)
*/

#ifndef _PIXEL_GPU_H_
#define _PIXEL_GPU_H_
#pragma once

#define NEW_LINE '\n'

#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

namespace RGB_GPU
{

	class Pixel_GPU
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
		__device__ Pixel_GPU();
		__device__ explicit Pixel_GPU(const unsigned char R, const unsigned char G, const unsigned char B);
		__device__ Pixel_GPU(const Pixel_GPU& Object);
		//////////////////////////////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/
		__device__ void Show_Object() const;
		//////////////////////////////////////////////////////////////////////////////
		/*
			SETTERY
		*/
		__device__ void Set_R(const unsigned char R);
		__device__ void Set_G(const unsigned char G);
		__device__ void Set_B(const unsigned char B);
		//////////////////////////////////////////////////////////////////////////////
		/*
			GETTERY
		*/
		__device__ constexpr char Get_R() const;
		__device__ constexpr char Get_G() const;
		__device__ constexpr char Get_B() const;
		//////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORY
		*/
		//JEDNOARGUMENTOWE
		//Pixel& operator=(const Pixel& Object);
		__device__ Pixel_GPU& operator=(const Pixel_GPU& Object);
		//////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUKTOR
		*/
		virtual ~Pixel_GPU();
		//////////////////////////////////////////////////////////////////////////////
	};

	Pixel_GPU::Pixel_GPU() :
		R(NULL),
		G(NULL),
		B(NULL)
	{

	}

	Pixel_GPU::Pixel_GPU(const unsigned char R, const unsigned char G, const unsigned char B) :
		R(R),
		G(G),
		B(B)
	{

	}

	Pixel_GPU::Pixel_GPU(const Pixel_GPU& Object) :
		R(Object.R),
		G(Object.G),
		B(Object.B)
	{

	}

	__device__ void Pixel_GPU::Show_Object() const
	{
		//_STD cout << "Red: [" << this->R << " ] " << "Green: [" << this->G << " ] " << "Blue: [" << this->B << " ] " << NEW_LINE;
	}

	__device__ void Pixel_GPU::Set_R(const unsigned char R)
	{
		this->R = R;
	}

	__device__ void Pixel_GPU::Set_G(const unsigned char G)
	{
		this->G = G;
	}

	__device__ void Pixel_GPU::Set_B(const unsigned char B)
	{
		this->B = B;
	}

	__device__ char Pixel_GPU::Get_R() const
	{
		return this->R;
	}

	__device__ char Pixel_GPU::Get_G() const
	{
		return this->G;
	}

	__device__ char Pixel_GPU::Get_B() const
	{
		return this->B;
	}

	__device__ Pixel_GPU& Pixel_GPU::operator=(const Pixel_GPU& Object)
	{
		if (this != _STD addressof(Object))
		{
			this->R = Object.R;
			this->G = Object.G;
			this->B = Object.B;
		}
		return *this;
	}

	Pixel_GPU::~Pixel_GPU()
	{
		this->R = NULL;
		this->B = NULL;
		this->B = NULL;
	}

}

#endif /* _PIXEL_GPU_H_ */