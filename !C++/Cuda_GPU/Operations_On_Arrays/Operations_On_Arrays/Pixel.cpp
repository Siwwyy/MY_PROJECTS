#include "Pixel.hpp"



RGB::Pixel::Pixel() :
	R(NULL),
	G(NULL),
	B(NULL)
{
}

RGB::Pixel::Pixel(const unsigned char R, const unsigned char G, const unsigned char B):
	R(R),
	G(G),
	B(B)
{
	//
}

RGB::Pixel::Pixel(const Pixel& Object) :
	R(Object.R),
	G(Object.G),
	B(Object.B)
{
	//static __int64 i = 0;
	//_STD cout << "Hey" <<i++<< NEW_LINE;
}

void RGB::Pixel::Show_Object() const
{
	//printf_s("%d" , this->R);
	_STD cout << "Red: [" << this->R << " ] " << "Green: [" << this->G << " ] " << "Blue: [" << this->B << " ] " << NEW_LINE;
}

void RGB::Pixel::Set_R(const unsigned char R)
{
	this->R = R;
}

void RGB::Pixel::Set_G(const unsigned char G)
{
	this->G = G;
}

void RGB::Pixel::Set_B(const unsigned char B)
{
	this->B = B;
}

constexpr char RGB::Pixel::Get_R() const
{
	return this->R;
}

constexpr char RGB::Pixel::Get_G() const
{
	return this->G;
}

constexpr char RGB::Pixel::Get_B() const
{
	return this->B;
}

RGB::Pixel& RGB::Pixel::operator=(const Pixel& Object)
{
	if (this != _STD addressof(Object))
	{
		this->R = Object.R;
		this->G = Object.G;
		this->B = Object.B;
	}
	return *this;
}

RGB::Pixel::~Pixel()
{
	this->R = NULL;
	this->B = NULL;
	this->B = NULL;
}
