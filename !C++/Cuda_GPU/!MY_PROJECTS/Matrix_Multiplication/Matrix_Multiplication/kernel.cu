
#include "device_launch_parameters.h"
#ifndef __CUDACC__
#define __CUDACC__
#endif

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"

#include "..//..//..//common/book.h"

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

#define SIZE 10

//int a{3};

void Fill_Matrix_CPU(__int32 ** Matrix);
void Fill_Matrix_CPU(__int32 Matrix[][SIZE]);
void Show_Matrix_CPU(__int32 ** Matrix);
void Show_Matrix_CPU(__int32 Matrix[][SIZE]);

__global__ void Multiply_Matrix(__int32* Matrix);

int main(int argc, char* argv[])
{
	//int a{4};

	//_STD cout << ::a << NEW_LINE;

	/*
		ALLOCATING NEEDED MEMORY ON CPU (exactly in RAM)
	*/
	__int32** Matrix_CPU;
	//__int32 Matrix_CPU[SIZE][SIZE]{};
	Matrix_CPU = (__int32**)malloc(SIZE * sizeof(__int32*));

	for (size_t i = 0; i < SIZE; ++i)
	{
		*(Matrix_CPU + i) = (__int32*)malloc(SIZE * sizeof(__int32));
		//Matrix_CPU[i] = (__int32*)malloc(SIZE * sizeof(__int32));
	}
	////////////////////////////////////////////////////

	//FILL MATRIX WITH RANDOM VALUES
	Fill_Matrix_CPU(Matrix_CPU);

	//_STD cout << Matrix_CPU[0] << NEW_LINE;
	//_STD cout << Matrix_CPU[1] << NEW_LINE;
	//_STD cin.get();
	//SHOW FILLED UP ARRAY
	Show_Matrix_CPU(Matrix_CPU);

//	_STD cout << sizeof(__int32) << ' ' << /*sizeof(char*) or sizeof(__int32*)  <<*/ NEW_LINE;


	/*
		ALLOCATING NEEDED MEMORY ON GPU
	*/
	__int32* Matrix_GPU;
	HANDLE_ERROR(cudaMalloc((void**)&Matrix_GPU, (SIZE * SIZE) *  sizeof(__int32)));	//GPU interprets 2D array as a flat array !

	////////////////////////////////////////////////////


	//COPY CPU ARRAY TO GPU
	//HANDLE_ERROR(cudaMemcpy(Matrix_GPU, Matrix_CPU, (SIZE * SIZE) * sizeof(__int32), HostToDevice));	//only for statics array from HOST's!

	for (size_t i = 0; i < SIZE; ++i)
	{
		cudaMemcpy(Matrix_GPU + i * SIZE, *(Matrix_CPU + i), sizeof(__int32) * SIZE, HostToDevice);
	}

	////////////////////////////////////////////////////

	Multiply_Matrix<<<SIZE,SIZE>>>(Matrix_GPU);


	//COPY FROM GPU TO CPU
	//HANDLE_ERROR(cudaMemcpy(Matrix_CPU, Matrix_GPU, (SIZE * SIZE) * sizeof(__int32), DeviceToHost));	//only for statics array

	for (size_t i = 0; i < SIZE; ++i)
	{
		cudaMemcpy(*(Matrix_CPU + i), Matrix_GPU + i * SIZE, sizeof(__int32) * SIZE, DeviceToHost);	//for dynamic allocation
	}
	////////////////////////////////////////////////////


	//SHOW RESULTS
	Show_Matrix_CPU(Matrix_CPU);

	/*
		FREEING PREVIOUSLY ALOCATED MEMORY
	*/
	//ON CPU
	for (size_t i = 0; i < SIZE; ++i)
	{
		free(*(Matrix_CPU + i));
	}
	free(Matrix_CPU);

	////ON GPU
	/*for (size_t i = 0; i < SIZE; ++i)
	{
		HANDLE_ERROR(cudaFree(*(Matrix_CPU + i)));
	}*/
	HANDLE_ERROR(cudaFree(Matrix_GPU));
	////////////////////////////////////////////////////


	system("pause");
	return 0;
}

void Fill_Matrix_CPU(__int32** Matrix)
{
	__int32 value = 0;
	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			*(*(Matrix + i) + j) = value++;
			//Matrix[i][j] = NULL;
		}
	}
}

void Fill_Matrix_CPU(__int32 Matrix[][SIZE])
{
	__int32 value = 0;
	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			//*(*(Matrix + i) + j) = value++;
			Matrix[i][j] = 1;
		}
	}
}

void Show_Matrix_CPU(__int32** Matrix)
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		_STD cout << '|' << ' ';
		for (size_t j = 0; j < SIZE; ++j)
		{
			_STD cout << *(*(Matrix + i) + j) << ' ';
		}
		_STD cout << '|' << NEW_LINE;
	}
	_STD cout << NEW_LINE;
}

void Show_Matrix_CPU(__int32 Matrix[][SIZE])
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		_STD cout << '|' << ' ';
		for (size_t j = 0; j < SIZE; ++j)
		{
			_STD cout << *(*(Matrix + i) + j) << ' ';
		}
		_STD cout << '|' << NEW_LINE;
	}
	_STD cout << NEW_LINE;
}

__global__ void Multiply_Matrix(__int32* Matrix)
{
	int id_x = threadIdx.x + blockIdx.x * blockDim.x;
	int id_y = threadIdx.y + blockIdx.y * blockDim.y;

	while (id_x < SIZE)
	{
		while (id_y < SIZE)
		{
			//printf("A[%d][%d]\n", id_y, id_x);
			//printf("A[%d][%d]\n", id_y * SIZE + id_x);
			//Matrix[id_y+ id_x] *= 2;
			Matrix[id_y * SIZE + id_x] *= 2;
			id_y += blockDim.y * gridDim.y;
			//printf("\n");
		}
		id_x += blockDim.x * gridDim.x;
	}
}