#include<stdio.h>
#include<math.h>

#define N 8
int Grid[N][N];

void OutPut()
{
	static int count = 1;
	int i=0;
	printf("Router %d:\n",count++);
	for(i=0;i<N;i++)
	{
		int j=0;
		for(j=0;j<N;j++)
		{
			printf("%d ",Grid[i][j]);
		}
		printf("\n");
	}
}

int Validate(int row,int col)
{
	int checked_row=0;
	for(checked_row=0;checked_row<row;checked_row++)
	{
		int checked_col = 0;
		while(Grid[checked_row][checked_col] != 1){
			checked_col++;
		}
		if(checked_col == col){
			return 0;
		}
		if((col-checked_col) == (row-checked_row)||
				(col-checked_col) == (checked_row-row)){
			return 0;
		}
	}
	return 1;
}

void Queen(int row)
{
	int col;
	if(row == N){
		OutPut();
		exit(0);
		return;
	}
	for(col=0;col<N;col++){
		Grid[row][col] = 1;

		if(Validate(row,col)){
			Queen(row+1);
		}

		Grid[row][col] = 0;
	}
}

int main(void)
{
	Queen(0);
	return 0;
}