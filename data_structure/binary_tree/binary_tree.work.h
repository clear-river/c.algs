#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

class bt_node{
    public:
    int v;
    bt_node *l, *r, *p;

    bt_node():v(0), l(NULL), r(NULL), p(NULL){}
    bt_node(const bt_node &node):l(NULL), r(NULL), p(NULL){
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
    private:
    bt_node *root;

    void destroy(bt_node *nodep){
	if(NULL == nodep) return;
	destroy(nodep->l);
	destroy(nodep->r);

	bt_node* parent = nodep->p;
	if(NULL == parent){
	    delete nodep;
	    return;
	}
	if(nodep == parent->l)
	    parent->l = NULL;
	else if(nodep == parent->r)
	    parent->r = NULL;
	else
	    throw std::runtime_error("left or right pointer mismatch with parent");
	delete nodep;
	return;
    }

    void copy(bt_node *curr_p, bt_node* &dst, bt_node *src){
	if(NULL == src){
	    dst = NULL; return;
	}
	dst = new bt_node(*src);
	dst->p = curr_p;
	copy(dst, dst->l, src->l);
	copy(dst, dst->r, src->r);
	return;
    }

    void _pre_order(bt_node *node){
	if(NULL == node) return;
	printf("%d,", node->v);
	_pre_order(node->l);
	_pre_order(node->r);
    }

    void _mid_order(bt_node* node){
	if(NULL == node) return;
	_mid_order(node->l);
	printf("%d,", node->v);
	_mid_order(node->r);
    }

    public:
    btree():root(NULL){}
    btree(bt_node* const p){
	root = p;
    }
    btree(const btree &t){
	copy(NULL, root, t.root);
    }
    ~btree(){
	destroy(root);
	root = NULL;
    }
    void  pre_order(){
	_pre_order(root);
    }
    void mid_order(){
	_mid_order(root);
    }
};

