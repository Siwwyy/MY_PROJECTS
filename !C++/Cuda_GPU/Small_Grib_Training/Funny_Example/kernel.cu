
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"
#include "..//..//common/cpu_bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

/*
	ON GPU
*/
//This program wil get results of vary counts on complex numbers

//Zn+1= Zn^2+C

//#define DIM 20

using namespace std;

////////////////////////////////////////////////////
//CPU

//struct cuComplex 
//{
//	float r;
//	float i;
//	cuComplex(float a, float b) : r(a), i(b) {}
//	~cuComplex() { r = 0.0; i = 0.0f; }
//
//	float magnitude2(void)
//	{
//		return r * r + i * i;
//	}
//
//	cuComplex operator*(const cuComplex& a)
//	{
//		return cuComplex(r * a.r - i * a.i, i * a.r + r * a.i);
//	}
//
//	cuComplex operator+(const cuComplex& a)
//	{
//		return cuComplex(r + a.r, i + a.i);
//	}
//
//};
//

//void kernel(unsigned char* ptr);
//int julia(int x, int y);
//
//int main(int argc, char* argv[])
//{
//	CPUBitmap bitmap(DIM, DIM);
//	unsigned char* ptr = bitmap.get_ptr();
//
//	kernel(ptr);
//		
//	system("pause");
//	return 0;
//}
//
//void kernel(unsigned char * ptr)
//{
//	for (int y = 0; y < DIM; y++)
//	{
//		for (int x = 0; x < DIM; x++)
//		{
//			int offset = x + y * DIM;
//			int juliaValue = julia(x, y);
//			ptr[offset * 4 + 0] = 255 * juliaValue;
//			ptr[offset * 4 + 1] = 0;
//			ptr[offset * 4 + 2] = 0;
//			ptr[offset * 4 + 3] = 255;
//		}
//	}
//}
//
//int julia(int x, int y)
//{
//	const float scale = 1.5;
//	float jx = scale * (float)(DIM / 2 - x) / (DIM / 2);
//	float jy = scale * (float)(DIM / 2 - y) / (DIM / 2);
//	cuComplex c(-0.8, 0.156);
//	cuComplex a(jx, jy);
//	int i = 0;
//	for (i = 0; i < 200; i++)
//	{
//		a = a * a + c;
//		if (a.magnitude2() > 1000)
//		{
//			return 0;
//		}
//	}
//	return 1;
//}

////////////////////////////////////////////////////
//GPU

#define DIM 1000

struct cuComplex
{
	float r;
	float i;
	__device__ cuComplex(float a, float b) : r(a), i(b) {}
	__device__ ~cuComplex() { r = 0.0; i = 0.0f; }

	__device__ float magnitude2(void)
	{
		return r * r + i * i;
	}

	__device__ cuComplex operator*(const cuComplex& a)
	{
		return cuComplex(r * a.r - i * a.i, i * a.r + r * a.i);
	}

	__device__ cuComplex operator+(const cuComplex& a)
	{
		return cuComplex(r + a.r, i + a.i);
	}
};
	

__global__ void kernel(unsigned char * ptr);
__device__ int julia(int x, int y);

int main(int argc, char* argv[])
{
	CPUBitmap bitmap(DIM, DIM);
	unsigned char* dev_bitmap{};

	HANDLE_ERROR(cudaMalloc((void**)& dev_bitmap,bitmap.image_size()));
	dim3 grid(DIM, DIM);


	kernel<<<grid, 1>>>(dev_bitmap);

	HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(),dev_bitmap,bitmap.image_size(),cudaMemcpyDeviceToHost));

	bitmap.display_and_exit();
	HANDLE_ERROR(cudaFree(dev_bitmap));

	system("pause");
	return 0;
}

__global__ void kernel(unsigned char* ptr)
{
	// Odwzorowanie z blockldx na współrzędne piksela
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x + y * gridDim.x;
	// Obliczenie wartości dla tego punktu
	int juliaValue = julia(x, y);
	ptr[offset * 4 + 0] = 255 * juliaValue;
	ptr[offset * 4 + 1] = 0;
	ptr[offset * 4 + 2] = 0;
	ptr[offset * 4 + 3] = 255;
}

__device__ int julia(int x, int y)
{
	const float scale = 1.5;
	float jx = scale * (float)(DIM / 2 - x) / (DIM / 2);
	float jy = scale * (float)(DIM / 2 - y) / (DIM / 2);
	cuComplex c(-0.8, 0.156);
	cuComplex a(jx, jy);
	int i = 0;
	for (i = 0; i < 200; i++)
	{
		a = a * a + c;
		if (a.magnitude2() > 1000)
		{
			return 0;
		}
	}
	return 1;
}
