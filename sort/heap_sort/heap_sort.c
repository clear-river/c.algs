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

void heapify(int *data, int n, int root){
    int max_child_index = 0, temp = 0;
    while(2*root+1 < n){
	max_child_index=(2*root+2<n && data[2*root+2] > data[2*root+1])?
	    2*root+2: 2*root+1;
	if (data[max_child_index] <= data[root])
	    return;
	temp = data[max_child_index];
	data[max_child_index] = data[root];
	data[root] = temp;
	root = max_child_index;
    }
    return;
}

void create_heap(int *data, int n){
    int curr_root = (n>>1)-1;
    for(; curr_root>=0; curr_root--)
	heapify(data, n, curr_root);
}

void heap_sort(int *data, int n){
    int curr_pos = n-1, temp = 0;
    create_heap(data, n);
    for(;curr_pos>0; curr_pos--){
	temp = data[curr_pos];
	data[curr_pos] = data[0];
	data[0] = temp;
	heapify(data, curr_pos, 0);
    }
}

int main(int argc, char** argv){
	printf("Before heapification:\n");
	dump_a(A, 10);
	//heapify(A, 1, 10);
	heap_sort(A, 10);
	printf("After heapification:\n");
	dump_a(A, 10);
	return 0;
}

