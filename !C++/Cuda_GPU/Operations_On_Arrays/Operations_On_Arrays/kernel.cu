//#define __cplusplus
//#define __CUDACC__
//#define __CUDACC_RTC__

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "..//..//common/book.h"

#include "..//..//Operations_On_Arrays/Operations_On_Arrays/Pixel.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

////////////////////////////////////////////////////
//GPU

#define HostToDevice cudaMemcpyHostToDevice
#define DeviceToHost cudaMemcpyDeviceToHost
#define OK cudaSuccess
#define NEW_LINE '\n'



void Fill_Array(const _STD string& file_path, _STD vector<RGB::Pixel> & Pixel_array);
__global__ void Counting_Unique_Colors(_STD vector<RGB::Pixel> & Pixel_array);

int main(int argc, char* argv[])
{
	_STD vector<RGB::Pixel> Pixel_array{};		//vector klasy Pixel

	Fill_Array("Lena.ppm", Pixel_array);
	system("pause");
	return 0;
}

void Fill_Array(const _STD string & file_path, _STD vector<RGB::Pixel>& Pixel_array)
{
	_STD fstream file;
	file.open(file_path.c_str(), std::ios_base::in);
	_STD string line{};
	__int32 a{ 1 };
	__int32 licznik{};
	__int32 char_number{};
	RGB::Pixel Temporary_Pixel{};
	std::string extension{};					//extension (p1,p2,p3 etc)
	__int32 width{};							//width
	__int32 height{};							//height
	__int32 color_range{};						//color range

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
					Pixel_array.reserve(width * height);
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
				Pixel_array.emplace_back(Temporary_Pixel);
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
	_STD cout << "  Array size: " << static_cast<size_t>(Pixel_array.size()) << NEW_LINE;
	_STD cout << "------------------------" << NEW_LINE;
	file.close();
}

__global__ void Counting_Unique_Colors(::std::vector<RGB::Pixel>& Pixel_array)
{
	
}