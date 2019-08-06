
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


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
	__host__ __device__ void Show_Object() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY
	*/
	__host__ __device__ void Set_R(const unsigned char R);
	__host__ __device__ void Set_G(const unsigned char G);
	__host__ __device__ void Set_B(const unsigned char B);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY
	*/
	__host__ __device__ const unsigned char Get_R() const;
	__host__ __device__ const unsigned char Get_G() const;
	__host__ __device__ const unsigned char Get_B() const;
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
__global__ void Counting_Unique_Colors(Pixel_GPU * Pixel_array, __int64 & unique_colors, const size_t & size);

int main(int argc, char* argv[])
{
	__int64 unique_colors{};
	__int64 unique{};
	size_t size{};

	HANDLE_ERROR(cudaMalloc((void**)& unique_colors, sizeof(__int64)));
	HANDLE_ERROR(cudaMalloc((void**)& size, sizeof(size_t)));

	unique_colors = 0;
	unique = 0;
	size = 0;

	Fill_Array("Lena.ppm");


	Pixel_GPU* Device_Array{};
	cudaMalloc((void**)& Device_Array, global_size * sizeof(Pixel_GPU));


	cudaMemcpy(Device_Array, Host_Array, global_size * sizeof(Pixel_GPU), HostToDevice);
	//cudaMemcpy(&global_size, &size, sizeof(size_t), HostToDevice);
	//cudaMemcpy(&size, &global_size, sizeof(size_t), HostToDevice);
	size = global_size;

	Counting_Unique_Colors <<<655,1024>>> (Device_Array, unique_colors, size);
	//Counting_Unique_Colors <<<1,1024>>> (Device_Array, unique_colors, size);



	//cudaMemcpy(&unique, &unique_colors, sizeof(__int64), DeviceToHost);
	unique = unique_colors;
	_STD cout << unique << NEW_LINE;

	cudaFree(&unique_colors);
	cudaFree(&size);
	cudaFree(Device_Array);

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

__global__ void Counting_Unique_Colors(Pixel_GPU* Pixel_array, __int64 & unique_colors, const size_t& size)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	bool is_unique = true;
	//int j = id + 1;
	while (id < size)
	{
		is_unique = true;
		for (int j = id + 1; j < size; j += blockDim.x * gridDim.x)
		{
			if (Pixel_array[id].Get_R() == Pixel_array[j].Get_R() && Pixel_array[id].Get_G() == Pixel_array[j].Get_G() && Pixel_array[id].Get_B() == Pixel_array[j].Get_B())
			{
				is_unique = false;
				break;
			}
		}
		if (is_unique == true)
		{
			
		}
		//if (Pixel_array[id].Get_R() == Pixel_array[j].Get_R() && Pixel_array[id].Get_G() == Pixel_array[j].Get_G() && Pixel_array[id].Get_B() == Pixel_array[j].Get_B())
		//{
		//	is_unique = false;
		////	break;
		//}
		else
		{
			++unique_colors;
		}
		//unique_colors = id;
		id += blockDim.x * gridDim.x;
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
	B(NULL)
{
	//Nothing here
}

__host__ __device__  Pixel_GPU::Pixel_GPU(const unsigned char R, const unsigned char G, const unsigned char B) :
	R(R),
	G(G),
	B(B)
{
	//Nothing here
}

__host__ __device__  Pixel_GPU::Pixel_GPU(const Pixel_GPU& Object) :
	R(Object.R),
	G(Object.G),
	B(Object.B)
{
	//Nothing here
}

__host__ __device__ void Pixel_GPU::Show_Object() const
{
	//_STD cout << "Red: [" << this->R << " ] " << "Green: [" << this->G << " ] " << "Blue: [" << this->B << " ] " << NEW_LINE;
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