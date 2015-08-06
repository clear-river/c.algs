#include <stdio.h>
#include <stdlib.h>

int A[9] = {51,62,69,78,83,89,92,94,100};

#include "./algorithm.h"

int main(int argc, char** argv){
	int hit = 0;
	int i70 = 0, i78 = 0, i80 = 0;
	/*printf("%d\n", biSearch(A, &hit, 0, 8, 70));
	printf("%d\n", biSearch(A, &hit, 0, 8, 78));
	printf("%d\n", biSearch(A, &hit, 0, 8, 80));*/
	i70 = biSearch(A, &hit, 0, 8, 70);
	if (!hit) printf("70 found at %d.\n", i70);
		else printf("70 not found. The greatest number less than 70 is found at %d being %d.\n", i70, A[i70]);
	//hit = 0;
	i78 = biSearch(A, &hit, 0, 8, 78);
	if (!hit) printf("78 found at %d.\n", i78);
		else printf("78 not found. The greatest number less than 78 is found at %d being %d.\n", i78, A[i78]);
	//hit = 0;
	i80 = biSearch(A, &hit, 0, 8, 80);
	if (!hit) printf("80 found at %d.\n", i80);
		else printf("80 not found. The greatest number less than 80 is found at %d being %d.\n", i80, A[i80]);
	return 0;
}
