
#include <iostream>
//#include "MemoryManager.h"
#include "Allocator.h"

int main()
{
	/*MemoryAllocator allocator;
	allocator.init();

	int* pi = (int*)allocator.alloc(sizeof(int));
	double* pd = (double*)allocator.alloc(sizeof(double)); 
	int* pa = (int*)allocator.alloc(10 * sizeof(int));
	allocator.dumpStat();
	allocator.dumpBlocks();

	allocator.free(pa);
	allocator.free(pd);
	allocator.free(pi);
	allocator.destroy();*/

	/*size_t sampleSize = 4;
	void* temp = (void*)Scald::malloc(sampleSize);

	std::cout << temp;*/

	Scald::LinearAllocator allocator(_MB(2), 16u);
	allocator.Init();

	void* tempAllocation = allocator.Allocate(256u);
	std::cout << "Allocated memory at address: " << tempAllocation << "\n";
	std::cout << "Current offset: " << allocator.GetCurrentOffset() << "\n";
	void* tempAllocation2 = allocator.Allocate(90u);
	std::cout << "Allocated memory at address: " << tempAllocation2 << "\n";
	std::cout << "Current offset: " << allocator.GetCurrentOffset() << "\n";

	return 0;
}