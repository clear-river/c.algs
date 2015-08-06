#ifndef BT_NODE
#define BT_NODE
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

typedef unsigned int uint;

class bt_node{
    public:
    uint min_degree, capacity, size;
    int* keys;
    uint leaf;
    bt_node ** children;

    bt_node(uint t):leaf(1), children(NULL), size(0){
        capacity = (t>>1) -1;
        min_degree = t;
        keys = (int*) malloc (capacity * sizeof (int));
    }

    ~bt_node (){
        if (keys) {free (keys);}
        if (children) {free (children);}
    }
};

#endif
