/*
Implement a CUDA program to determine the number of CUDA-capable devices in the system. For each device, examine the following device properties:

- Device name
- Number of Streaming Multiprocessors
- Maximum number of threads per block
- Maximum thread dimensions (x, y, z)
- Maximum grid dimensions (x, y, z)
- Device clock frequency
*/

#include <stdio.h>
#include <cuda_runtime.h>

int main()
{
	int n;

	cudaGetDeviceCount(&n);
	printf("Number of CUDA devices: %d\n", n);

	for (int i = 0; i < n; i++)
	{
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);

		printf("Device %d\n", i);
		printf("Device name: %s\n", prop.name);
		printf("Number of streaming multiprocessors: %d\n", prop.multiProcessorCount);
		printf("Maximum threads per block: %d\n", prop.maxThreadsPerBlock);
		
		printf("Maximum thread dimensions: (%d, %d, %d)\n",
               prop.maxThreadsDim[0],
               prop.maxThreadsDim[1],
               prop.maxThreadsDim[2]);
		printf("Maximum grid dimensions: (%d, %d, %d)\n",
               prop.maxGridSize[0],
               prop.maxGridSize[1],
               prop.maxGridSize[2]);

        printf("Device clock frequency: %.2f MHz\n", prop.clockRate / 1000.0);
        
        printf("\n");
	}

	return 0;
}