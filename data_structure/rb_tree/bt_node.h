#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

class bt_node{
    public:
    enum color {red, black};
    color c;
    int v;
    bt_node *p, *l, *r;

    bt_node (const int val = 0, const color cl = black):p(NULL), l(NULL), r(NULL){
	v = val;
	c = cl;
    }

    bt_node (const bt_node &n):p(NULL), l(NULL), r(NULL){
	v = n.v;
	c = n.c;
    }
};
