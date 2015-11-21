#include <stdio.h>

#define SCALE 8
int grid[SCALE][SCALE];
#include "algorithm.h"

void output(){
    int row = 0, col = 0;
    for (row = 0; row < SCALE; row ++){
        for(col = 0; col < SCALE; col ++){
            printf ("%d ", grid[row][col]);
        }
        printf ("\n");
    }
}

int main(int argc, char** argv){
    put_queen(0);
    return 0;
}
