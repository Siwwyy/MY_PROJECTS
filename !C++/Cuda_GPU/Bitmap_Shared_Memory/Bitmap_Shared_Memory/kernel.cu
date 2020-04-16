
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#ifndef __CUDACC__
#define __CUDACC__
#endif
#include "cuda_runtime_api.h"


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

//
//__global__ void kernel(unsigned char* ptr) 
//{
//	// Rzutowanie threadIdx/BlockIdx na pozycje pikseli
//	int x = threadIdx.x + blockIdx.x * blockDim.x;
//	int y = threadIdx.y + blockIdx.y * blockDim.y;
//	int offset = x + y * blockDim.x * gridDim.x;
//
//	__shared__ float shared[16][16];
//
//	// Obliczenie wartoœci dla tej pozycji
//	const float period = 128.0f;
//
//	shared[threadIdx.x][threadIdx.y] = 255 * (sinf(x * 2.0f * PI / period) + 1.0f) * (sinf(y * 2.0f * PI / period) + 1.0f) / 4.0f;
//
//	// Usuniêcie tego wywo³ania funkcji syncthreads bêdzie widoczne
//	// w wyniku. Dlatego jest ona potrzebna.
//	__syncthreads();
//
//	ptr[offset * 4 + 0] = 0;
//	ptr[offset * 4 + 1] = shared[15 - threadIdx.x][15 - threadIdx.y];
//	ptr[offset * 4 + 2] = 0;
//	ptr[offset * 4 + 3] = 255;
//}
//
//// Dane globalne potrzebne procedurze aktualizuj¹cej
//struct DataBlock 
//{
//	unsigned char* dev_bitmap;
//};
//
//int main(int argc, char* argv[])
//{
//	DataBlock   data;
//	CPUBitmap bitmap(DIM, DIM, &data);
//	unsigned char* dev_bitmap;
//
//	HANDLE_ERROR(cudaMalloc((void**)& dev_bitmap, bitmap.image_size())); 
//	data.dev_bitmap = dev_bitmap;
//
//	dim3 grids(DIM / 16, DIM / 16);
//	dim3 threads(16, 16);
//	kernel <<<grids, threads >>> (dev_bitmap);
//
//	HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(), dev_bitmap, bitmap.image_size(), cudaMemcpyDeviceToHost));
//
//	HANDLE_ERROR(cudaFree(dev_bitmap));
//
//	bitmap.display_and_exit();
//
//	system("pause");
//	return 0;
//}


#define DIM 1000

struct cuComplex {
    float   r;
    float   i;
    // cuComplex( float a, float b ) : r(a), i(b)  {}
    __device__ cuComplex(float a, float b) : r(a), i(b) {} // Fix error for calling host function from device
    __device__ float magnitude2(void) {
        return r * r + i * i;
    }
    __device__ cuComplex operator*(const cuComplex& a) {
        return cuComplex(r * a.r - i * a.i, i * a.r + r * a.i);
    }
    __device__ cuComplex operator+(const cuComplex& a) {
        return cuComplex(r + a.r, i + a.i);
    }
};

__device__ int julia(int x, int y) {
    const float scale = 1.5;
    float jx = scale * (float)(DIM / 2 - x) / (DIM / 2);
    float jy = scale * (float)(DIM / 2 - y) / (DIM / 2);

    cuComplex c(-0.8, 0.156);
    cuComplex a(jx, jy);

    int i = 0;
    for (i = 0; i < 200; i++) {
        a = a * a + c;
        if (a.magnitude2() > 1000)
            return 0;
    }

    return 1;
}

__global__ void kernel(unsigned char* ptr) {
    // map from blockIdx to pixel position
    int x = blockIdx.x;
    int y = blockIdx.y;
    int offset = x + y * gridDim.x;

    // now calculate the value at that position
    int juliaValue = julia(x, y);
    ptr[offset * 4 + 0] = 255 * juliaValue;
    ptr[offset * 4 + 1] = 0;
    ptr[offset * 4 + 2] = 0;
    ptr[offset * 4 + 3] = 255;
}

// globals needed by the update routine
struct DataBlock {
    unsigned char* dev_bitmap;
};

int main(void) {
    DataBlock   data;
    CPUBitmap bitmap(DIM, DIM, &data);
    unsigned char* dev_bitmap;

    HANDLE_ERROR(cudaMalloc((void**)&dev_bitmap, bitmap.image_size()));
    data.dev_bitmap = dev_bitmap;

    dim3    grid(DIM, DIM);
    kernel << <grid, 1 >> > (dev_bitmap);

    HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(), dev_bitmap,
        bitmap.image_size(),
        cudaMemcpyDeviceToHost));

    HANDLE_ERROR(cudaFree(dev_bitmap));

    bitmap.display_and_exit();
}
