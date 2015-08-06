void heap_sort(int *data, int n);

void hpf (int* d, int n, int i){
    int ch = 0, temp = 0;
    while (2*i+1 < n){
	ch = (2*i+2<n && d[2*i+1]<d[2*i+2])?2*i+2:2*i+1;
	if (d[i]<d[ch]){
	    temp = d[i];d[i] = d[ch];d[ch] = temp;
	}else{
	    return;
	}
	i = ch;
    }
}

void heap_sort (int* d, int n){
    int i = 0, temp = 0;
    for (i=(n<<1)-1; i>=0; i--){
	hpf (d, n, i);
    }
    for (i=n-1; i>0; i--){
	temp = d[0];d[0]=d[i];d[i]=temp;
	hpf (d, i, 0);
    }
}

