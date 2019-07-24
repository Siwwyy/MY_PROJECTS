
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"
#include "..//..//common/cpu_bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////
//GPU

#define DIM 100
#define OBJECT_SIZE (DIM/2)

class _Point
{
private:
	/*
		ZMIENNE PRIVATE
	*/
	float x;
	float y;
	//////////////////////////////////////////////////////////////////////////////
public:
	/*
		KONSTRUKTORY PUBLIC
	*/
	_Point() = delete;
	__device__ _Point(const float x, const float y);
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	__device__ void Set_X(const float* new_X);
	__device__ void Set_Y(const float* new_Y);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/
	__device__ constexpr float Get_X() const;
	__device__ constexpr float Get_Y() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY PUBLIC
	*/
	//JEDNOARGUMENTOWE
	__device__ _Point& operator+(const _Point& Object);
	__device__ _Point& operator-(const _Point& Object);
	__device__ _Point& operator*(const _Point& Object);
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	__device__ ~_Point();		//wirtualny destruktor
	//////////////////////////////////////////////////////////////////////////////
};

__global__ void Kernel(unsigned char* ptr);
__device__ int Create_Square(int x, int y);

int main(int argc, char* argv[])
{
	CPUBitmap bitmap(DIM, DIM);
	unsigned char* dev_bitmap{};

	HANDLE_ERROR(cudaMalloc((void**)& dev_bitmap, bitmap.image_size()));
	dim3 grid(DIM, DIM);

	Kernel<<<grid, 1 >>>(dev_bitmap);

	HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(), dev_bitmap, bitmap.image_size(), cudaMemcpyDeviceToHost));

	bitmap.display_and_exit();
	HANDLE_ERROR(cudaFree(dev_bitmap));

	system("pause");
	return 0;
}

// CLASS POINT CASE

__device__ _Point::_Point(const float x, const float y):
	x(x),
	y(y)
{

}

__device__ void _Point::Set_X(const float* new_X)
{
	this->x = (*new_X);
}

__device__ void _Point::Set_Y(const float* new_Y)
{
	this->y = (*new_Y);
}

__device__ constexpr float _Point::Get_X() const
{
	return this->x;
}

__device__ constexpr float _Point::Get_Y() const
{
	return this->y;
}

__device__ _Point& _Point::operator+(const _Point& Object)
{
	this->x += Object.x;
	this->y += Object.y;
	return *this;
}

__device__ _Point& _Point::operator-(const _Point& Object)
{
	this->x -= Object.x;
	this->y -= Object.y;
	return *this;
}

__device__ _Point& _Point::operator*(const _Point& Object)
{
	this->x *= Object.x;
	this->y *= Object.y;
	return *this;
}

_Point::~_Point()
{
	this->x = 0;
	this->y = 0;
}

////////////////////////////////////////////////////

__global__ void Kernel(unsigned char* ptr)
{
	// Odwzorowanie z blockldx na współrzędne piksela
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x + y * gridDim.x;
	// Obliczenie wartości dla tego punktu
	int my_value = Create_Square(x, y);
	ptr[offset * 4 + 0] = 255 * my_value;
	ptr[offset * 4 + 1] = 0;
	ptr[offset * 4 + 2] = 0;
	ptr[offset * 4 + 3] = 255;
}

__device__ int Create_Square(int x, int y)
{
	const float scale = 1.5;
	float jx = scale * (float)(DIM / 2 - x) / (DIM / 2);
	float jy = scale * (float)(DIM / 2 - y) / (DIM / 2);

	_Point Object(jx, jy);

	for (size_t i = 0; i < 200; i++)
	{
		if (Object.Get_X() > OBJECT_SIZE)
		{
			return 0;
		}
	}
	return 1;
}