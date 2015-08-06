class bt_node {
    public:
    enum rb_color {red, black};
    int v;
    rb_color c;
    bt_node *p, *l, *r;

    bt_node (const int value = 0, const rb_color cl = black):p(NULL), l(NULL), r(NULL){
	v = value;
	c = cl;
    }

    bt_node (const bt_node &n):p(NULL), l(NULL), r(NULL){
	v = n.v;
	c = n.c;
    }
};
