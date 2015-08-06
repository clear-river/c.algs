#include <stdio.h>
#include <stdlib.h>

const int unit_size = 5;

int step_length(int r){
    if (r==0) return 1;
    int result = unit_size;
    for (int i=1; i<r; i++)
	result *= unit_size;
    return result;
}

int start_i (int r, int first){
    int step_len = step_length(r);
    return first+step_len>>1;
}

int count(int r, int first, int last){
    int elem_num = last - first + 1;
    if (r==0) return elem_num;
    int step_len = step_length(r);
    return (elem_num+step_len-1)/step_len;
}

int end_i(int r, int first, int last){
    int elem_num = last-first+1;
    if (r==0) return last;
    if (r==1) return first+ ((elem_num%unit_size)>>1) + elem_num/unit_size*unit_size - 1;
    int elem_count = count(r-1, first, last);
    if ((elem_count % unit_size) == 1)
	return end_i(r-1, first, last);
    return start_i(r-1) + (elem_count>>1) * step_length(r-1);
}
