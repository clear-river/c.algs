void quick_sort(int *d, int s, int e);

int partition (int* d, int s, int e){
    int t=0, p=s, u=s+1;
    for (u = s + 1; u <= e; u ++){
	if (d[u] < d[0]){
	    t = d[++p]; d[p] = d[u]; d[u] = t;
	}
    }
    t = d[s]; d[s] = d[p]; d[p] = t;
    return p;
}

void quick_sort (int *d, int s, int e){
    int p = 0;
    if (s>=e) return;
    p = partition (d, s, e);
    quick_sort (d, s, p-1);
    quick_sort (d, p+1, e);
    return;
}
