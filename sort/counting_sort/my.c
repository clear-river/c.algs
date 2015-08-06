#include <stdlib.h>
#include <stdio.h>

void dump_a(int *a, int n){
	int i = 0;
	for(; i<n; i++){
		printf("%d,", a[i]);
	}
	printf("\n");
}

void sort(int *data, int n, int ceiling){
    int *count = (int*) malloc((ceiling+1)*sizeof(int));
    int *buffer = (int*) malloc(n*sizeof(int));
    int i=0;
    
    for(i=0; i<=ceiling; i++)
	count[i] = 0;
	
    for(i=0; i<n; i++)
	count[data[i]]++;
	
    for(i=1; i<=ceiling; i++)
	count[i] += count[i-1];
    
    //working, but not steady.
    for(i=0; i<n; i++)
	buffer[--count[data[i]]] = data[i];
	
    free(count);
    
    for(i=0; i<n; i++)
	data[i] = buffer[i];
    free(buffer);
    return;
}

int main(int argc, char* argv[]){
	int A[6] = {13, 19, 19, 5, 12, 16};
	sort(A, 6, 19);
	dump_a(A, 6);
	return 0;
}
