class pipeline {
    public:
    typedef unsigned int uint;
    uint in, out, size, number;
    uint *proc, *trans, *sub_min;
    pipeline **choice;

    static uint curr_number;

    pipeline (const uint i, const uint o, const uint s, uint *p, uint *t){
	if (s == 0) {return;}
	in = i; out = o; proc = p; trans = t;
	size = s;
	number = curr_number++;
	sub_min = (uint*) malloc (s*sizeof(uint));
	choice = (pipeline**) malloc (s*sizeof(pipeline*));
    }

    ~pipeline (){
	    if (sub_min) {
	        free (sub_min);
	    }
	    if (choice) {
	        free (choice);
	    }
    }

    void dump_sub_min(){
        printf("pipeline %u sub_min:\n",number);
        for (uint i=0; i<size; i++){
            printf("%u,", sub_min[i]);
        }
        printf("\n");
    }

    void dump_choices(){
        printf("pipeline %u choices:\n", number);
        for(uint i=0; i<size; i++){
            printf("%u,", (choice[i])?choice[i]->number:0);
        }
        printf("\n");
    }
};

