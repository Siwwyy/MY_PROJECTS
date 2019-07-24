
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "..//..//common/book.h"

#include <stdio.h>
#include <windows.h>
#include <iostream>

constexpr size_t array_size = 10;
#define N array_size
///*
//	ON CPU
//*/
//
//void addition(__int32 * array_1, __int32 * array_2, __int32 * array_3);
//
//int main(int argc, char * argv[])
//{
//	__int32 array_1[array_size]{}, array_2[array_size]{}, array_3[array_size]{};
//		
//	for (size_t i = 0; i < array_size; ++i)
//	{
//		array_1[i] = i;
//		array_2[i] = i+i;
//	}
//
//	addition(array_1, array_2, array_3);
//	//Dispalying the results of adding 
//	for (size_t i = 0; i < array_size; ++i)
//	{
//		printf_s("%d + %d = %d\n", array_1[i], array_2[i], array_3[i]);
//	}
//
//	system("pause");
//	return 0;
//}
//
//void addition(__int32* array_1, __int32* array_2, __int32* array_3)
//{
//	/*for (size_t i = 0; i < array_size; ++i)
//	{
//		array_3[i] = (array_1[i] + array_2[i]);
//	}*/
//	size_t id{};
//	while(id < array_size)
//	{
//		array_3[id] = (array_1[id] + array_2[id]);
//		++id;
//	}
//}

__global__ void addition(__int32* array_1, __int32* array_2, __int32* array_3);

int main(int argc, char * argv[])
{
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
	HANDLE_ERROR(cudaMemcpy(dev_a, a, N * sizeof(int), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, N * sizeof(int), cudaMemcpyHostToDevice));
	addition<<<N, 1>>>(dev_a, dev_b, dev_c);
	// Kopiowanie tablicy c z GPU do CPU
	HANDLE_ERROR(cudaMemcpy(c, dev_c, N * sizeof(int), cudaMemcpyDeviceToHost));
	// Wyświetlenie wyniku
	for (int i = 0; i < N; i++)
	{
		printf_s("%d + %d = %d\n", a[i], b[i], c[i]);
	}
	// Zwolnienie pamięci alokowanej na GPU
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	system("pause");
	return 0;
}

__global__ void addition(__int32* array_1, __int32* array_2, __int32* array_3)
{
	int id = blockIdx.x; // Działanie na danych znajdujących się pod tym indeksem
	if (id < N)
	{
		//add *100000 or more to get an error execution
		array_3[id] = (array_1[id] + array_2[id]);
		//array_3[id] = (array_1[id*10000000] + array_2[id]);
	}	
	//return __global__ void();
	/*
		It means that when we are invoking this function (less than N - 1 off course,
		cause our array size is N) we have to call blocks of GPU's contained in GRID.
		id = blockIdx.x is just a number of block currently (in easy way, index) we 
		working on
	*/
}
