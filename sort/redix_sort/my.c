#include <stdio.h>
#include <stdlib.h>

int get_elem(int **a, int col, int i, int j){
	return (int)(((int*)a)[i*col+j]);
}

void dump_matrix(int **a, int row, int col){
	int i=0, j=0;
	for(;i<row; i++){
		for(j=0;j<col;j++)
			printf("%d,", get_elem(a, col, i, j));
		printf("\n");
	}
	return;
}

void dump_array(int *a, int n){
	int i = 0;
	for(; i<n; i++)
		printf("%d,", a[i]);
	printf("\n");
	return;
}

void sort(int **a, int row, int col,
		int *b, int range){
	int **temp = 0; int *temp_address = 0;
	int i=0, j=0, k=0;
	
	temp = (int **) malloc(sizeof(int*)*row);
	for(i=0; i<row; i++)
		temp[i] = (int*) malloc(sizeof(int)*col);
	
	for(j=row-1; j>=0; j--){
		for(i=0; i<range; i++)
			b[i] = 0;
		for(i=0; i<col; i++){
			//printf("a[%d][%d] = %d\n", j, i, get_elem(a, col, j, i));
			b[get_elem(a, col, j, i)] ++;
		}
		//dump_array(b, range);
		for(i=1; i<range; i++)
			b[i] += b[i-1];
		dump_array(b, range);
		dump_matrix(a, row, col);
		printf("to dump temp:\n");
		for(i=col-1; i>=0; i--){
			for(k=0; k<row; k++){
				temp[k][b[get_elem(a, col, j, i)]-1] = get_elem(a, col, k, i);
				//temp[k][i] = get_elem(a, col, k, b[get_elem(a, col, j, i)-1]);
				dump_array(temp[k], col);
			}
			b[get_elem(a, col, j, i)] --;
			printf("\n");
		}
		printf("temp dumping complete.\n");
		for (i=0; i<col; i++)
			for(k=0; k<row; k++){
				temp_address = ((int*)a+k*col+i);
				*temp_address = temp[k][i];
				printf("temp[%d][%d] = %d cp to a+%d(%x)\n", k, i, temp[k][i], k*col+i, a+k*col+i);
				dump_matrix(a, row, col);
			}
		/*3,4,6,8,4,7,3,
		2,5,5,3,3,2,5,
		9,7,7,9,6,0,5,*/
		printf("\n");
	}
	
	for(i=0; i<row; i++)
		free(temp[i]);
	free(temp);
}

int main(int argc, char* argv[]){
	int card[3][7] = {
		{3,4,6,8,4,7,3},
		{2,5,5,3,3,2,5},
		{9,7,7,9,6,0,5}
	};
	int b[10] = {0};
	dump_matrix((int**)card, 3, 7);
	printf("\n");
	sort((int**)card, 3, 7, b, 10);
	dump_matrix((int**)card, 3, 7);
	return 0;
}
