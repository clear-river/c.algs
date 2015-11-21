#ifndef B_TREE
#define B_TREE

#include "./bt_node.h"
#include <memory.h>


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

    void _dump_tree(const bt_node* rnode, _uint indent){
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
	if (d[m] == t) {return m;}
	return (t < d[m])? bisearch (d, s, m-1, t): bisearch (d, m+1, e, t);
    }

    bt_node* _search (bt_node* node, int k, _uint* i){
	_uint index;
	index = (_uint) bisearch (node->keys, 0, node->size-1, k);
	if (index < node->size && node->keys[index] == k){
	    *i = index;
	    return node;
	}
	if (node->leaf == 1){
	    return NULL;
	}
	_disk_read(node->children[index]);
	return _search(node->children[index], k, i);
    }

    bt_node* search (int k, _uint* index){
	return _search (root, k, index);
    }

    void split (bt_node* prt, _uint index){
	_uint t = min_dgr;
	bt_node* org_ch = prt->children[index];
	bt_node* new_ch = new bt_node (t);
	new_ch->leaf = org_ch->leaf;
	new_ch->size = t-1;
	_uint i = 0;
	for (i = 0; i<t-1; i++){
	    new_ch->keys[i] = org_ch->keys[t+i];
	}
	if (new_ch->leaf == 0){
	    new_ch->children = (bt_node**) malloc ((new_ch->capacity+1) * sizeof (bt_node *));
	    for (i=0; i<=t-1; i++){
		new_ch->children[i] = org_ch->children[t+i];
	    }
	}
	org_ch->size = t-1;
	for (i = prt->size; i>index; i--){
	    prt->children[i+1] = prt->children[i];
	}
	prt->children[index+1] = new_ch;
	for (i = prt->size-1; i>=index; i--){
	    prt->keys[i+1] = prt->keys[i];
	}
	prt->keys[index] = org_ch->keys[t-1];
	prt->size ++;
	_disk_write (prt);
	_disk_write (org_ch);
	_disk_write (new_ch);
    }

    void insert (int k){
	if (root->size < ((min_dgr << 1)-1)){
	    insert_nonfull (root, k);
	    return;
	}
	bt_node* new_r = new bt_node (min_dgr);
	new_r->leaf = 0;
	new_r->size = 0;
	new_r->children = (bt_node**) malloc ((new_r->capacity + 1)*sizeof (bt_node*));
	memset(new_r->children, 0, (new_r->capacity + 1)*sizeof (bt_node*));
	new_r->children[0] = root;
	root = new_r;
	printf("split root start.\n");
	split (root, 0);
	printf("split root end.\n");
	insert_nonfull(root, k);
    }

    void insert_nonfull (bt_node* node, int k){
	_uint i = 0;
	if (node->leaf){
	    for (i = node->size-1; i>=0; i--){
		if (node->keys[i] < k) {break;}
		node->keys[i+1] = node->keys[i];
	    }
	    node->keys[i+1] = k;
	    node->size++;
	    _disk_write(node);
	    return;
	}
	for (i = node->size-1; i>=0; i--){
	    if (node->keys[i] < k){
		break;
	    }
	}
	_disk_read (node->children[++i]);
	if (node->children[i]->size == (min_dgr << 1)-1){
	    printf("split node %u at %u start.\n", node->keys[0], i);
	    split (node, i);
	    printf("split node %u at %u end.\n", node->keys[0], i);
	    if (node->keys[i] < k){
		i++;
	    }
	}
	insert_nonfull (node->children[i], k);
    }

};

#endif
