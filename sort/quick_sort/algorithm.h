void quick_sort(int *d, int s, int e);

int partition (int*d, int s, int e){
    int c = s+1, p = s, temp = 0;
    for(; c<=e; c++){
	if (d[c] < d[s]){
	    temp = d[++p];
	    d[p] = d[c];
	    d[c] = temp;
	}
    }
    temp = d[s];
    d[s] = d[p];
    d[p] = temp;
    return p;
}

void quick_sort (int*d, int s, int e){
    int p = 0;
    if (s>=e) {return;}
    p = partition (d, s, e);
    quick_sort(d, s, p-1);
    quick_sort(d, p+1, e);
}
