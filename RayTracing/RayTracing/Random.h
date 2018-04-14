#pragma once
namespace YQS
{
	#include <stdlib.h>  
	
	#define RANDOM_M 0x100000000LL  
	#define RANDOM_C 0xB16  
	#define RANDOM_A 0x5DEECE66DLL  

	static unsigned long long seed = 1;

	double drand48()
	{
		seed = (RANDOM_A * seed + RANDOM_C) & 0xFFFFFFFFFFFFLL;
		auto x = seed >> 16;
		return  (x / static_cast<double>(RANDOM_M));

	}

	void srand48(unsigned int i)
	{
		seed = (static_cast<long long int>(i) << 16) | rand();
	}
}