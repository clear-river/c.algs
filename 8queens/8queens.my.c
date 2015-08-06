#include <stdio.h>

#define SCALE 8
int grid[SCALE][SCALE];

void output(){
	int row = 0, col = 0;
	for (row = 0; row < SCALE; row ++){
		for(col = 0; col < SCALE; col ++){
			printf ("%d ", grid[row][col]);
		}
		printf ("\n");
	}
}

int validate(int row, int col){
	int target_row = 0, target_col=0;
	for(;target_row < row; target_row++){
		target_col=0;
		while(grid[target_row][target_col] == 0)
			target_col ++;
		if (col == target_col) return 0;
		if ((col - target_col == row - target_row) ||
				(col - target_col == target_row - row)){
			return 0;
		}
	}
	return 1;
}
void put_queen(int row){
	int col=0;
	
	if (row == SCALE){
		output();
		exit(0);
		return;
	}
	
	for (col = 0; col < SCALE; col++){
		grid[row][col] = 1;
		if(validate(row, col)){
			put_queen(row+1);
		}
		grid[row][col] = 0;
	}
}


int main(int argc, char** argv){
	put_queen(0);
	return 0;
}
