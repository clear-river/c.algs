#include <stdlib.h>
void sort(int *data, int n, int ceiling);

void sort(int *d, int n, int t){
    int *b = (int*) malloc (n*sizeof(int));
    int *c = (int*) malloc ((t+1)*sizeof(int));
    int i = 0;
    if(!b || !c) {printf("malloc error.\n"); exit(1);}
    for (i=0; i<=t; i++) {c[i] = 0;}
    for (i=0; i<n; i++) {c[d[i]] ++;}
    for (i=1; i<=t; i++) {c[i] += c[i-1];}
    for (i=n-1; i>=0; i--) {b[--c[d[i]]] = d[i];}
    free (c);
    for (i=0; i<n; i++) {d[i] = b[i];}
    free (b);
}
