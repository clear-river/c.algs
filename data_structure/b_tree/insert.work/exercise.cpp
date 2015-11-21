#include "./b_tree.h"
#include <queue>
#include <math.h>
#include <memory.h>

void attach_node (bt_node*, std::queue<bt_node*> &);

void init_tree (b_tree *r){
    std::queue<bt_node*> nq;
    int th=2, dgr=4; bt_node* new_n = NULL;
    for (int nh=2; nh>=0; nh--){
	for (int ni=0; ni<(int) pow (dgr, th-nh); ni++){
	    new_n = new bt_node(2);
	    if (r->root == NULL) {r->root = new_n;}
	    for (int ki=0; ki<dgr; ki++){
		new_n->keys[ki] = (int) pow (dgr, nh) * (ni*dgr+ki+1) - 1;
		new_n->keys[ki] = new_n->keys[ki] << 1;
	    }
	    new_n->size = new_n->capacity;
	    attach_node( new_n, nq);
	    nq.push(new_n);
	}
    }
}

void attach_node(bt_node* n, std::queue<bt_node*> &_queue){
    if (_queue.empty()) {return;}
    bt_node* prt = _queue.front();
    if (prt->leaf){
	prt->leaf = 0;
	prt->children = (bt_node**) malloc ((prt->capacity + 1) * sizeof (bt_node*));
	memset (prt->children, 0, (prt->capacity+1)*sizeof(bt_node*));
    }
    for (int i = 0; i<=prt->size; i++){
	if (prt->children[i]) {continue;}
	prt->children[i] = n;
	if (i == prt->size){
	    _queue.pop();
	}
	break;
    }
}

int main(int argc, char* argv[]){
    b_tree *tree = new b_tree(2);
    bt_node* target = NULL;
    init_tree (tree);
    tree->dump_tree();

    _uint i = 0;
    target = tree->search(26, &i);
    if (target){
	printf("%u found at node %u with index %u\n", 26, target->keys[0], i);
	//tree->_dump_tree(target, 0);
    }
    target = tree->search(29, &i);
    if (target){
	printf("%u found at node %u with index %u\n", 29, target->keys[0], i);
	//tree->_dump_tree(target, 0);
    }else{
	printf("%u not found.\n", 29);
    }

    /*target = tree->root->children[0];
    tree->destroy (target->children[2]);
    target->keys[1] = target->keys[2];
    target->children[2] = target->children[3];
    target->size--;
    tree->dump_tree();
    printf ("==========================split node 4.\n");
    tree->split (target, 1);
    printf ("==========================split node 4 done.\n");
    tree->dump_tree();*/

    printf("41 insertion started.\n");
    tree->insert(41);
    printf("41 insertion complete.\n");
    tree->dump_tree();
    delete tree;
}
