//#define __cplusplus
//#define __CUDACC__
//#define __CUDACC_RTC__

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"

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

#define imin(a,b) (a<b?a:b)
#define sum_squares(x)  (x*(x+1)*(2*x+1)/6)

const int N = 33 * 1024;
const int threadsPerBlock = 256;
const int blocksPerGrid = imin(32, (N + threadsPerBlock - 1) / threadsPerBlock);


__global__ void dot(float* a, float* b, float* c) 
{
	__shared__ float cache[threadsPerBlock]{};
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	int cacheIndex = threadIdx.x;

	float temp{};
	while (tid < N) 
	{
		temp += a[tid] * b[tid];
		tid += blockDim.x * gridDim.x;
	}

	// Ustawienie wartoœci pamiêci podrêcznej
	cache[cacheIndex] = temp;

	// Synchronizacja w¹tków w tym bloku
	__syncthreads();

	// W przypadku redukcji threadsPerBlock musi byæ potêg¹ 2,
	// ze wzglêdu na poni¿szy kod
	int i = blockDim.x / 2;
	while (i != 0) 
	{
		if (cacheIndex < i)
		{
			cache[cacheIndex] += cache[cacheIndex + i];
		}
		__syncthreads();
		i /= 2;
	}

	if (cacheIndex == 0)
	{
		c[blockIdx.x] = cache[0];
	}		
}

int main(int argc, char* argv[])
{
	float* a{}, * b{}, c{}, * partial_c{};
	float* dev_a{}, * dev_b{}, * dev_partial_c{};

	// Alokacja pamiêci na CPU
	a = (float*)malloc(N * sizeof(float));
	b = (float*)malloc(N * sizeof(float));
	partial_c = (float*)malloc(blocksPerGrid * sizeof(float));

	// Alokacja pamiêci na GPU
	HANDLE_ERROR(cudaMalloc((void**)& dev_a, N * sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)& dev_b, N * sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)& dev_partial_c, blocksPerGrid * sizeof(float)));

	// Zape³nienie pamiêci hosta danymi
	for (int i = 0; i < N; i++) 
	{
		a[i] = i;
		b[i] = i * 2;
	}

	// Skopiowanie tablic a i b do GPU
	HANDLE_ERROR(cudaMemcpy(dev_a, a, N * sizeof(float), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, N * sizeof(float), cudaMemcpyHostToDevice));

	dot<<<blocksPerGrid, threadsPerBlock>>> (dev_a, dev_b,dev_partial_c);

	// Skopiowanie tablicy c z powrotem z GPU do CPU
	HANDLE_ERROR(cudaMemcpy(partial_c, dev_partial_c, blocksPerGrid * sizeof(float), cudaMemcpyDeviceToHost));

	// Zakoñczenie pracy na CPU
	c = 0;
	for (int i = 0; i < blocksPerGrid; i++) 
	{
		c += partial_c[i];
	}


	printf("Does GPU value %.6g = %.6g?\n", c, 2 * sum_squares((float)(N - 1)));

	// Zwolnienie pamiêci na GPU
	HANDLE_ERROR(cudaFree(dev_a));
	HANDLE_ERROR(cudaFree(dev_b));
	HANDLE_ERROR(cudaFree(dev_partial_c));

	// Zwolnienie pamiêci na CPU
	free(a);
	free(b);
	free(partial_c);

	system("pause");
	return 0;
}