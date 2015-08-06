//biSearch
int biSearch (int* d, int *h, int s, int e, int t){
    int m = 0;
    if (s>e) {*h = -1; return e;}
    m = (s+e) >> 1;
    if (d[m] == t){ *h = 0; return m;}
    return (d[m] < t)? biSearch (d, h, m+1, e, t): biSearch (d, h, s, m-1, t);
}

