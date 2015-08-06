#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

class bt_node{
    public:
    int v;
    bt_node *l, *r, *p;
    
    bt_node(int value = 0):l(NULL),r(NULL),p(NULL){
    	v = value;
    }
    
    bt_node(const bt_node &n):l(NULL),r(NULL),p(NULL){
    	v = n.v;
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
	
	public:
	btree():root(NULL){}
	btree (bt_node *node = NULL){
		root = node;
	}
	
	btree (const btree* tp){
		copy (NULL, root, tp->root);
	}
	
	~btree (){
		destroy(root);
	}
	
	void pre_order (bt_node* sub_r = (bt_node*)(1)){
		if (sub_r == (bt_node*)1) sub_r = root;
		if (NULL == sub_r) return;
		printf("%d,", sub_r->v);
		pre_order (sub_r->l);
		pre_order (sub_r->r);
	}
	
	void mid_order (bt_node* sub_r = (bt_node*)(1)){
		if (sub_r == (bt_node*)1) sub_r = root;
		if (NULL == sub_r) return;
		mid_order (sub_r->l);
		printf("%d,", sub_r->v);
		mid_order (sub_r->r);
	}
	
	private:
	void copy (bt_node* sub_p, bt_node* &sub_r, const bt_node* src){
		if (NULL == src){
			sub_r = NULL; return;
		}
		
		sub_r = new bt_node(*src);
		sub_r -> p = sub_p;
		copy (sub_r, sub_r->l, src->l);
		copy (sub_r, sub_r->r, src->r);
	}
	
	void destroy (bt_node *sub_r){
		if (NULL == sub_r) return;
		destroy (sub_r->l);
		destroy (sub_r->r);
		
		bt_node *p = sub_r->p;
		if (p){
			if (sub_r == p->l)
				p->l = NULL;
			else if (sub_r == p->r)
				p->r = NULL;
			else{
				printf("child mismatch with parent\n");
				throw std::runtime_error("mismatch");
			    }
		}
		delete sub_r;
	}
};
