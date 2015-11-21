#include "./b_tree.h"
#include <queue>
#include <math.h>
#include <memory.h>

void attach_node (bt_node* node, std::queue<bt_node *> &_queue);

void init_234_tree (b_tree* t){
    bt_node* temp = NULL;
    std::queue<bt_node*> nq;
    int dgr = 4, th = 2;
    for (int nh = 2; nh >= 0; nh --){
	for (int ni = 0; ni < (int) pow (dgr, th-nh); ni++){
	    temp = new bt_node (2);
	    if (t->root == NULL) {t->root = temp;}
	    temp->size = temp->capacity;
	    for (int ki = 0; ki < 3; ki ++){
		temp->keys[ki] = (ki + ni*dgr + 1)*(int) pow (dgr, nh) - 1;
	    }
	    attach_node (temp, nq);
	    nq.push(temp);
	}
    }
}

void attach_node (bt_node* node, std::queue<bt_node*> &_queue){
    if (_queue.empty()) {return;}
    bt_node* prt = _queue.front();
    if (prt->leaf) {
	prt->leaf = 0;
	prt->children = (bt_node**) malloc ((prt->capacity+1) * sizeof(bt_node*));
	memset (prt->children, 0, (prt->capacity+1) * sizeof(bt_node*));
    }
    int i = 0;
    for (i = 0; i<= prt->capacity; i++){
	if (!prt->children[i]){
	    prt->children[i] = node;
	    break;
	}
    }
    if (i == prt->capacity){
	_queue.pop();
    }
}

int main(int argc, char* argv[]){
    b_tree *tree = new b_tree(2);
    bt_node* target = NULL;
    init_234_tree (tree);
    tree->dump_tree();
    delete tree;
    exit (0);

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
