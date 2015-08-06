#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "./queue.h"

int main(int argc, char* argv[]){
	
    queue *my_que = NULL;
    try{
    	my_que = new queue(4);
    }catch (const std::runtime_error &e){
    	std::cerr << e.what() << std::endl;
    	return 1;
    }
    int res = 0, temp;
    int i = 0;
    for (; i<4; i++){
	res = my_que->enqueue(i+1);
	printf("enqueue:%d, res:%d\n", i+1, res);
	//my_que->dump_queue();
    }

    queue *my_que2 = new queue(*my_que);
    delete my_que;

    for(i = 0; i < 4; i++){
	res = my_que2->dequeue(temp);
	printf("dequeue:%d, res:%d\n", temp, res);
	//my_que->dump_queue();
    }
    
    delete(my_que2);
    return 0;
}
