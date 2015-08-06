#include <assert.h>

void merge_sort(int *data, int start, int end);

void merge (int* data, int s, int m, int e){
    int *b = NULL;
    int f = s, l = m+1, bp = s;
    b = (int*) malloc ((e+1)*sizeof(int));
    while (f<m+1 && l<e+1){
	b[bp++] = (data[f]<data[l])?data[f++]:data[l++];
    }
    while (f<m+1){
	b[bp++] = data[f++];
    }
    while (l<e+1){
	b[bp++] = data[l++];
    }
    for (bp = s;bp<=e; bp++){
	data[bp] = b[bp];
    }
    free (b);
}

void merge_sort (int* d, int s, int e){
    int m = 0;
    if (s>=e) {return;}
    m = (s+e) >> 1;
    merge_sort (d, s, m);
    merge_sort (d, m+1, e);
    merge (d, s, m, e);
}
