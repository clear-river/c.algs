#include "./rb_tree.h"

void finalize_print (){
    putchar(0x08);
    putchar(0x20);
    printf("\n");
}

int main (int argc, char* argv[]){
    bt_node *root = new bt_node(0, bt_node::black);
    int max = 13;

    rb_tree *tree = new rb_tree (root);
    delete root;
    printf ("================================================================================\n");
    tree->pre_order();
    finalize_print ();
    tree->mid_order();
    finalize_print ();
    printf ("================================================================================\n");
    for (int i = 1; i<= max; i+=1){
    bt_node* temp = new bt_node (i);
    tree->insert(*temp);
    delete temp;
    }
    tree->pre_order();
    finalize_print ();
    bt_node* elem = tree->minimum(tree->root);
    while (elem != NULL){
	printf("%d[%s],", elem->v, (elem->c == bt_node::red)?"red":"black");
	elem = tree->successor(elem);
    }
    finalize_print ();
    printf ("================================================================================\n");
    for (int i = 1; i<= max; i+=1){
    tree->remove(tree->find(i));
    tree->pre_order();
    finalize_print ();
    tree->mid_order();
    finalize_print ();
    printf ("================================================================================\n");
    }
    delete tree;
    return 0;
}
