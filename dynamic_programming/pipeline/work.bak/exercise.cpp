#include "./function.h"

int main (int argc, char* argv[]){
    pipeline::uint p1p[] = {7, 9, 3, 4, 8, 4};
    pipeline::uint p1t[] = {2, 3, 1, 3, 4, 0};
    pipeline::uint p2p[] = {8, 5, 6, 4, 5, 7};
    pipeline::uint p2t[] = {2, 1, 2, 2, 1, 0};
    pipeline::uint p1in = 2, p2in = 4, p1out = 3, p2out = 2, size = 6;

    pipeline *p1 = new pipeline (p1in, p1out, size, p1p, p1t);
    pipeline *p2 = new pipeline (p2in, p2out, size, p2p, p2t);

    print_s_sequence (calc_min_dur (p1, p2));

    delete p1;
    delete p2;
}
