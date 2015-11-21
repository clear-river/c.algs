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
        //_dump_tree (node, 0);
        return;
    }


    bt_node* _search (bt_node* node, int k, int *i){
        int index = node->find (k);
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

    bt_node* adjust_downward (int direction, int key, bt_node* prt){
        bt_node *ch, *bro;
        int index, bro_index;
        if (direction < 0){
            index = 0;
            if (prt->leaf) {return prt;}
        }else if (direction > 0){
            index = prt->size;
            if (prt->leaf) {return prt;}
        }else{
            index = prt->find (key);
            if (index < prt->size && prt->keys[index] == key){
                return prt;
            }
            if (prt->leaf){
                return NULL; //found NO key and reached the leaf node.
            }
        }
        ch = prt->children[index];
        if (ch->size > min_dgr-1){
            return adjust_downward(direction, key, ch);
        }
        if (index == 0){
            bro_index = 1;
        }else if (index == prt->size){
            bro_index = prt->size - 1;
        }else{
            bro_index = (prt->children[index-1]->size > min_dgr-1)? index-1: index;
        }
        bro = prt->children[bro_index];
        if (bro->size > min_dgr-1){
            ch->size++;
            if (bro_index < index){
                for (int i=ch->size-1; i>0; i--){
                    ch->keys[i] = ch->keys[i-1];
                }
                ch->keys[0] = prt->keys[bro_index];
                prt->keys[bro_index] = bro->keys[bro->size-1];
                if (ch->leaf==0){
                    for (int i=ch->size; i>0; i--){
                        ch->children[i] = ch->children[i-1];
                    }
                    ch->children[0] = bro->children[bro->size];
                }
                bro->size--;
            }else{
                ch->keys[ch->size-1] = prt->keys[index];
                prt->keys[index] = bro->keys[0];
                for (int i=1; i<bro->size; i++){
                    bro->keys[i-1] = bro->keys[i];
                }
                if (ch->leaf==0){
                    ch->children[ch->size] = bro->children[0];
                    for (int i=1; i<=bro->size; i++){
                        bro->children[i-1] = bro->children[i];
                    }
                }
                bro->size--;
            }
        }else{
            if (bro_index < index){
                index--; bro_index++;
                ch = prt->children[index];
                bro = prt->children[bro_index];
            }
            merge_ch(prt, index);
            if (prt->size == 0){
                root = ch;
                delete prt;
            }
        }
        return adjust_downward (direction, key, ch);
    }

    void merge_ch (bt_node* prt, int index){
        bt_node* node = prt->children[index];
        bt_node* bro = prt->children[index+1];
        node->size = (min_dgr<<1)-1;
        node->keys[min_dgr-1] = prt->keys[index];
        for (int i=0; i<min_dgr-1; i++){
            node->keys[min_dgr+i] = bro->keys[i];
        }
        if (node->leaf==0){
            node->children[min_dgr] = bro->children[0];
            for (int i=1; i<min_dgr; i++){
                node->children[min_dgr+i] = bro->children[i];
            }
        }
        delete bro;
        for (int i=index; i<prt->size-1; i++){
            prt->keys[i] = prt->keys[i+1];
        }
        for (int i=index+1; i<prt->size; i++){
            prt->children[i] = prt->children[i+1];
        }
        prt->size--;
        return;
    }

    void _delete_key (bt_node* node, int key){
        if (!node) {return;}
        int index = node->find (key);
        if (node->leaf){
            for (int i = index+1; i<node->size; i++){
                node->keys[i-1] = node->keys[i];
            }
            node->size--;
            return;
        }
        bt_node* ch;
        int ch_key;
        if (node->children[index]->size > min_dgr-1){
            ch = adjust_downward (1, 0, node->children[index]);
            ch_key = ch->keys[ch->size-1];
            node->keys[index] = ch_key;
            _delete_key (ch, ch_key);
            return;
        }
        if (node->children[index+1]->size > min_dgr-1){
            ch = adjust_downward (-1, 0, node->children[index+1]);
            ch_key = ch->keys[0];
            node->keys[index] = ch_key;
            _delete_key (ch, ch_key);
            return;
        }
        merge_ch (node, index);
        _delete_key (node->children[index], key);
        if (node->size == 0){
            root = node->children[0];
            delete node;
        }
    }

    void delete_key (int key){
        bt_node* node_k = adjust_downward(0, key, root);
        _delete_key (node_k, key);
    }
};

#endif
