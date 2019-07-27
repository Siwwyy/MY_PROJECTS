
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
//#define N 10
#define N (33 * 1024)

__global__ void addition(__int32* array_1, __int32* array_2, __int32* array_3);

int main(int argc, char* argv[])
{
	/*_STD cout << argc << NEW_LINE;
	_STD cout << *argv << NEW_LINE;*/
	int a[N]{}, b[N]{}, c[N]{};
	int* dev_a{}, * dev_b{}, * dev_c{};
	// Alokacja pamięci na GPU
	HANDLE_ERROR(cudaMalloc((void**)& dev_a, N * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)& dev_b, N * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)& dev_c, N * sizeof(int)));
	//Zapełnienie tablic a i b na CPU
	for (int i = 0; i < N; i++)
	{
		a[i] = i;
		b[i] = i + i;
	}
	//Kopiowanie tablic a i b do GPU
	//_STD cout << ((N + (N - 1)) / 2) << NEW_LINE;
	HANDLE_ERROR(cudaMemcpy(dev_a, a, N * sizeof(int), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, N * sizeof(int), cudaMemcpyHostToDevice));
	//addition <<<((N + (N-1))/2),N>>> (dev_a, dev_b, dev_c);
	addition <<<128,128>>> (dev_a, dev_b, dev_c);
	// Kopiowanie tablicy c z GPU do CPU
	HANDLE_ERROR(cudaMemcpy(c, dev_c, N * sizeof(int), cudaMemcpyDeviceToHost));
	// Wyświetlenie wyniku
	for (int i = 0; i < N; i++)
	{
		printf_s("%d + %d = %d\n", a[i], b[i], c[i]);
	}
	// Zwolnienie pamięci alokowanej na GPU
	//std::cout << cudaDevAttrMaxThreadsPerBlock << NEW_LINE;
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	////Some informations about GPU capacity (max threads etc.)
	//_STD cout << NEW_LINE;
	//dim3 gridDim{N,N};
	//dim3 blockDim{N,N};
	//printf("Grid : {%d, %d, %d} blocks. Blocks : {%d, %d, %d} threads.\n",gridDim.x, gridDim.y, gridDim.z, blockDim.x, blockDim.y, blockDim.z);
	//cudaDeviceProp prop{};
	//int count{};
	//HANDLE_ERROR(cudaGetDeviceCount(&count));	//amount of Device properties
	//for (int i = 0; i < count; i++)
	//{
	//	HANDLE_ERROR(cudaGetDeviceProperties(&prop, i));
	//	printf("Amount of global memory: %ld\n", prop.totalGlobalMem);
	//	printf("Amount of constant memory: %ld\n", prop.totalConstMem);
	//	printf("Max. memory height: %ld\n", prop.memPitch);
	//	printf("Max. amount of threads per block %d\n", prop.maxThreadsPerBlock);
	//	printf("Max. amount of threads dimensionals: (%d, %d, %d)\n",prop.maxThreadsDim[0], prop.maxThreadsDim[i],prop.maxThreadsDim[2]);
	//	printf("Max. amount of grid dimensionals: (%d, %d, %d)\n",prop.maxGridSize[0], prop.maxGridSize[i], prop.maxGridSize[2]);
	//	printf("\n");
	//}

	system("pause");
	return 0;
}

//__global__ void addition(__int32* array_1, __int32* array_2, __int32* array_3)
//{
//	int id = threadIdx.x;
//	if (id < N)
//	{
//		//add *100000 or more to get an error execution
//		array_3[id] = (array_1[id] + array_2[id]);
//	}
//	/*
//		It means that when we are invoking this function (less than N - 1 off course,
//		cause our array size is N) we have to call blocks of GPU's contained in GRID.
//		int id = threadIdx.x is just a number of thread in currently currently 
//		(in easy way, index) weworking on
//	*/
//}

__global__ void addition(__int32* array_1, __int32* array_2, __int32* array_3)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	while(id < N) 
	{
		array_3[id] = array_1[id] + array_2[id];
		id += blockDim.x * gridDim.x;
		//id = threadIdx.x + blockIdx.x * blockDim.x;
	}
	/*
		It means that when we are invoking this function (less than N - 1 off course,
		cause our array size is N) we have to call blocks of GPU's contained in GRID.
		int id = threadIdx.x is just a number of thread in currently currently
		(in easy way, index) weworking on
	*/
}

