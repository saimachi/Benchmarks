#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define ARRSIZE 1000000

int main() {
	int *A, *B, *C;
	A = (int *)malloc(ARRSIZE*sizeof(int));
	B = (int *)malloc(ARRSIZE*sizeof(int));
	C = (int *)malloc(ARRSIZE*sizeof(int));

	for (int i = 0; i < ARRSIZE; i++) {
		A[i] = i;
		B[i] = i;
	}
	
	struct timeval start, end;
	gettimeofday(&start, NULL);
	#pragma omp parallel for default(none) shared(A,B,C)
	for (int i = 0; i < ARRSIZE; i++) {
		C[i] = A[i] + B[i];
	}
	gettimeofday(&end, NULL);

	double time_taken = (end.tv_sec) + (end.tv_usec/1e6) - ((start.tv_sec) + (start.tv_usec/1e6));
	printf("Time taken to add integer arrays of length %d: %g (seconds)\n", ARRSIZE, time_taken);

	free(A);
	free(B);
	free(C);
}
