#include <stdexcept>

class queue{
    private:
    int* buffer;
    unsigned int size, head, tail;

    public:
    queue(unsigned int n):head(0), tail(0){
	if(n==0) return;
	size = n;
	buffer = (int*) malloc (n*sizeof(int));
	if (NULL == buffer)
	    throw std::bad_alloc();
    }

    ~queue(){
	if (NULL != buffer){
	    free(buffer);
	    buffer = NULL;
	}
    }

    queue (const queue &q2){
	head = q2.head;
	tail = q2.tail;
	size = q2.size;
	buffer = (int*) malloc (size*sizeof(int));
	if (NULL == buffer)
	    throw std::bad_alloc();
	for(unsigned int i = 0; i< size; i++)
	    buffer[i] = q2.buffer[i];
    }

    int is_full(){
	return (head == (tail+1)%size);
    }
    
    int is_empty(){
	return head == tail;
    }

    int enqueue(int elem){
	if(is_full())
	    return 1;
	buffer[tail] = elem;
	tail = (tail+1)%size;
	return 0;
    }

    int dequeue(int *elem){
	if(is_empty())
	    return 1;
	*elem = buffer[head];
	head = (head+1)%size;
	return 0;
    }
};
