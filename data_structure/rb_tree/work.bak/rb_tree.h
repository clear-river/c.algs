#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include "./bt_node.h"

class rb_tree {
    private:
    bt_node* nil;
    public:
    bt_node* root;

    rb_tree (const bt_node* r = NULL){
	nil = new bt_node();
	if (NULL  == r){
	    root = nil;
	    return;
	}
	root = new bt_node (r->v, bt_node::black);
	root->p = root->l = root->r = nil;
    }

    rb_tree (const rb_tree &t){
	nil = new bt_node();
	copy (nil, root, t.root, t.nil);
    }

    ~rb_tree () {
	destroy (root);
	delete nil;
    }

    void pre_order (){
	_pre_order (root);
    }

    void mid_order (){
	_mid_order (root);
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
   
    void insert (const bt_node &node){
        bt_node *temp, *parent = nil, *current = root;
        try{
            temp = new bt_node (node);
        } catch (...) {
            printf ("something error happened.\n");
            exit (1);
        }   
        while (current != nil){
            parent = current;
            current = (temp->v < current->v)? current->l:current->r;
        }   
        if (parent == nil){
            root = temp;
        }else{
            if (temp->v < parent->v){
                parent->l = temp;
            }else{
                parent->r = temp;
            }
        }

        temp->p = parent;
        temp->l = temp->r = nil;
        temp->c = bt_node::red;
        insert_fixup(temp);
    }

    bt_node *find (int v){
        bt_node* n = root;
        while (n != nil && n->v != v){
            n = (v < n->v)? n->l : n->r;
        }
        return (n == nil)? NULL : n;
    }

    void remove (bt_node* n){
        if (n == nil || n == NULL) {return;}
        bt_node *n2d = n, *ch = nil;
        if (n->l != nil && n->r != nil){
            n2d = successor (n);
        }
        ch = (n2d->l == nil)? n2d->r : n2d->l;
        if (n2d->p == nil){
            root = ch;
        }else{
            if (n2d == n2d->p->l){
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
    void copy (bt_node* prt, bt_node* &crt, const bt_node *src, const bt_node* snil){
	if (src == snil){
	    crt = nil;
	    return;
	}
	crt = new bt_node (*src);
	crt->p = prt;
	copy (crt, crt->l, src->l, snil);
	copy (crt, crt->r, src->r, snil);
    }

    void destroy (bt_node* n){
	if (n == nil) {return;}
	destroy (n->l);
	destroy (n->r);
	delete n;
    }

    void _pre_order (const bt_node* n){
	if (n == nil) {return;}
	printf ("%d[%s],", n->v, (n->c == bt_node::red)? "red" :"black");
	_pre_order (n->l);
	_pre_order (n->r);
    }

    void _mid_order (const bt_node* n){
	if (n == nil) {return;}
	_mid_order (n->l);
	printf ("%d[%s],", n->v, (n->c == bt_node::red)? "red": "black");
	_mid_order (n->r);
    }

    void remove_fixup (bt_node* node){
        while (node != root && node->c == bt_node::black){
            bt_node * bro = nil;
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
                    node = node->p; continue;
                }
                if (bro->r->c == bt_node::black){
                    bro->l->c = bt_node::black;
                    bro->c = bt_node::red;
                    right_rotate (bro);
                    bro = node->p->r;
                }
                bro->c = node->p->c;
                node->p->c = bro->r->c = bt_node::black;
                left_rotate (node->p);
                node = root;
            } else {//if (node == node->p->l)
                bro = node->p->l;
                if (bro->c == bt_node::red){
                    bro->c = bt_node::black;
                    node->p->c = bt_node::red;
                    right_rotate(node->p);
                    bro = node->p->l;
                }
                if (bro->l->c == bt_node::black && bro->r->c == bt_node::black){
                    bro->c = bt_node::red;
                    node = node->p; continue;
                }
                if (bro->l->c == bt_node::black){
                    bro->r->c = bt_node::black;
                    bro->c = bt_node::red;
                    left_rotate (bro);
                    bro = node->p->l;
                }
                bro->c = node->p->c;
                node->p->c = bro->l->c = bt_node::black;
                right_rotate (node->p);
                node = root;
            } //else
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
            bt_node* u = nil;
            if (n->p == n->p->p->l){
                u = n->p->p->r;
                if (u->c == bt_node::red){
                    u->c = n->p->c = bt_node::black;
                    n->p->p->c = bt_node::red;
                    n = n->p->p; continue;
                }
                if (n == n->p->r){
                    n = n->p;
                    left_rotate (n);
                }
                n->p->c = bt_node::black;
                n->p->p->c = bt_node::red;
                right_rotate (n->p->p);
            } else {
                u = n->p->p->l;
                if (u->c == bt_node::red){
                    u->c = n->p->c = bt_node::black;
                    n->p->p->c = bt_node::red;
                    n = n->p->p; continue;
                }
                if (n == n->p->l) {
                    n = n->p;
                    right_rotate (n);
                }
                n->p->c = bt_node::black;
                n->p->p->c = bt_node::red;
                left_rotate (n->p->p);
            }
        }
        root->c = bt_node::black;
    }
};
