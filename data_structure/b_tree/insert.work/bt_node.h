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

    std::vector<std::string> dump_content () const {
	std::vector<std::string> buf;
	std::stringstream content;

	content << "min_degree=" << min_degree << ";" << std::endl;
	buf.push_back(content.str()); content.str("");

	content << "capacity=" << capacity << ";" << " size=" << size << ";" << std::endl;
	buf.push_back(content.str()); content.str("");

	for (int i = 0; i<size; i++){
	    content << "keys[" << i << "]=" << keys[i] << ";" << std::endl;
	    buf.push_back(content.str()); content.str("");
	}

	if (leaf){
	    content << "#Leaf node." << std::endl;
	    buf.push_back(content.str()); content.str("");
	    return buf;
	}

	for (int i=0; i<=size; i++){
	    content << "children[" << i << "]=";
	    if (children[i]){
		content << children[i]->keys[0];
	    }else{
		content << "NULL";
	    }
	    content << ";" << std::endl;
	    buf.push_back(content.str()); content.str("");
	}
	return buf;
    }
};

#endif
