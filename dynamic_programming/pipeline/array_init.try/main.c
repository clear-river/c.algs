#include <stdio.h>
#include <stdlib.h>

#include "./array.h"

int main(int argc, char* argv[]){
    array a = array();
    for (int i = 0; i< 5; i++){
	printf ("%d,", a.arr[i]);
    }
    printf ("\n");
    return 0;
}
