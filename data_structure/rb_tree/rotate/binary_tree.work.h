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
    //private:
    public:
    bt_node *root;

    void destroy(bt_node *nodep){
	if(NULL == nodep) return;
	destroy(nodep->l);
	destroy(nodep->r);

	bt_node* p = nodep->p;
	if(NULL == p){
	    delete nodep;
	    return;
	}
	if(nodep == p->l)
	    p->l = NULL;
	else if(nodep == p->r)
	    p->r = NULL;
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

    void left_rotate (bt_node* node){
        if (NULL == node){
            return;
        }
        bt_node * rChild = node->r;
        if (NULL == rChild){
            return;
        }
        node->r = rChild->l;
        if (rChild->l != NULL){
            rChild->l->p = node;
        }
        rChild->p = node->p;
        if (NULL == node->p){
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
        return;
    }

    void right_rotate (bt_node *node){
        if (NULL == node) {return;}
        bt_node * lChild = node->l;
        if (NULL == lChild) {return;}
        node->l = lChild->r;
        if (NULL != lChild->r) {
            lChild->r->p = node;
        }
        lChild->p = node->p;
        if (NULL == node->p){
            root = lChild;
        }else{
            if (node == node->p->l){
                node->p->l = lChild;
            }else{
                node->p->r = lChild;
            }
        }
        lChild->r = node;
        node->p = lChild;
        return;
    }
};

