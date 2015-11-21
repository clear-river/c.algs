#ifndef B_TREE
#define B_TREE

#include "./bt_node.h"
#include <memory.h>
#include <iostream>


class b_tree{
    public:
    bt_node* root;
    _uint min_dgr;

    b_tree (_uint t){
        root = NULL;
	min_dgr = t;
    }

    ~b_tree (){
        destroy (root);
    }

    void destroy (bt_node* n){
        if (n == NULL) {return;}
        if (n->leaf) {delete n; return;}
        for (_uint i = 0; i <= n->size; i++){
            destroy (n->children[i]);
        }
        delete n;
        return;
    }

    void dump_tree (){
    	_dump_tree(root, 0);
    }

/*    void _dump_tree(const bt_node* rnode, _uint indent){
    	if (rnode == NULL) {
    	    for (_uint i = 0; i<indent; i++){
    			printf("\t");
    	    }
    	    printf("Node is NULL\n\n");
    	    return;
    	}
    	std::vector<std::string> node_dump = rnode->dump_content();
    	std::vector<std::string>::iterator dump_p = node_dump.begin();
    	for (; dump_p != node_dump.end(); dump_p++){
    	    for (_uint i = 0; i<indent; i++){
    			printf("\t");
    	    }
    	    printf("%s", dump_p->c_str());
    	}
        printf("\n");
    	if (rnode->leaf) {return;}
    	for (_uint i = 0; i <= rnode->size; i++){
    	    _dump_tree (rnode->children[i], indent+1);
    	}
    	return;
    }*/

    void _dump_tree (const bt_node* node, int indent){
	if (!node) {
	    for (int i = 0; i< indent; i++){
		std::cout << "\t";
	    }
	    std::cout << "#Node is NULL\n" << std::endl;
	    return;
	}
	std::vector <std::string> buf = node->dump_content();
	std::vector <std::string>::iterator dump_p = buf.begin();
	for (; dump_p!=buf.end(); dump_p++){
	    for (int i = 0; i < indent; i++){
		std::cout << "\t";
	    }
	    std::cout << dump_p->c_str();
	}
	std::cout << std::endl;
	if (node->leaf) {return;}
	for (int index = 0; index <= node->size; index++){
	    _dump_tree (node->children[index], indent+1);
	}
	return;
    }
    
    void _disk_read (bt_node* node){
	printf("read node %u.\n", node->keys[0]);
	return;
    }

    void _disk_write (bt_node* node){
	printf("write node %u:\n", node->keys[0]);
	_dump_tree (node, 0);
	return;
    }

    int bisearch (int* d, int s, int e, int t){
	if (s>e) {return s;}
	int m = (s+e) >> 1;
	if (t == d[m]){
	    return m;
	}
	return (t<d[m])? bisearch (d, s, m-1, t): bisearch (d, m+1, e, t);
    }

    bt_node* _search (bt_node* node, int k, int *i){
	int index = bisearch (node->keys, 0, node->size-1, k);
	if (index < node->size && k == node->keys[index]){
	    *i = index;
	    return node;
	}
	if (node->leaf){
	    return NULL;
	}
	_disk_read (node->children[index]);
	return _search(node->children[index], k, i);
    }

    bt_node* search (int value, int *index){
	return _search(root, value, index);
    }

    void split (bt_node* node, int index){
	bt_node* ch = node->children[index];
	bt_node* new_ch = new bt_node(min_dgr);
	int i = 0;
	new_ch->leaf = ch->leaf;
	new_ch->size = ch->size = min_dgr-1;
	for (i=0; i<min_dgr-1; i++){
	    new_ch->keys[i] = ch->keys[min_dgr+i];
	}
	if (new_ch->leaf == 0){
	    new_ch->children = (bt_node**) malloc ((new_ch->capacity+1)*sizeof(bt_node*));
	    for (i=0; i<min_dgr; i++){
		new_ch->children[i] = ch->children[min_dgr+i];
	    }
	}
	for (i=node->size; i>index; i--){
	    node->children[i+1] = node->children[i];
	}
	for (i=node->size-1; i>=index; i--){
	    node->keys[i+1] = node->keys[i];
	}
	node->size++;
	node->keys[index] = ch->keys[min_dgr-1];
	node->children[index+1] = new_ch;
	_disk_write(node);
	_disk_write(ch);
	_disk_write(new_ch);
    }

void insert(int k){
    if (root == NULL){
	root = new bt_node(min_dgr);
    }
    if (root->size == root->capacity){
	bt_node* new_r = new bt_node (min_dgr);
	new_r->leaf = 0;
	new_r->children = (bt_node**) malloc ((new_r->capacity+1) * sizeof (bt_node*));
	new_r->children[0] = root;
	root = new_r;
	split (root, 0);
    }
    insert_nonfull (root, k);
}

void insert_nonfull (bt_node* node, int k){
    int i = 0;
    if (node->leaf){
	for (i=node->size-1; i>=0; i--){
	    if (k<node->keys[i]) {
		node->keys[i+1] = node->keys[i];
		continue;
	    }
	    break;
	}
	node->keys[i+1] = k;
	node->size++;
	_disk_write(node);
	return;
    }
    for (i=0; i<node->size; i++){
	if (k<node->keys[i]){
	    break;
	}
    }
    _disk_read (node->children[i]);
    if (node->children[i]->size == node->children[i]->capacity){
	split(node, i);
	if (k>node->keys[i]){
	    i++;
	}
    }
    insert_nonfull(node->children[i], k);
}

};

#endif
