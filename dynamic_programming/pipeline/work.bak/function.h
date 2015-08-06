#include <stdio.h>
#include <stdlib.h>

#include "./pipeline.h"

pipeline::uint pipeline::curr_number = 1;

pipeline* calc_min_dur (pipeline* p1, pipeline *p2){
    p1->sub_min[0] = p1->in + p1->proc[0];
    p2->sub_min[0] = p2->in + p2->proc[0];
    p1->choice[0] = p2->choice[0] = NULL;
    pipeline::uint i = 1;
    for (; i<p1->size; i++){
	if (p1->sub_min[i-1] < p2->sub_min[i-1] + p2->trans[i-1]){
	    p1->sub_min[i] = p1->sub_min[i-1] + p1->proc[i];
	    p1->choice[i] = p1;
	}else{
	    p1->sub_min[i] = p2->sub_min[i-1] + p2->trans[i-1] + p1->proc[i];
	    p1->choice[i] = p2;
	}
	if (p2->sub_min[i-1] < p1->sub_min[i-1] + p1->trans[i-1]){
	    p2->sub_min[i] = p2->sub_min[i-1] + p2->proc[i];
	    p2->choice[i] = p2;
	}else{
	    p2->sub_min[i] = p1->sub_min[i-1] + p1->trans[i-1] + p2->proc[i];
	    p2->choice[i] = p1;
	}
    }//for
    p1->dump_sub_min();
    p1->dump_choices();
    p2->dump_sub_min();
    p2->dump_choices();

    return ((p1->sub_min[(p1->size)-1] + p1->out) < (p2->sub_min[(p2->size)-1] + p2->out))? p1 : p2;
}

/*void _print_s_sequence (pipeline *curr, pipeline::uint i){
    if (curr->choice[i-1] != NULL){
	_print_s_sequence(curr->choice[i-1], i-1);
    }
    printf ("pipeline %u, station %u\n", curr->number, i);
}*/
void _print_s_sequence (pipeline *curr, pipeline::uint i){
    if (curr->choice[i] == NULL) {return;}
    _print_s_sequence(curr->choice[i], i-1);
    printf("pipeline %u, station %u\n", curr->choice[i]->number, i);
}

void print_s_sequence (pipeline *p){
    _print_s_sequence(p, p->size-1);
    printf ("pipeline %u, station %u\n", p->number, p->size);
}
