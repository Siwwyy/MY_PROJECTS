
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>


////////////////////////////////////////////////////
//GPU

#define HostToDevice cudaMemcpyHostToDevice
#define DeviceToHost cudaMemcpyDeviceToHost
#define OK cudaSuccess
#define NEW_LINE '\n'
#define N 10	//size of array

__global__ void Multiply(__int64* array_1, __int64* array_2, __int64* array_3);

int main(int argc, char* argv[])
{
	//__int64 * a_CPU{}, * b_CPU{}, * c_CPU{};
	__int64 a_CPU[N][N], b_CPU[N][N], c_CPU[N][N];
	__int64 * a_GPU{}, * b_GPU{}, * c_GPU{};

	/*a_CPU = (__int64*)malloc(N * sizeof(__int64));
	b_CPU = (__int64*)malloc(N * sizeof(__int64));
	c_CPU = (__int64*)malloc(N * sizeof(__int64));*/

	cudaMalloc((void**)& a_GPU, N*N * sizeof(__int64));
	cudaMalloc((void**)& b_GPU, N * N * sizeof(__int64));
	cudaMalloc((void**)& c_GPU, N * N * sizeof(__int64));

	//for (size_t i = 0; i < N; ++i)
	//{
	//	*(a_CPU + i) = static_cast<__int64>(i);
	//	*(b_CPU + i) = static_cast<__int64>(i * i);
	///*	a_CPU[i] = static_cast<__int64>(i);
	//	b_CPU[i] = static_cast<__int64>(i*i);*/
	//	*(c_CPU + i) = 0;
	//}

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			a_CPU[i][j] = static_cast<__int64>(j+i);
			b_CPU[i][j] = static_cast<__int64>(i*j);
			*(*(c_CPU + i) + j) = 0;

		}
	}

	cudaMemcpy(a_GPU, a_CPU, N * N * sizeof(__int64), HostToDevice);
	cudaMemcpy(b_GPU, b_CPU, N * N * sizeof(__int64), HostToDevice);

	Multiply <<<N, N>>> (a_GPU, b_GPU, c_GPU);

	cudaMemcpy(c_CPU, c_GPU, N * N * sizeof(__int64), DeviceToHost);

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			_STD cout << *(*(c_CPU+i) + j) << ' ';
		}
		_STD cout << NEW_LINE;
	}

	//free(a_CPU);
	//free(b_CPU);
	//free(c_CPU);

	cudaFree(a_GPU);
	cudaFree(b_GPU);
	cudaFree(c_GPU);

	system("pause");    
	return 0;
}

__global__ void Multiply(__int64* array_1, __int64* array_2, __int64* array_3)
{
	size_t index = threadIdx.x + blockIdx.x * blockDim.x;
	while (index < N)
	{
		array_3[index] = array_1[index] + array_2[index];
		index += blockDim.x * gridDim.x;
	}


	/*size_t index_x = blockIdx.x;
	size_t index_y = threadIdx.x + blockIdx.x * blockDim.x;
	while (index_y < N)
	{
		array_3[index_x][index_y] = array_1[index_x][index_y] + array_2[index_x][index_y];
		index_y += blockDim.x * gridDim.x;
	}*/
}