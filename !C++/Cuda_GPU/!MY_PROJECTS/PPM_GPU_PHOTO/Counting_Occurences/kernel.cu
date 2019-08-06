
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#ifndef __CUDACC__
#define __CUDACC__
#endif
#include "device_functions.h"


#include "../..//..//common/book.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <random>
#include <chrono>

////////////////////////////////////////////////////
//GPU

#define HostToDevice cudaMemcpyHostToDevice
#define DeviceToHost cudaMemcpyDeviceToHost
#define OK cudaSuccess
#define NEW_LINE '\n'
#define N 100

#define BlocksPerGrid (N/10)
#define ThreadsPerBlock (N/10)

////////////////////////////////////////////////////////
/*
	RANDOM GENERATOR
*/

auto start = _STD chrono::system_clock::now();
_STD random_device random_engine;							
_STD mt19937 generator(random_engine());

////////////////////////////////////////////////////////


void Fill_Array(__int32* array, const size_t& size, const short int choice);
void Show_Array(__int32* array, const size_t& size);
void Show_Array_and_Occurences(const __int32* array_integer, const __int32* array_occurences, const size_t& size);

/*
	GPU FUNCTIONS
*/
__global__ void Count_Occurences(const __int32 * array_integer, __int32* array_occurences, const size_t& size);
////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	size_t array_size = N; //or self amount

	/*
		CPU ARRAYS
	*/
	__int32* integer_array{};
	__int32* integer_array_occurences{};
	integer_array = (__int32*)malloc(array_size * sizeof(__int32));
	integer_array_occurences = (__int32*)malloc(array_size * sizeof(__int32));
	////////////////////////////////////////////////////////

	/*
		GPU ARRAYS
	*/
	__int32* integer_array_GPU{};
	__int32* integer_array_GPU_occurences{};
	HANDLE_ERROR(cudaMalloc((void**)& integer_array_GPU, array_size * sizeof(__int32)));
	HANDLE_ERROR(cudaMalloc((void**)& integer_array_GPU_occurences, array_size * sizeof(__int32)));
	////////////////////////////////////////////////////////


	Fill_Array(integer_array, array_size, 3);
	//Show_Array(integer_array, array_size);


	HANDLE_ERROR(cudaMemcpy(integer_array_GPU, integer_array, array_size * sizeof(__int32), HostToDevice));

	//Counting the occurence of the numbers in these arrays
	Count_Occurences <<< BlocksPerGrid, ThreadsPerBlock >>> (integer_array_GPU, integer_array_GPU_occurences, array_size);


	HANDLE_ERROR(cudaMemcpy(integer_array_occurences, integer_array_GPU_occurences, array_size * sizeof(__int32), DeviceToHost));



	Show_Array_and_Occurences(integer_array, integer_array_occurences, array_size);

	/*
		Free the memory
	*/
	//ON CPU
	free(integer_array);
	free(integer_array_occurences);

	//ON GPU
	cudaFree(integer_array_GPU);
	cudaFree(integer_array_GPU_occurences);
	////////////////////////////////////////////////////////


	system("pause");
	return 0;
}


/*
	ARRAY FILLER
	1 -> For self assignment
	2 -> For random engine assignment
	3 -> For basic null values, currently it is a 0
*/
void Fill_Array(__int32* array, const size_t& size, const short int choice)
{
	if (choice == 1)
	{
		for (size_t i = 0; i < size; ++i)
		{
			array[i] = i;
		}
	}
	else if (choice == 2)
	{
		std::uniform_int_distribution<> dis(1, size);			//range of our randomly generator
		for (size_t i = 0; i < size; ++i)
		{
			array[i] = dis(generator);
		}
	}
	else if (choice == 3)
	{
		for (size_t i = 0; i < size; ++i)
		{
			array[i] = 0;
		}
	}
	else
	{
		_STD cerr << "ERROR:: [WRONG NUMBER OF CHOICE] " << NEW_LINE;
	}
}

void Show_Array(__int32* array, const size_t& size)
{
	for (size_t i = 0; i < size; ++i)
	{
		_STD cout << array[i] << ' ';
	}
	_STD cout << NEW_LINE;
}

void Show_Array_and_Occurences(const __int32* array_integer, const __int32* array_occurences, const size_t& size)
{
	for (size_t i = 0; i < size; ++i)
	{
		_STD cout << array_integer[i] << " -> " << array_occurences[i] << NEW_LINE;
	}
	_STD cout << NEW_LINE;
}


//GPU FUNCTIONS

__global__ void Count_Occurences(const __int32* array_integer, __int32* array_occurences, const size_t& size)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	size_t occurence{};
	__shared__ size_t cache_array_of_occurences[ThreadsPerBlock];//change it into array of occurented already
	int cache_index = threadIdx.x;

	while (id < N)
	{
		int id_j = id + 1;
		while (id_j < N)
		{
			if (array_integer[id] == array_integer[id_j])
			{
				++occurence;
			}
			id_j += 1;
		}
		id += blockDim.x * gridDim.x;
	}

	cache_array_of_occurences[cache_index] = occurence;

	//very important to put below this function __syncthreads cause
	//we have to know when all of the threads will end their work!!!
	__syncthreads();

	array_occurences[threadIdx.x + blockIdx.x * blockDim.x] = cache_array_of_occurences[cache_index];
	
	__syncthreads();
}