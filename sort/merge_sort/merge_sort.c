#include <stdio.h>
#include <stdlib.h>

int A[9] = {83, 89, 62, 94, 56, 69, 78, 92, 100};
int SA[9] = {0};

void dump_array(int *a){
    int i = 0;
    for (; i<9; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}

void merge(int *data, int start, int middle, int end){
	int *buffer = (int*) malloc ((end+1)*sizeof(int));
	int former = start, latter = middle+1, buffer_i = start;
	while (former<middle+1 && latter<end+1)
		buffer[buffer_i++] = (data[former]<data[latter])? data[former++]:data[latter++];
	
	while(former<middle+1)
		buffer[buffer_i++] = data[former++];
	while(latter<end+1)
		buffer[buffer_i++] = data[latter++];
		
	for(buffer_i=start; buffer_i<=end; buffer_i++)
		data[buffer_i] = buffer[buffer_i];
	free(buffer);
}

void merge_sort(int* data, int start, int end){
	int middle = 0;
	if (start>=end) return;
	middle = (start+end) >> 1;
	merge_sort(data, start, middle);
	merge_sort(data, middle+1, end);
	merge(data, start, middle, end);
}

int main(int argc, char** argv){
    printf("Before merge sort:\n");
    dump_array(A);
    
    merge_sort(A, 0, 8);
    
    printf("After merge sort:\n");
    dump_array(A);
    return 0;
    //return test_merge();
 }
