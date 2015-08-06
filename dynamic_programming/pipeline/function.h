#include <stdio.h>
#include <stdlib.h>

#include "./pipeline.h"

pipeline::uint pipeline::curr_number = 1;

pipeline* calc_min_dur (pipeline* a, pipeline* b){
    a->sub_min[0] = a->in + a->proc[0];
    b->sub_min[0] = b->in + b->proc[0];
    a->choice[0] = b->choice[0] = NULL;
    pipeline::uint i = 1;
    for (i = 1; i<a->size; i++){
	if (a->sub_min[i-1] + a->trans[i-1] < b->sub_min[i-1]){
	    b->sub_min[i] = a->sub_min[i-1] + a->trans[i-1] + b->proc[i];
	    b->choice[i] = a;
	}else{
	    b->sub_min[i] = b->sub_min[i-1] + b->proc[i];
	    b->choice[i] = b;
	}

	if (b->sub_min[i-1] + b->trans[i-1] < a->sub_min[i-1]){
	    a->sub_min[i] = b->sub_min[i-1] + b->trans[i-1] + a->proc[i];
	    a->choice[i] = b;
	}else{
	    a->sub_min[i] = a->sub_min[i-1] + a->proc[i];
	    a->choice[i] = a;
	}
    }
    a->dump_sub_min();
    a->dump_choices();
    b->dump_sub_min();
    b->dump_choices();
    return (a->sub_min[i-1] + a->out < b->sub_min[i-1] + b->out)?a:b;
}

void _print_s_sequence (pipeline* p, pipeline::uint i){
    if (p->choice[i] == NULL) {return;}
    _print_s_sequence (p->choice[i], i-1);
    printf("%u, %u\n", p->choice[i]->number, i);
}

void print_s_sequence (pipeline* p){
    _print_s_sequence (p, p->size-1);
    printf("%u, %u\n", p->number, p->size);
}
