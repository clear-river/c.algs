#include <stdio.h>
#include <stdlib.h>

int A[9] = {83, 89, 62, 94, 56, 69, 78, 92, 100};

void sort(int* a, int n){
	int key = 0, i = 0;
	if (n == 0) return;
	sort(a, n-1);
	key = a[n]; i = n-1;
	while(a[i]>key && i>=0){
		a[i+1] = a[i];
		i--;
	}
	a[i+1] = key;
	return;
}

int main(int argc, char** argv){
	int i = 0;
	sort(A, 8);
	for (;i<9;i++){
		printf("%d,", A[i]);
	}
	printf("\n");
	return 0;
}