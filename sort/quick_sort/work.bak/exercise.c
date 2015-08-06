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

#include "./algorithm.h"

int main(int argc, char** argv){
    int a[6] = {13, 19, 9, 5, 12, 16};

    dump_array(a, 6);
    quick_sort(a, 0, 5);
    dump_array(a, 6);
    return 0;
}
