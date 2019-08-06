
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#ifndef __CUDACC__
#define __CUDACC__
#endif
#include "device_functions.h"


#include "..//..//common/book.h"
#include "..//..//common/cpu_bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>



////////////////////////////////////////////////////
//GPU

#define HostToDevice cudaMemcpyHostToDevice
#define DeviceToHost cudaMemcpyDeviceToHost
#define OK cudaSuccess
#define NEW_LINE '\n'

#define DIM 1024
#define PI 3.1415926535897932f


__global__ void kernel(unsigned char* ptr) 
{
	// Rzutowanie threadIdx/BlockIdx na pozycje pikseli
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;

	__shared__ float shared[16][16];

	// Obliczenie wartości dla tej pozycji
	const float period = 128.0f;

	shared[threadIdx.x][threadIdx.y] = 255 * (sinf(x * 2.0f * PI / period) + 1.0f) * (sinf(y * 2.0f * PI / period) + 1.0f) / 4.0f;

	// Usunięcie tego wywołania funkcji syncthreads będzie widoczne
	// w wyniku. Dlatego jest ona potrzebna.
	__syncthreads();

	ptr[offset * 4 + 0] = 0;
	ptr[offset * 4 + 1] = shared[15 - threadIdx.x][15 - threadIdx.y];
	ptr[offset * 4 + 2] = 0;
	ptr[offset * 4 + 3] = 255;
}

// Dane globalne potrzebne procedurze aktualizującej
struct DataBlock 
{
	unsigned char* dev_bitmap;
};

int main(int argc, char* argv[])
{
	DataBlock   data;
	CPUBitmap bitmap(DIM, DIM, &data);
	unsigned char* dev_bitmap;

	HANDLE_ERROR(cudaMalloc((void**)& dev_bitmap, bitmap.image_size())); 
	data.dev_bitmap = dev_bitmap;

	dim3 grids(DIM / 16, DIM / 16);
	dim3 threads(16, 16);
	kernel <<<grids, threads >>> (dev_bitmap);

	HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(), dev_bitmap, bitmap.image_size(), cudaMemcpyDeviceToHost));

	HANDLE_ERROR(cudaFree(dev_bitmap));

	bitmap.display_and_exit();

	system("pause");
	return 0;
}