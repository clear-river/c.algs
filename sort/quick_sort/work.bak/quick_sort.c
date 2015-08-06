#include <stdio.h>
#include <stdlib.h>

void dump_array(int *data, int size){
    int i = 0;
    for (;i<size; i++){
	printf("%d,", data[i]);
    }
    printf("\n");
    return;
}

int seperate(int* data, int start, int end){
    int pos = start, temp = 0, curr = start + 1;
    for(; curr<=end; curr++){
	if(data[curr] > data[start]){
	    continue;
	}
	temp = data[++pos];
	data[pos] = data[curr];
	data[curr] = temp;
    }
    temp = data[start];
    data[start] = data[pos];
    data[pos] = temp;
    return pos;
}

void quick_sort(int *data, int start, int end){
    int sep = 0;
    if (start >= end) return;
    sep = seperate(data, start, end);
    quick_sort(data, start, sep - 1);
    quick_sort(data, sep + 1, end);
    return;
}

int main(int argc, char** argv){
    int a[6] = {13, 19, 9, 5, 12, 16};

    dump_array(a, 6);
    quick_sort(a, 0, 5);
    dump_array(a, 6);
    return 0;
}
