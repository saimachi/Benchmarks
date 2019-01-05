#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 10000

int main() {
	printf("The array size is: %d. The benchmark involves 64-bit integers!\n", ARR_SIZE);
	long long int *buf;
	buf = (long long int *)malloc(ARR_SIZE * sizeof(long long int));

	long long int *buf2;
	buf2 = (long long int *)malloc(ARR_SIZE * sizeof(long long int));

	long long int *prod;
	prod = (long long int *)malloc(ARR_SIZE * sizeof(long long int));

	//Initialize multiplicands with some values first
	for (int i = 0; i < ARR_SIZE; i++) {
		buf[i] = i*ARR_SIZE;
		buf2[i] = i*ARR_SIZE;
	}
	
	//We only want to measure the time that the matrix multiplication takes
	clock_t begin = clock(); 
	
	for (int index = 0; index < ARR_SIZE; index++) {
		prod[index] = buf[index] * buf2[index];
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken (no OpenMP nor SIMD): %f (seconds)\n", time_spent);

	//Let's clear our product array
	memset(prod, 0, ARR_SIZE*sizeof(prod));

	begin = clock();

	#pragma omp for
	for (int index = 0; index < ARR_SIZE; index++) {
		prod[index] = buf[index] * buf2[index];
	}

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken (with OpenMP): %f (seconds)\n", time_spent);

	memset(prod, 0, ARR_SIZE*sizeof(prod));

	begin = clock();

	#pragma omp simd
	for (int index = 0; index < ARR_SIZE; index++) {
		prod[index] = buf[index] * buf2[index];
	}

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken (with SIMD): %f (seconds)\n", time_spent);

	//Free our allocated arrays
	free(prod);
	free(buf);
	free(buf2);
}
