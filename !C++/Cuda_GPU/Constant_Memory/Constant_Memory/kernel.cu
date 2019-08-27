
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

#define rnd( x ) (x * rand() / RAND_MAX)
#define INF     2e10f

struct Sphere {
	float   r, b, g;
	float   radius;
	float   x, y, z;
	__device__ float hit(float ox, float oy, float* n) {
		float dx = ox - x;
		float dy = oy - y;
		if (dx * dx + dy * dy < radius * radius) {
			float dz = sqrtf(radius * radius - dx * dx - dy * dy);
			*n = dz / sqrtf(radius * radius);
			return dz + z;
		}
		return -INF;
	}
};
#define SPHERES 20

__constant__ Sphere s[SPHERES];

__global__ void kernel(unsigned char* ptr) {
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;
	float   ox = (x - DIM / 2);
	float   oy = (y - DIM / 2);

	float   r = 0, g = 0, b = 0;
	float   maxz = -INF;
	for (int i = 0; i < SPHERES; i++) {
		float   n;
		float   t = s[i].hit(ox, oy, &n);
		if (t > maxz) {
			float fscale = n;
			r = s[i].r * fscale;
			g = s[i].g * fscale;
			b = s[i].b * fscale;
			maxz = t;
		}
	}

	ptr[offset * 4 + 0] = (int)(r * 255);
	ptr[offset * 4 + 1] = (int)(g * 255);
	ptr[offset * 4 + 2] = (int)(b * 255);
	ptr[offset * 4 + 3] = 255;
}

// Dane globalne potrzebne procedurze aktualizuj¹cej
struct DataBlock {
	unsigned char* dev_bitmap;
};

int main(int argc, char* argv[])
{
	
	DataBlock   data;
	// Zarejestrowanie czasu pocz¹tkowego
	cudaEvent_t     start, stop;
	HANDLE_ERROR(cudaEventCreate(&start));
	HANDLE_ERROR(cudaEventCreate(&stop));
	HANDLE_ERROR(cudaEventRecord(start, 0));

	CPUBitmap bitmap(DIM, DIM, &data);
	unsigned char* dev_bitmap;

	// Alokowanie pamiêci na GPU dla mapy bitowej
	HANDLE_ERROR(cudaMalloc((void**)& dev_bitmap,
		bitmap.image_size()));

	// Alokowanie tymczasowej pamiêci, zainicjowanie jej, skopiowanie jej do
	// pamiêci sta³ej na GPU, a nastêpnie zwolnienie
	Sphere* temp_s = (Sphere*)malloc(sizeof(Sphere) * SPHERES);
	for (int i = 0; i < SPHERES; i++) {
		temp_s[i].r = rnd(1.0f);
		temp_s[i].g = rnd(1.0f);
		temp_s[i].b = rnd(1.0f);
		temp_s[i].x = rnd(1000.0f) - 500;
		temp_s[i].y = rnd(1000.0f) - 500;
		temp_s[i].z = rnd(1000.0f) - 500;
		temp_s[i].radius = rnd(100.0f) + 20;
	}
	HANDLE_ERROR(cudaMemcpyToSymbol(s, temp_s, sizeof(Sphere) * SPHERES));
	free(temp_s);

	// Wygenerowanie mapy bitowej z danych kul
	dim3    grids(DIM / 16, DIM / 16);
	dim3    threads(16, 16);
	kernel << <grids, threads >> > (dev_bitmap);

	// Skopiowanie mapy bitowej z powrotem z GPU w celu wyœwietlenia
	HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(), dev_bitmap,
		bitmap.image_size(),
		cudaMemcpyDeviceToHost));

	// Zarejestrowanie czasu zakoñczenia i wyœwietlenie wyniku pomiaru czasu
	HANDLE_ERROR(cudaEventRecord(stop, 0));
	HANDLE_ERROR(cudaEventSynchronize(stop));
	float   elapsedTime;
	HANDLE_ERROR(cudaEventElapsedTime(&elapsedTime,
		start, stop));
	printf("Czas generowania:  %3.1f ms\n", elapsedTime);

	HANDLE_ERROR(cudaEventDestroy(start));
	HANDLE_ERROR(cudaEventDestroy(stop));

	HANDLE_ERROR(cudaFree(dev_bitmap));

	// Wyœwietlenie
	bitmap.display_and_exit();
	system("pause");
	return 0;
}