#include "./b_tree.h"
#include <queue>
#include <math.h>
#include <memory.h>

void attach_node (bt_node* node, std::queue<bt_node*> & node_queue){
    if (node_queue.empty()) {return;}
    bt_node* parent = node_queue.front();
    if (parent->leaf){
        parent->leaf = 0;
        parent->children = (bt_node**) malloc ((parent->capacity + 1) * sizeof (bt_node*));
        memset (parent->children, 0, (parent->capacity + 1) * sizeof (bt_node*));
    }
    for (_uint i = 0; i <= parent->size; i++){
        if (parent->children[i] != NULL) {continue;}
        parent->children[i] = node;
        if (i == parent->size) {
            node_queue.pop();
        }
        break;
    }
}

void init_234_tree (b_tree* tr){
    _uint height = 2, degree = 4, h = 2;
    std::queue <bt_node*> nq;
    for (h = height; h >= 0; h--){
        for (_uint node_n = 0; node_n < (_uint) pow (degree, height-h); node_n++){
            bt_node* node = new bt_node (2);
            if (tr->root == NULL) {tr->root = node;}
            node->size = node->capacity;
            for (_uint key_i = 0; key_i < node->capacity; key_i ++){
                node->keys[key_i] = (_uint) pow (degree, h) * (degree * node_n + key_i + 1) - 1;
                //node->keys[key_i] = (node->keys[key_i]) << 1;
            }
            attach_node (node, nq);
            nq.push (node);
        }
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
