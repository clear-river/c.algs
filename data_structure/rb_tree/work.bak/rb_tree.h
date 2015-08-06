#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include "./bt_node.h"

class rb_tree {
    public:
    bt_node *root;
    private:
    bt_node *nil;

    public:
    rb_tree (const rb_tree *t = NULL){
	nil = new bt_node();
	if (t == NULL){
	    root = nil; return;
	}
	_copy(nil, root, t->root, t->nil);
    }

    ~rb_tree (){
	if (root != nil){
	    _destroy (root);
	}
	delete nil;
    }

    void mid_order (){
	_mid_order (root);
    }
    void pre_order (){
	_pre_order (root);
    }

    bt_node* minimum (bt_node* n){ 
        if (n == nil) {return NULL;}
        while (n->l != nil){
            n = n->l;
        }   
        return n;
    }   

    bt_node* successor (bt_node* n){ 
        if (n == nil) {return NULL;}
        if (n->r != nil) {return minimum (n->r);}
        bt_node* prt = n->p;
        while (prt != nil && n == prt->r){
            n = prt;
            prt = n->p;
        }   
        return (prt == nil)?NULL:prt;
    }
   
    void insert (const bt_node &n){
	bt_node *temp = new bt_node (n.v, bt_node::red);
	bt_node *prt = nil, *crt = root;
	while (crt != nil){
	    prt = crt;
	    crt = (temp->v < crt->v)?crt->l:crt->r;
	}
	if (prt == nil){
	    root = temp;
	}else{
	    if (temp->v < prt->v){
		prt->l = temp;
	    }else{
		prt->r = temp;
	    }
	}
	temp->p = prt;
	temp->l = temp->r = nil;
	insert_fixup(temp);
    }

    bt_node* find (int v){
	bt_node* result = root;
	while (result != nil && result->v != v){
	    result = (v < result->v)? result->l:result->r;
	}
	return (result == nil)?NULL:result;
    }

    void remove (bt_node* n){
	if (n == nil || n == NULL) {return;}
	bt_node *n2d = n, *ch = nil;
	if (n->l != nil && n->r != nil){
	    n2d = successor (n);
	}
	ch = (n2d->l != nil)? n2d->l:n2d->r;
	if (n2d->p == nil){
	    root = ch;
	}else{
	    if (n2d== n2d->p->l){
		n2d->p->l = ch;
	    }else{
		n2d->p->r = ch;
	    }
	}
	ch->p = n2d->p;
	if (n != n2d){
	    n->v = n2d->v;
	}
	if (n2d->c == bt_node::black){
	    remove_fixup (ch);
	}
	delete n2d;
    }

    private:
    void _copy (bt_node* prt, bt_node* &crt, const bt_node* t_r, const bt_node* t_n){
	if (t_r == t_n){
	    crt = nil; return;
	}
	crt = new bt_node (*t_r);
	crt->p = prt;
	_copy (crt, crt->l, t_r->l, t_n);
	_copy (crt, crt->r, t_r->r, t_n);
    }

    void _destroy (bt_node* crt){
	if (crt == nil) {return;}
	_destroy (crt->l);
	_destroy (crt->r);
	delete crt;
    }

    void _mid_order (const bt_node *n){
	if (n == nil) {return;}
	_mid_order(n->l);
	printf ("%d[%s],", n->v, (n->c == bt_node::red?"red":"black"));
	_mid_order (n->r);
    }

    void _pre_order (const bt_node* n){
	if (n == nil) {return;}
	printf ("%d[%s],", n->v, (n->c == bt_node::red)? "red" :"black");
	_pre_order (n->l);
	_pre_order (n->r);
    }

    void remove_fixup (bt_node* node){
	bt_node * bro;
	while (node != root && node->c == bt_node::black){
	    if (node == node->p->l){
		bro = node->p->r;
		if (bro->c == bt_node::red){
		    bro->c = bt_node::black;
		    node->p->c = bt_node::red;
		    left_rotate (node->p);
		    bro = node->p->r;
		}
		if (bro->l->c == bt_node::black && bro->r->c == bt_node::black){
		    bro->c = bt_node::red;
		    node = node->p;
		    continue;
		}
		if (bro->r->c == bt_node::black){
		    bro->c = bt_node::red;
		    bro->l->c = bt_node::black;
		    right_rotate (bro);
		    bro = node->p->r;
		}
		bro->c = node->p->c;
		node->p->c = bro->r->c = bt_node::black;
		left_rotate (node->p);
		node = root;
	    }else{ // node == node->p->r
		bro = node->p->l;
		if (bro->c == bt_node::red){
		    bro->c = bt_node::black;
		    node->p->c = bt_node::red;
		    right_rotate (node->p);
		    bro = node->p->l;
		}
		if (bro->l->c == bt_node::black && bro->r->c == bt_node::black){
		    bro->c = bt_node::red;
		    node = node->p;
		    continue;
		}
		if (bro->l->c == bt_node::black){
		    bro->c = bt_node::red;
		    bro->r->c = bt_node::black;
		    left_rotate (bro);
		    bro = node->p->l;
		}
		bro->c = node->p->c;
		node->p->c = bro->l->c = bt_node::black;
		right_rotate (node->p);
		node = root;
	    }// end if 
	}//while
	node->c = bt_node::black;
    }

    void left_rotate (bt_node* node){
        bt_node* rch = node->r;
        node->r = rch->l;
        if (rch->l != nil){
            rch->l->p = node;
        }
        rch->p = node->p;
        if (node->p == nil){
            root = rch;
        }else{
            if (node == node->p->l){
                node->p->l = rch;
            }else{
                node->p->r = rch;
            }
        }
        node->p = rch;
        rch->l = node;
    }

    void right_rotate (bt_node* node){
        bt_node* lch = node->l;
        node->l = lch->r;
        if (lch->r != nil){
            lch->r->p = node;
        }
        lch->p = node->p;
        if (node->p == nil){
            root = lch;
        }else{
            if (node == node->p->l){
                node->p->l = lch;
            }else{
                node->p->r = lch;
            }
        }
        lch->r = node;
        node->p = lch;
    }

    void insert_fixup (bt_node* n){
	while (n->p->c == bt_node::red){
	    bt_node* uncle;
	    if (n->p == n->p->p->l){
		uncle = n->p->p->r;
		if (uncle->c == bt_node::red){
		    n->p->c = uncle->c = bt_node::black;
		    n->p->p->c = bt_node::red;
		    n = n->p->p; continue;
		}
		if (n == n->p->r){
		    n = n->p;
		    left_rotate(n);
		}
		n->p->c = bt_node::black;
		n->p->p->c = bt_node::red;
		right_rotate (n->p->p);
	    }else{ //n->p == n->p->p->r
		uncle = n->p->p->l;
		if (uncle->c == bt_node::red){
		    n->p->c = uncle->c = bt_node::black;
		    n->p->p->c = bt_node::red;
		    n = n->p->p; continue;
		}
		if (n == n->p->l){
		    n = n->p;
		    right_rotate(n);
		}
		n->p->c = bt_node::black;
		n->p->p->c = bt_node::red;
		left_rotate (n->p->p);
	    }//endif
	}//while
	root->c = bt_node::black;
    }
};
