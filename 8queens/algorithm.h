#ifndef _ALGORITHM
#define _ALGORITHM
#include <stdio.h>

int validate (int row, int col){//, int* grid[], int SCALE){
    int target_row, target_col;
    for (target_row=0; target_row < row; target_row++){
	target_col=0;
	while(grid[target_row][target_col] == 0){
	    //break;
	    target_col++;
	}
	if (target_col == col) {return 0;}
	if ((col - row == target_col - target_row) || (col + row == target_col + target_row)) {
	    return 0;
	}
    }
    return 1;
}

void put_queen (int row){
    int col = 0;
    if (row == SCALE){
	output();
	//exit(0);
	return;
    }
    for (col=0; col < SCALE; col++){
	if (validate (row, col)){
	    grid[row][col] = 1;
	    //printf("%d, %d marked.\n", row, col);
	    put_queen(row+1);
	    grid[row][col] = 0;
	    //printf("%d, %d reseted.\n", row, col);
	}
    }
}

#endif
