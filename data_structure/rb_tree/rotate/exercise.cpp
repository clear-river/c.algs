#include "./binary_tree.h"

int main(int argc, char* argv[]){
    bt_node* temp = new bt_node();
    bt_node* root = temp;
    temp->v = 15;
    temp->add_child(6, 0);
    temp->add_child(18, 1);
    temp = temp->l;
    temp->add_child(3, 0);
    temp->add_child(7, 1);
    temp = temp->l;
    temp->add_child(2, 0);
    temp->add_child(4, 1);
    temp = temp->p->r;
    temp->add_child(13, 1);
    temp = temp->r;
    temp->add_child(9, 0);
    temp = root->r;
    temp->add_child(17, 0);
    temp->add_child(20, 1);

    btree *tree = new btree(root);
    btree *tree2 = new btree(*tree);
    delete tree;

    printf("pre_order and mid_order:\n");
    tree2->pre_order();
    putchar(0x08);
    putchar(0x20);
    printf("\n");
    tree2->mid_order();
    putchar(0x08);
    putchar(0x20);
    printf("\n");

    tree2->left_rotate(tree2->root);
    printf("pre_order and mid_order:\n");
    tree2->pre_order();
    putchar(0x08);
    putchar(0x20);
    printf("\n");
    tree2->mid_order();
    putchar(0x08);
    putchar(0x20);
    printf("\n");

    tree2->right_rotate(tree2->root);
    printf("pre_order and mid_order:\n");
    tree2->pre_order();
    putchar(0x08);
    putchar(0x20);
    printf("\n");
    tree2->mid_order();
    putchar(0x08);
    putchar(0x20);
    printf("\n");

    delete tree2;
}
