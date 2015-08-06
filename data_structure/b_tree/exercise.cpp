#include "./b_tree.h"

int main(int argc, char* argv[]){
    b_tree *tree = new b_tree(2);
    delete tree;
}
