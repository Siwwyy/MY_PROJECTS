
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

void Fill_Array(const _STD string& file_path);
void Show_Array(Pixel_GPU* Pixel_array, const size_t& size);
__global__ void Counting_Unique_Colors(Pixel_GPU * Pixel_array, __int64 * unique_colors, const size_t * size);

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

	char abc[4][4][4]{};// = { 1,2,3,4 };

	int cos{97};
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				abc[i][j][k] = (char)(cos++);
			}
		
		}
	}



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
	_STD cout << abc[0][1][3] << ' ';

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

__global__ void Counting_Unique_Colors(Pixel_GPU* Pixel_array, __int64 * unique_colors, const size_t * size)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;
	bool is_unique = true;
	const int color_range = Pixel_array[0].Get_Color_Range();
	if (id < *size)
	{
		//if (Pixel_array[id].Get_Color_Range() > color_range)
		//{
		//	continue;
		//}
		//else
		//{
		
		//}
		//__syncthreads();
		while (j < *size)
		{
			/*	Pixel_array[j].Set_Color_Range(static_cast<int>(color_range + 100));
				Pixel_array[j].Set_R(static_cast<int>(color_range + 100));*/
		/*	if (Pixel_array[id].Get_R() == Pixel_array[j].Get_R() && Pixel_array[id].Get_G() == Pixel_array[j].Get_G() && Pixel_array[id].Get_B() == Pixel_array[j].Get_B())
			{
				Pixel_array[j].Set_Color_Range(static_cast<int>(color_range + 100));
			}*/
			Pixel_array[j].Set_Color_Range(static_cast<int>(color_range + 100));
			j++;
		}
		//__syncthreads();
		//Pixel_array[id].Set_Color_Range(static_cast<int>(color_range + 100));
		//__syncthreads();
		/*Pixel_array[id].Set_Color_Range(static_cast<int>(color_range + 100));
		Pixel_array[id].Set_R(static_cast<int>(color_range + 100));
		id += blockDim.x * gridDim.x;*/
	}

	id = threadIdx.x + blockIdx.x * blockDim.x;
	if (Pixel_array[id].Get_Color_Range() == color_range)
	{
		++(*unique_colors);
	}
	//(*unique_colors) = 1000;

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