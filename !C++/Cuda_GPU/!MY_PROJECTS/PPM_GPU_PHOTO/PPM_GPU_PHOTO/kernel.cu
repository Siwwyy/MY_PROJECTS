
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#ifndef __CUDACC__
#define __CUDACC__
#endif
#include "device_functions.h"


#include "..//..//..//common/book.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



////////////////////////////////////////////////////
//GPU

#define HostToDevice cudaMemcpyHostToDevice
#define DeviceToHost cudaMemcpyDeviceToHost
#define OK cudaSuccess
#define NEW_LINE '\n'
#define N 100
#define Amount_Of_Blocks 655
#define Amount_Of_Threads 1024

class Pixel_GPU
{
private:
	/*
		PRIVATE VARIABLES
	*/
	unsigned char R;
	unsigned char G;
	unsigned char B;
	int color_range;
	//////////////////////////////////////////////////////////////////////////////
protected:
	/*
		PROTECTED VARIABLES
	*/

	//////////////////////////////////////////////////////////////////////////////
public:
	/*
		KONSTRUKTORY
	*/
	__host__ __device__ Pixel_GPU();
	__host__ __device__ explicit Pixel_GPU(const unsigned char R, const unsigned char G, const unsigned char B);
	__host__ __device__ Pixel_GPU(const Pixel_GPU& Object);
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	__host__ void Show_Object() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY
	*/
	__host__ __device__ void Set_R(const unsigned char R);
	__host__ __device__ void Set_G(const unsigned char G);
	__host__ __device__ void Set_B(const unsigned char B);
	__host__ __device__ void Set_Color_Range(const int Color_Range);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY
	*/
	__host__ __device__ const unsigned char Get_R() const;
	__host__ __device__ const unsigned char Get_G() const;
	__host__ __device__ const unsigned char Get_B() const;
	__host__ __device__ const int Get_Color_Range() const;
	//__host__ __device__ Pixel_GPU * Get_Pointer() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		OPERATORY
	*/
	//JEDNOARGUMENTOWE
	__host__ __device__ Pixel_GPU& operator=(const Pixel_GPU& Object);
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	virtual ~Pixel_GPU();
	//////////////////////////////////////////////////////////////////////////////
};

Pixel_GPU* Host_Array{};
size_t global_size{};
__int64 unique{};
__int32 cos_CPU[Amount_Of_Blocks]{};

void Fill_Array(const _STD string& file_path);
void Show_Array(Pixel_GPU* Pixel_array, const size_t& size);
__global__ void Show_Array_GPU(Pixel_GPU* Pixel_array, const size_t * size);
__global__ void Counting_Unique_Colors(Pixel_GPU * Pixel_array, __int64 * unique_colors, const size_t * size);
__global__ void Counting_Unique_Colors(Pixel_GPU * Pixel_array, bool * Is_Unique_or_Not , const size_t * size);
__global__ void Increase(__int64 *& counter);
__global__ void Show_Device_Variables(size_t * size);

/////////////////////////////////////////////////////////////////////
__global__ void Foo_GPU(__int32 * array);
void Foo_CPU(__int32 * array);
/////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	//__int64 * unique_colors{};
	//__int64 unique{};

	//size_t * size{};

	//HANDLE_ERROR(cudaMalloc((void**)& unique_colors, sizeof(__int64)));
	//HANDLE_ERROR(cudaMalloc((void**)& size, sizeof(size_t)));

	////unique_colors = 0;
	////unique = 0;
	////size = 0;

	//Fill_Array("Lena.ppm");

	////Show_Array(Host_Array, global_size);

	//Pixel_GPU* Device_Array{};
	//cudaMalloc((void**)& Device_Array, global_size * sizeof(Pixel_GPU));


	//cudaMemcpy(Device_Array, Host_Array, global_size * sizeof(Pixel_GPU), HostToDevice);
	////cudaMemcpy(&global_size, &size, sizeof(size_t), HostToDevice);
	//cudaMemcpy(size, &global_size, sizeof(size_t), HostToDevice);
	////size = global_size;

	//Counting_Unique_Colors <<<655,1024>>> (Device_Array, unique_colors, size);
	////Counting_Unique_Colors <<<1,1024>>> (Device_Array, unique_colors, size);



	//cudaMemcpy(Host_Array, Device_Array, global_size * sizeof(Pixel_GPU), DeviceToHost);
	//Show_Array(Host_Array, global_size);

	//cudaMemcpy(&unique, unique_colors, sizeof(__int64), DeviceToHost);
	////unique = unique_colors;
	//_STD cout << unique << NEW_LINE;

	//cudaFree(unique_colors);
	//cudaFree(size);
	//cudaFree(Device_Array);

	//free(Host_Array);

	

	/*__int64 *counter_CPU;
	__int64 *counter_GPU;

	counter_CPU = (__int64*)malloc(sizeof(__int64));
	HANDLE_ERROR(cudaMalloc((void**)&counter_GPU, sizeof(__int64)));


	Increase <<<10, 10 >>> (counter_GPU);

	HANDLE_ERROR(cudaMemcpy(counter_CPU, counter_GPU, sizeof(__int64) , DeviceToHost));


	_STD cout << *counter_CPU << NEW_LINE;


	HANDLE_ERROR(cudaFree(counter_GPU));
	free(counter_CPU);*/



	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////


	Fill_Array("Lena.ppm");


	///////////////////////////////////////////////////////////////
	Pixel_GPU* Device_Array{};
	cudaMalloc((void**)& Device_Array, global_size * sizeof(Pixel_GPU));

	bool* Is_Unique_or_Not{};
	cudaMalloc((void**)& Is_Unique_or_Not, global_size * sizeof(bool));
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	size_t* size{};
	cudaMalloc((void**)& size, sizeof(size_t));
	cudaMemset(size, 0, sizeof(size_t));
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	__int64* unique_colors{};
	cudaMalloc((void**)& unique_colors, sizeof(__int64));
	cudaMemset(unique_colors, 0, sizeof(__int64));
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	/*__int32* cos_GPU{};
	cudaMalloc((void**)& cos_GPU, sizeof(__int32) * Amount_Of_Blocks);
	cudaMemset(cos_GPU, 0, sizeof(__int32) * Amount_Of_Blocks);*/
	///////////////////////////////////////////////////////////////


	cudaMemcpy(Device_Array, Host_Array, global_size * sizeof(Pixel_GPU), HostToDevice);
	cudaMemcpy(size, &global_size, sizeof(size_t), HostToDevice);


	//Case for tests only
	//_STD cout << global_size << NEW_LINE;
	//Show_Device_Variables <<<1, 1>>>(size);
	//cudaMemcpy(&global_size, size, sizeof(size_t), DeviceToHost);
	//_STD cout << global_size << NEW_LINE;
	///////////////////////////////////////////////////////////////


	Counting_Unique_Colors <<<Amount_Of_Blocks, Amount_Of_Threads>>> (Device_Array, Is_Unique_or_Not, size);

	//cudaMemcpy(Host_Array, Device_Array, global_size * sizeof(Pixel_GPU), DeviceToHost);
	cudaMemcpy(Host_Array, Device_Array, sizeof(Pixel_GPU)* global_size, DeviceToHost);
	//for (size_t i = 0; i < global_size; ++i)
	//{
	//	cudaMemcpy(Host_Array, Device_Array , sizeof(Pixel_GPU) * global_size, DeviceToHost);	//for dynamic allocation
	//}

	//cudaMemcpy(&unique, unique_colors, sizeof(__int64), DeviceToHost);
	//for (size_t i = 0; i < global_size; ++i)
	//{
	//	if()
	//}

	//_STD cout << "Unique colors: " << unique << NEW_LINE;

	//for (size_t i = 0; i < global_size; ++i)
	//{
	//	if (Host_Array->Get_Color_Range() == 255)
	//	{
	//		unique++;
	//	}
	//}
	Show_Array_GPU <<< 1,1 >>> (Device_Array, size);
	/*Show_Array(Host_Array, global_size);
	*///_STD cout << "Unique colors: " << unique << NEW_LINE;

	//Case for tests only
	/*Foo_GPU <<< 50, 1 >>> (cos_GPU);
	cudaMemcpy(cos_CPU, cos_GPU, sizeof(__int32)* Amount_Of_Blocks, DeviceToHost);
	Foo_CPU(cos_CPU);*/
	///////////////////////////////////////////////////////////////\




	//Delete the allocated memory
	cudaFree(size);
	cudaFree(Device_Array);
	cudaFree(Is_Unique_or_Not);
	cudaFree(unique_colors);

	free(Host_Array);

	system("pause");
	return 0;
}


void Fill_Array(const _STD string& file_path)
{
	_STD fstream file;
	file.open(file_path.c_str(), std::ios_base::in);
	_STD string line{};
	__int32 a{ 1 };
	Pixel_GPU Temporary_Pixel{};
	std::string extension{};					//extension (p1,p2,p3 etc)
	__int32 width{};							//width
	__int32 height{};							//height
	__int32 color_range{};						//color range
	static size_t i = 0;
	if (file.good() == false)
	{
		exit(0);
	}
	else
	{
		while (file.eof() == false)
		{
			if (a < 5)
			{
				_STD getline(file, line);
				if (a == 1)
				{
					extension = line;
				}
				else if (a == 3)
				{
					_STD string line_second = "";
					int counter = 0;
					for (int i = 0; i < line.size(); i++)
					{
						if (line[i] == ' ')
						{
							width = stoi(line_second);
							line_second = "";
						}
						else
						{
							line_second += line[i];
						}
						counter++;
					}
					height = stoi(line_second);
					global_size = static_cast<size_t>(width * height);
					Host_Array = (Pixel_GPU*)malloc(global_size * sizeof(Pixel_GPU));
				}
				else if (a == 4)
				{
					color_range = (stoi(line));
				}
			}
			else if (a >= 5)
			{
				int color = 0;
				file >> color;
				Temporary_Pixel.Set_R(color);
				color = 0;
				file >> color;
				Temporary_Pixel.Set_G(color);
				color = 0;
				file >> color;
				Temporary_Pixel.Set_B(color);
				//Temporary_Pixel.Set_Color_Range(color_range);
				color = 0;
				Host_Array[i++] = Temporary_Pixel;
			}
			line = "";
			a++;
		}
	}
	_STD cout << "--------------------------" << NEW_LINE;
	_STD cout << "  Information" << NEW_LINE;
	_STD cout << "  Loaded format: " << extension << NEW_LINE;
	_STD cout << "  Width: " << width << NEW_LINE;
	_STD cout << "  Height: " << height << NEW_LINE;
	_STD cout << "  Color Range: " << color_range << NEW_LINE;
	_STD cout << "------------------------" << NEW_LINE;
	//_STD cout << "  Array size: " << static_cast<size_t>(Pixel_array.size()) << NEW_LINE;
	_STD cout << "  Array size: " << static_cast<size_t>((global_size)) << NEW_LINE;
	_STD cout << "------------------------" << NEW_LINE;
	file.close();
}

void Show_Array(Pixel_GPU* Pixel_array, const size_t& size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (Pixel_array[i].Get_Color_Range() > 255)
		{
			Pixel_array[i].Show_Object();
			_STD cin.get();
		}
	/*	Pixel_array[i].Show_Object();
		_STD cin.get();*/
	}
}

__global__ void Show_Array_GPU(Pixel_GPU* Pixel_array, const size_t* size)
{
	int a{};
	for (size_t i = 0; i < *size; i++)
	{
		if (Pixel_array[i].Get_Color_Range() == 255)
		{
			printf("The Size is following: %u \n", Pixel_array[i].Get_Color_Range());
			//++a;
			//_STD cin.get();
		}
	}
	//printf("The Size is following: %u \n", a);
}

__global__ void Counting_Unique_Colors(Pixel_GPU* Pixel_array, __int64 * unique_colors, const size_t * size)
{
	//int id = threadIdx.x + blockIdx.x * blockDim.x;
	//int j = threadIdx.y + blockIdx.y * blockDim.y;
	//bool is_unique = true;
	//const int color_range = Pixel_array[0].Get_Color_Range();
	//if (id < *size)
	//{
	//	//if (Pixel_array[id].Get_Color_Range() > color_range)
	//	//{
	//	//	continue;
	//	//}
	//	//else
	//	//{
	//	
	//	//}
	//	//__syncthreads();
	//	while (j < *size)
	//	{
	//		/*	Pixel_array[j].Set_Color_Range(static_cast<int>(color_range + 100));
	//			Pixel_array[j].Set_R(static_cast<int>(color_range + 100));*/
	//	/*	if (Pixel_array[id].Get_R() == Pixel_array[j].Get_R() && Pixel_array[id].Get_G() == Pixel_array[j].Get_G() && Pixel_array[id].Get_B() == Pixel_array[j].Get_B())
	//		{
	//			Pixel_array[j].Set_Color_Range(static_cast<int>(color_range + 100));
	//		}*/
	//		Pixel_array[j].Set_Color_Range(static_cast<int>(color_range + 100));
	//		j++;
	//	}
	//	//__syncthreads();
	//	//Pixel_array[id].Set_Color_Range(static_cast<int>(color_range + 100));
	//	//__syncthreads();
	//	/*Pixel_array[id].Set_Color_Range(static_cast<int>(color_range + 100));
	//	Pixel_array[id].Set_R(static_cast<int>(color_range + 100));
	//	id += blockDim.x * gridDim.x;*/
	//}
	//int id_x = threadIdx.x + blockIdx.x * blockDim.x;
	int id_x = blockIdx.x;
	//int id_y = threadIdx.y + blockIdx.y * blockDim.y;
	//const int color_range = Pixel_array[0].Get_Color_Range();

	printf("The Size is following: %u [%u] \n", *size);
	if (id_x < *size)
	{
		/*while (id_y < *size)
		{
			if (Pixel_array[id_x].Get_R() == Pixel_array[id_y * (*size) + id_x].Get_R() && Pixel_array[id_x].Get_G() == Pixel_array[id_y * (*size) + id_x].Get_G() && Pixel_array[id_x].Get_B() == Pixel_array[id_y * (*size) + id_x].Get_B())
			{
				Pixel_array[id_x].Set_Color_Range(static_cast<int>(color_range + 100));
				__syncthreads();
			}
			id_y += blockDim.y * gridDim.y;
		}

		if (Pixel_array[id_x].Get_Color_Range() == color_range)
		{
			++(*unique_colors);
			__syncthreads();
		}*/
		++(*unique_colors);
		//__syncthreads();
		//id_x += blockDim.x * gridDim.x;
	}
	
	//(*unique_colors) = 1000;
	//printf("Unique colors: %u \n", *unique_colors);
}

__global__ void Counting_Unique_Colors(Pixel_GPU* Pixel_array, bool * Is_Unique_or_Not, const size_t* size)
{
	int id_x = threadIdx.x + blockIdx.x * blockDim.x;
	int id_y = threadIdx.y + blockIdx.y * blockDim.y;
	const int color_range = Pixel_array[0].Get_Color_Range();

	//printf("The Size is following: %u [%u] \n", *size);
	while (id_x < *size)
	{
		if (Pixel_array[id_x].Get_Color_Range() > 255)
		{
			continue;
		}
		else
		{
			while ((id_y + 1) < *size)
			{
				if (Pixel_array[id_x].Get_R() == Pixel_array[id_y * (*size) + id_x].Get_R() && 
					Pixel_array[id_x].Get_G() == Pixel_array[id_y * (*size) + id_x].Get_G() && 
					Pixel_array[id_x].Get_B() == Pixel_array[id_y * (*size) + id_x].Get_B())
				{
					Pixel_array[id_x].Set_Color_Range(static_cast<int>(color_range + (id_y * (*size) + id_x) + 1));
					printf("Color range: %u \n", Pixel_array[id_x].Get_Color_Range());
					//break;
					__syncthreads();
				}
				id_y += blockDim.y * gridDim.y;
			}
		}
		
		//__syncthreads();
		id_x += blockDim.x * gridDim.x;
	}
	//__syncthreads();

	//if (Pixel_array[id_x].Get_Color_Range() == color_range)
	//{
	//
	//	__syncthreads();
	//}
}

__global__ void Increase(__int64 *& counter)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	if (id < N)
	{
		__syncthreads();
		++((counter));
		__syncthreads();
	}
}

__global__ void Show_Device_Variables(size_t * size)
{
	printf("The Size is following: %u \n", *size);
	//*size = 100;
}

__global__ void Foo_GPU(__int32* array)
{
	int id = blockIdx.x;
	//int id = threadIdx.x + blockIdx.x * blockDim.x;
	while (id < Amount_Of_Blocks)
	{
		array[id] = 10;
		id += blockDim.x * gridDim.x;
	}
}

void Foo_CPU(__int32* array)
{
	for (size_t i = 0; i < Amount_Of_Blocks; ++i)
	{
		_STD cout << array[i] << ' ' << i << NEW_LINE;
	}
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/*
	PIXEL_GPU CLASS CASE
*/
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


__host__ __device__ Pixel_GPU::Pixel_GPU() :
	R(NULL),
	G(NULL),
	B(NULL),
	color_range(255)
{
	//Nothing here
}

__host__ __device__  Pixel_GPU::Pixel_GPU(const unsigned char R, const unsigned char G, const unsigned char B) :
	R(R),
	G(G),
	B(B),
	color_range(255)
{
	//Nothing here
}

__host__ __device__  Pixel_GPU::Pixel_GPU(const Pixel_GPU& Object) :
	R(Object.R),
	G(Object.G),
	B(Object.B),
	color_range(Object.color_range)
{
	//Nothing here
}

__host__ void Pixel_GPU::Show_Object() const
{
	_STD cout << "Red: [" << static_cast<int>(this->R) << " ] " << "Green: [" << static_cast<int>(this->G) << " ] " << "Blue: [" << static_cast<int>(this->B) << " ] " << "Color range: " << this->color_range << NEW_LINE;
}

__host__ __device__ void Pixel_GPU::Set_R(const unsigned char R)
{
	this->R = R;
}

__host__ __device__ void Pixel_GPU::Set_G(const unsigned char G)
{
	this->G = G;
}

__host__ __device__ void Pixel_GPU::Set_B(const unsigned char B)
{
	this->B = B;
}

__host__ __device__  void Pixel_GPU::Set_Color_Range(const int Color_Range)
{
	this->color_range = Color_Range;
}

__host__ __device__ const unsigned char Pixel_GPU::Get_R() const
{
	return this->R;
}

__host__ __device__ const unsigned char Pixel_GPU::Get_G() const
{
	return this->G;
}

__host__ __device__ const unsigned char Pixel_GPU::Get_B() const
{
	return this->B;
}

__host__ __device__ const int Pixel_GPU::Get_Color_Range() const
{
	return this->color_range;
}

//__host__ __device__ Pixel_GPU * Pixel_GPU::Get_Pointer() const
//{
//	return ;
//}

__host__ __device__ Pixel_GPU& Pixel_GPU::operator=(const Pixel_GPU& Object)
{
	//if (this != _STD addressof(Object))
	if (this != &Object)
	{
		this->R = Object.R;
		this->G = Object.G;
		this->B = Object.B;
		this->color_range = Object.color_range;
	}
	return *this;
}

Pixel_GPU::~Pixel_GPU()
{
	this->R = NULL;
	this->B = NULL;
	this->B = NULL;
}


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////






//RUBBISH
//char abc[4][4][4]{};// = { 1,2,3,4 };

	//int cos{97};
	//for (size_t i = 0; i < 4; i++)
	//{
	//	for (size_t j = 0; j < 4; j++)
	//	{
	//		for (size_t k = 0; k < 4; k++)
	//		{
	//			abc[i][j][k] = (char)(cos++);
	//		}
	//	
	//	}
	//}



	/*for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				_STD cout << abc[i][j][k] << ' ';
			}
			_STD cout << NEW_LINE;
		}
		_STD cout << NEW_LINE;
	}*/
	//_STD cout << abc[0][1][3] << ' ';
