#include <stdio.h>

int main(int argc, char** argv){
	int A[5] = {1, 25, 78, 92, 76};
	for (int i = 1; i < 5; i ++){
		int key = A[i];
		int j;
		for (j = i-1; j >=0; j--){
			if (A[j] > key)
				A[j+1] = A[j];
			else
				break;
		}
		A[j+1] = key;
	}
	
	//output
	for (int i = 0; i<5; i++){
		printf ("%d ", A[i]);
	}
	printf ("\n");
	return 0;
}