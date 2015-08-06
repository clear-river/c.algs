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

#include "./algorithm.h"

int main(int argc, char** argv){
    printf("Before merge sort:\n");
    dump_array(A);
    
    merge_sort(A, 0, 8);
    
    printf("After merge sort:\n");
    dump_array(A);
    return 0;
    //return test_merge();
 }
