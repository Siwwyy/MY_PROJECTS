
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <windows.h>

#include "..//..//common/book.h"

__global__ void Hello_WORD_GPU(void)
//__global__ void Hello_WORD_GPU(int & i)
{
	//static int i;
	printf("HELLO WORD GPU ! \n");
	//printf("HELLO WORD GPU !%\d \n", i++);
}

//void Hello_WORD_CPU()
//{
//	printf("HELLO WORD CPU ! \n");
//}

//int main()
//{
//	//Hello_WORD_CPU();
////	int i = 0;
//	printf("HELLO WORD CPU ! \n");
//	Hello_WORD_GPU <<<10, 1>>>();;
//	cudaDeviceReset();
//	system("pause");
//    return 0;
//}

//int main()
//{
//	//Hello_WORD_CPU();
////	int i = 0;
//	cudaDeviceProp prop{};
//	int count{};
//	HANDLE_ERROR(cudaGetDeviceCount(&count));
//	for (int i = 0; i < count; i++)
//	{
//		HANDLE_ERROR(cudaGetDeviceProperties(&prop, i));
//		//Kod wykorzystujący zdobyte informacje o właściwościach
//	}
//	system("pause");
//	return 0;
//}

int main()
{
	cudaDeviceProp prop;
	int count;
	HANDLE_ERROR(cudaGetDeviceCount(&count));
	for (int i = 0; i < count; i++)
	{
		HANDLE_ERROR(cudaGetDeviceProperties(&prop, i));
		printf(" --- Ogólne informacje o urządzeniu %d — \n", i);
		printf("Nazwa: %s\n", prop.name);
		printf("Potencjal obliczeniowy: %d.%d\n", prop.major, prop.minor);
		printf("Zegar: %d\n", prop.clockRate);
		printf("Ustawienie deviceOverlap: ");
		if (prop.deviceOverlap)
			printf("Wlączone\n");
		else
			printf("Wylączone\n");

		printf("Limit czasu dziatania jądra: ");
		if (prop.kernelExecTimeoutEnabled)
			printf("Wylaczony\n");
		else
			printf("Wylaczony\n");
		printf("Informacje o pamięci urządzenia %d '\n", i);
		printf("Ilość pamięci globalnej: %ld\n", prop.totalGlobalMem);
		printf("Ilość pamięci stalej: %ld\n", prop.totalConstMem);
		printf("Maks. szerokość pamięci: %ld\n", prop.memPitch);
		printf("Wyrównanie tekstur: %ld\n", prop.textureAlignment);
		printf("Informacje na temat wieloprocesorów urządzenia %d \n", i);
		printf("Liczba wieloprocesorów: %d\n",
			prop.multiProcessorCount);
		printf("Pamięć wspolna na wieloprocesor: %ld\n", prop.sharedMemPerBlock);
		printf("Rejestry na wieloprocesor: %d\n", prop.regsPerBlock);
		printf("Liczba wątków w osnowie: %d\n", prop.warpSize);
		printf("Maks. liczba watkow na blok: %d\n",
			prop.maxThreadsPerBlock);
		printf("Maks. liczba wymiarów wątków: (%d, %d, %d)\n",
			prop.maxThreadsDim[0], prop.maxThreadsDim[i],
			prop.maxThreadsDim[2]);
		printf("Maks. liczba wymiarów siatki: (%d, %d, %d)\n",
			prop.maxGridSize[0], prop.maxGridSize[i],
			prop.maxGridSize[2]);
		printf("\n");
	}
	system("pause");
	return 0;
}