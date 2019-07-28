
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"
#include "..//..//common/cpu_anim.h"

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
#define DIM 1920

struct DataBlock
{
	unsigned char* dev_bitmap;
	CPUAnimBitmap* bitmap;

};

// Zwolnienie pamięci alokowanej na GPU
void cleanup(DataBlock* d) 
{
	cudaFree(d->dev_bitmap);
}


__global__ void kernel(unsigned char* ptr, int ticks)
{
	// Odwzorowanie z threadldx/Blockldx na położenie pikseli
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;
	// Obliczenie wartości dla danego miejsca
	float fx = x - DIM / 2;
	float fy = y - DIM / 2;
	float d = sqrtf(fx * fx + fy * fy);
	unsigned char grey = (unsigned char)(128.0f + 127.0f * cos(d / 10.0f - ticks / 7.0f) / (d / 10.0f + 1.0f));
	ptr[offset * 4 + 0] = grey;
	ptr[offset * 4 + 1] = grey;
	ptr[offset * 4 + 2] = grey;
	ptr[offset * 4 + 3] = 255;
}


void generate_frame(DataBlock* d, int ticks) {
	dim3 blocks(DIM / 16, DIM / 16);
	dim3 threads(16, 16);
	kernel<<<blocks, threads>>>(d->dev_bitmap, ticks);
	HANDLE_ERROR(cudaMemcpy(d->bitmap->get_ptr(),d->dev_bitmap,d->bitmap->image_size(),cudaMemcpyDeviceToHost));
}


int main(int argc, char* argv[])
{
	DataBlock data;
	CPUAnimBitmap bitmap(DIM, DIM, &data);
	data.bitmap = &bitmap;
	HANDLE_ERROR(cudaMalloc((void**)& data.dev_bitmap, bitmap.image_size()));
	bitmap.anim_and_exit((void (*)(void*, int))generate_frame,(void (*)(void*))cleanup);

	system("pause");
	return 0;
}