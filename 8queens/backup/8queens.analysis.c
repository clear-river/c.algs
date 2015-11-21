#include<stdio.h>
#include<math.h>

#define N 4

#define SET 10
#define RESET 11
#define CHECK 12
#define CHECK_AGAINST 13

int Grid[N][N];

void LogAction(int act, int row, int col){
	switch (act){
		case SET:
			printf("set ");
			break;
		case RESET:
			printf("reset ");
			break;
		case CHECK:
			printf("check ");
			break;
		case CHECK_AGAINST:
			printf("check against ");
			break;
		default:
			printf("unknown action:%d", act);
	}
	printf("(%d, %d)", row, col);
	printf("\n");
	return;
}

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
	LogAction(CHECK, row, col);
	for(checked_row=0;checked_row<row;checked_row++)
	{
		int checked_col = 0;
		while(Grid[checked_row][checked_col] != 1){
			checked_col++;
		}
		
		LogAction(CHECK_AGAINST, checked_row, checked_col);
		if(checked_col == col){
			printf("col collision\n");
			return 0;
		}

		if((col-checked_col) == (row-checked_row)||
				(col-checked_col) == (checked_row-row)){
			printf("diag collision\n");
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
		//return;
	}

	for(col=0;col<N;col++){
		Grid[row][col] = 1;
		LogAction(SET, row, col);
		
		if(Validate(row,col)){
			//Try the next row in case of a successful validation.
			//There won't be 2 queens stay at the same row.
			Queen(row+1);
		}
		
		Grid[row][col] = 0;//clear the queen when roll back
		LogAction(RESET, row, col);
	}
}

int main(void)
{
	//OutPut();
	Queen(0);
	return 0;
}