
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


////////////////////////////////////////////////////
//GPU

#define HostToDevice cudaMemcpyHostToDevice
#define DeviceToHost cudaMemcpyDeviceToHost
#define OK cudaSuccess
#define NEW_LINE '\n'
#define N 100
#define Amount_Of_Blocks 655
#define Amount_Of_Threads 1024

//SELF HEADERS
#include "Functions.hpp"
////////////////////////////////////

int main(int argc, char* argv[])
{
	using Functions::Read_BitMap;

	_STD string file_path = "bitmap1.png";

	Read_BitMap(file_path.c_str());

	system("pause");
	return 0;
}