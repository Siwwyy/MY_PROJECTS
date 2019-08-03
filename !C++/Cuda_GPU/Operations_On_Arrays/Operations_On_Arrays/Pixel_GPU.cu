#include "..//../Operations_On_Arrays/Operations_On_Arrays/Pixel.cuh"



//RGB_GPU::Pixel_GPU::Pixel_GPU() :
//	R(NULL),
//	G(NULL),
//	B(NULL)
//{
//
//}
//
//RGB_GPU::Pixel_GPU::Pixel_GPU(const unsigned char R, const unsigned char G, const unsigned char B) :
//	R(R),
//	G(G),
//	B(B)
//{
//	//
//}
//
//RGB_GPU::Pixel_GPU::Pixel_GPU(const Pixel_GPU& Object) :
//	R(Object.R),
//	G(Object.G),
//	B(Object.B)
//{
//	//static __int64 i = 0;
//	//_STD cout << "Hey" <<i++<< NEW_LINE;
//}
//
//void RGB_GPU::Pixel_GPU::Show_Object() const
//{
//	//printf_s("%d" , this->R);
//	//_STD cout << "Red: [" << this->R << " ] " << "Green: [" << this->G << " ] " << "Blue: [" << this->B << " ] " << NEW_LINE;
//}
//
//__device__ void RGB_GPU::Pixel_GPU::Set_R(const unsigned char R)
//{
//	this->R = R;
//}
//
//__device__ void RGB_GPU::Pixel_GPU::Set_G(const unsigned char G)
//{
//	this->G = G;
//}
//
//__device__ void RGB_GPU::Pixel_GPU::Set_B(const unsigned char B)
//{
//	this->B = B;
//}
//
//__device__ constexpr char RGB_GPU::Pixel_GPU::Get_R() const
//{
//	return this->R;
//}
//
//__device__ constexpr char RGB_GPU::Pixel_GPU::Get_G() const
//{
//	return this->G;
//}
//
//__device__ constexpr char RGB_GPU::Pixel_GPU::Get_B() const
//{
//	return this->B;
//}
//
//__device__ Pixel_GPU& RGB_GPU::Pixel_GPU::operator=(const Pixel_GPU& Object)
//{
//	if (this != _STD addressof(Object))
//	{
//		this->R = Object.R;
//		this->G = Object.G;
//		this->B = Object.B;
//	}
//	return *this;
//}
//
//RGB_GPU::Pixel_GPU::~Pixel_GPU()
//{
//	this->R = NULL;
//	this->B = NULL;
//	this->B = NULL;
//}