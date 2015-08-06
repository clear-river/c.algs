#ifndef B_TREE
#define B_TREE

#include "./bt_node.h"
class b_tree{
    public:
    bt_node* root;
    uint min_dgr;

    b_tree (uint t){
        root = new bt_node(t);
        root->capacity = 0;
        root->size = 0;
	root->min_dgr = t;
    }

    ~b_tree (){
        destroy (root);
    }

    private:
    void destroy (bt_node* n){
        if (n == NULL) {return;}
        if (n->leaf) {delete n; return;}
        for (uint i = 0; i <= n->size; i++){
            destroy (n->children[i]);
        }
        delete n;
        return;
    }
};

#endif
