#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

/*void add_child(int v, int side){
bt_node *temp = new bt_node();
temp->value = v;
temp->parent = this;
if(!side)
    left = temp;
else
    right = temp;
}*/

class bt_node{
    public:
    int v;
    bt_node *p, *l, *r;

    bt_node(const int value = 0):
	    p(NULL),l(NULL),r(NULL){
	v = value;
    }

    bt_node(const bt_node &node):
	    p(NULL), l(NULL), r(NULL){
	v = node.v;
    }
void add_child(int v, int side){
bt_node *temp = new bt_node();
temp->v = v;
temp->p = this;
if(!side)
    l = temp;
else
    r = temp;
}
};

class btree{
    public:
    bt_node *root;
    btree(bt_node* t = NULL){
	root = t;
    }
    btree(const btree &t){
	copy(NULL, t.root, root);
    }
    ~btree(){
	destroy(root);
    }
    void pre_order(){
	_pre_order(root);
    }
    void mid_order(){
	_mid_order(root);
    }
    void left_rotate (bt_node *node){
	if (!node) {return;}
	bt_node* rChild = node->r;
	if (!rChild) {return;}
	node->r = rChild->l;
	if (rChild->l){
	    rChild->l->p = node;
	}
	rChild->p = node->p;
	if (!node->p){
	    root = rChild;
	}else{
	    if (node == node->p->l){
		node->p->l = rChild;
	    }else{
		node->p->r = rChild;
	    }
	}
	rChild->l = node;
	node->p = rChild;
    }
    void right_rotate (bt_node *node) {
	if (!node) {return;}
	bt_node *lChild = node->l;
	if (!lChild) {return;}
	node->l = lChild->r;
	if (!lChild->r) {
	    lChild->r->p = node;
	}
	lChild->p = node->p;
	if (!node->p){
	    root = lChild;
	}else{
	    if(node == node->p->l){
		node->p->l = lChild;
	    }else{
		node->p->r = lChild;
	    }
	}
	lChild->r = node;
	node->p = lChild;
    }
    private:
    void copy (bt_node * cur_p, const bt_node* src, bt_node * &dst){
	if (!src) {dst = NULL; return;}
	dst = new bt_node(*src);
	dst->p = cur_p;
	copy (dst, src->l, dst->l);
	copy (dst, src->r, dst->r);
    }

    void destroy (bt_node *node){
	if (!node) {return;}
	destroy (node->l);
	destroy (node->r);
	delete node;
    }

    void _pre_order (bt_node* node){
	if (!node) {return;}
	printf("%d,", node->v);
	_pre_order(node->l);
	_pre_order(node->r);
    }

    void _mid_order (bt_node *node){
	if(!node) {return;}
	_mid_order(node->l);
	printf("%d,", node->v);
	_mid_order(node->r);
    }
};
