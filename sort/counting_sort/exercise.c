#include <stdlib.h>
#include <stdio.h>

void dump_a(int *a, int n){
	int i = 0;
	for(; i<n; i++){
		printf("%d,", a[i]);
	}
	putchar(0x08);putchar(0x20);
	printf("\n");
}

#include "./algorithm.h"

int main(int argc, char* argv[]){
	int A[6] = {13, 19, 19, 5, 12, 16};
	sort(A, 6, 19);
	dump_a(A, 6);
	return 0;
}
