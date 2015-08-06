#include <stdio.h>
#include <stdlib.h>

int A[10] = {4,1,3,2,16,9,10,14,8,7}; 

void dump_a(int* a, int n){
	int i = 0;
	for(; i<n; i++){
		printf("%d,", a[i]);
	}
	printf("\n");
	return;
}

#include "./algorithm.h"

int main(int argc, char** argv){
	printf("Before heapification:\n");
	dump_a(A, 10);
	//heapify(A, 1, 10);
	heap_sort(A, 10);
	printf("After heapification:\n");
	dump_a(A, 10);
	return 0;
}

