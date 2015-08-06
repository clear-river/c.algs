#include <stdexcept>
class queue{
    private:
    typedef unsigned int uint;
    int *b;
    uint s, h, t;

    public:
    queue (uint size = 0):b(NULL), h(0), t(0){
	s = size;
	if (!size) {
	    return;
	}
	b = (int*) malloc (s*sizeof(int));
	if (NULL == b){
	    throw std::bad_alloc();
	}
    }

    queue (const queue &q){
	if (q.s == 0){
	    s = h = t = 0;
	    b = NULL;
	    return;
	}
	s = q.s;
	b = (int*) malloc (s*sizeof(int));
	if (b == NULL){
	    throw std::bad_alloc();
	}
	h = q.h; t = q.t;
	for (uint i = h; i!= t; i = (i+1)%s){
	    b[i] = q.b[i];
	}
    }

    ~queue (){
	if (b) {
	    free (b);
	}
    }

    int is_full(){
	return ((t+1)%s) == h;
    }

    int is_empty(){
	return t == h;
    }

    int enqueue (const int e){
	if (is_full()){
	    return 1;
	}
	t = (t+1)%s;
	b[t] = e;
	return 0;
    }

    int dequeue (int &e){
	if (is_empty()){
	    return 1;
	}
	e = b[h];
	h = (h+1)%s;
	return 0;
    }
};
