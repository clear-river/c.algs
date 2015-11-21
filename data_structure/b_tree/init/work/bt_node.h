#ifndef BT_NODE
#define BT_NODE
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

//typedef unsigned int _uint;
typedef int _uint;

class bt_node{
    public:
    _uint min_degree, capacity;
    int* keys;
    _uint leaf;
    bt_node ** children;
    _uint size;

    bt_node(_uint t):leaf(1), children(NULL), size(0){
        capacity = (t<<1) -1;
        min_degree = t;
        keys = (int*) malloc (capacity * sizeof (int));
    }

    ~bt_node (){
        if (keys) {free (keys);}
        if (children) {free (children);}
    }

    std::vector<std::string> dump_content() const{
        std::vector<std::string> buf;
        char str_buf[500];
    
        sprintf(str_buf, "min_degree=%u;\n", min_degree);
        buf.push_back(str_buf);
        sprintf(str_buf, "capacity=%u;size=%u;\n", capacity, size);
        buf.push_back(str_buf);
        for (_uint i = 0; i < size; i++){
            sprintf(str_buf, "keys[%u]=%u;\n", i, keys[i]);
            buf.push_back(str_buf);
        }
        if (leaf){
            sprintf(str_buf, "#Leaf node.\n");
            buf.push_back(str_buf);
            return buf;
        }
        std::stringstream strstrm;
        for (_uint i = 0; i <= size; i++){
            strstrm << "children[" << i << "]=";
            if (children[i] == NULL) {
                strstrm << "NULL" << std::endl;
            }else{
                strstrm << children[i]->keys[0] << std::endl;
            }
            //(children[i] == NULL)?"NULL":children[i]->keys[0] << std::endl;
            buf.push_back(strstrm.str());
            strstrm.str("");
        }
        return buf;
    }
};

#endif
