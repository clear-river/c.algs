#include <stdio.h>

int main(int argc, char ** argv){
	int A[6] = {57,254,105, 2, 570, 300};
	int key = A[1];
	//printf("%d %d %d\n", A[0], A[1], A[2]);
	
	for (int i = 1; i< 6; i++){
		key = A[i];
		int j=0;
		for (j = i-1; j>=0; j--){
			printf("i=%d j=%d\n", i, j);
			if (A[j] > key){
				A[j+1] = A[j];
				printf("%d relocated\n", A[j]);
			}else{
				printf("break\n");
				break;
			}
		}
		printf("a[%d+1] = %d\n", j, key);
		A[j+1] = key;
		printf("\n\n");
	}
	printf("%d %d %d %d %d %d\n", A[0], A[1], A[2], A[3], A[4], A[5]);
	return 0;
}

