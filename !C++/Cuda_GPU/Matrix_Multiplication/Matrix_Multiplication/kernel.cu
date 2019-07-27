
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////
//GPU

#define NEW_LINE '\n'


#define D2H cudaMemcpyDeviceToHost
#define H2D cudaMemcpyHostToDevice

#define BLOCK_SIZE 10	//height
#define GRID_SIZE 10	//width

//__global__ void Fill_Array(int** array_2D);
//__global__ void Multiply(int** array_2D, int n);

int main(int argc, char* argv[])
{
	//int **array_2D_GPU;
	//int array_2D_CPU[GRID_SIZE][BLOCK_SIZE]{};
	////constexpr size_t array_2D_GPU_size_i = DIM;

	//dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE); // so your threads are BLOCK_SIZE*BLOCK_SIZE, 256 in this case
	//dim3 dimGrid(GRID_SIZE, GRID_SIZE); // 1*1 blocks in a grid

	//HANDLE_ERROR(cudaMalloc((void***)& array_2D_GPU, array_2D_GPU_size));
	////HANDLE_ERROR(cudaMalloc((void**)&array_2D, array_2D_size * sizeof(int)));
	////HANDLE_ERROR(cudaMalloc((void**)&array_2D, DIM * sizeof(int)));

	////Fill the array
	///*Fill_Array<<<DIM, DIM>>>(array_2D_GPU);
	//Multiply<<<DIM, DIM>>>(array_2D_GPU,2);*/

	//HANDLE_ERROR(cudaMemcpy(array_2D_CPU, array_2D_GPU, array_2D_GPU_size, cudaMemcpyDeviceToHost));
	//// Wyświetlenie wyniku
	//for (size_t i = 0; i < array_2D_GPU_size; i++)
	//{
	//	std::cout << '|';
	//	for (size_t j = 0; j < array_2D_GPU_size; j++)
	//	{
	//		std::cout << array_2D_CPU[i][j] << '|';
	//	}
	//	std::cout << NEW_LINE;
	//}

	//cudaFree(array_2D_GPU);
	//FOR GPU
	//int** array_2D_GPU;
	//int** array_2D_CPU;
	//constexpr size_t array_size_GPU = (GRID_SIZE * BLOCK_SIZE * sizeof(int));

	////allocation
	//HANDLE_ERROR(cudaMalloc((void**)&array_2D_GPU, (GRID_SIZE*sizeof(int*))));
	//HANDLE_ERROR(cudaMemcpy(array_2D_GPU, array_2D_CPU, array_size_GPU, D2H));
	//for (size_t i = 0; i < GRID_SIZE; i++)
	//{
	//	cudaMalloc((void**)&array_2D_GPU[i], BLOCK_SIZE * sizeof(int));
	//}
	//HANDLE_ERROR(cudaMemcpy(array_2D_CPU, array_2D_GPU, array_size_GPU, H2D));
	int** ppArray_a{}, ** ppArray_b{};
	const size_t size = 10;
	cudaMalloc((void**)& ppArray_a, 10 * sizeof(int*));

	for (int i = 0; i < 10; i++)

	{

		cudaMalloc(&ppArray_b[i], 100 * sizeof(int)); /* Replace 100 with the dimension that u want */

	}

	cudaMemcpy(ppArray_a, ppArray_b, 10 * sizeof(int*), H2D);
	//FOR CPU
	//int array_2D_CPU[GRID_SIZE][BLOCK_SIZE]{};
	//constexpr size_t array_size_CPU = (GRID_SIZE * BLOCK_SIZE * sizeof(int));
	//int* dev_a{};
	//// Alokacja pamięci na GPU
	//HANDLE_ERROR(cudaMalloc((void**)& dev_a, 10 * sizeof(int)));
	//cudaFree(array_2D_GPU);
	system("pause");
	return 0;
}

/////////////////////////////////////////////////////////////////