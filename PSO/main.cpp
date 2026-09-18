#include "PSO.h"

int main(int argc, char* argv[]){
    int run = 1;
    int eva = atoi(argv[1]);
    int pop_size = atoi(argv[2]);
    int dim = atoi(argv[3]);
    double c1 = 2.0;
    double c2 = 2.0;
    double w = 0.7;
    double v_max = 12.8;
    double v_min = -v_max;
    PSO alg;
    alg.RunAlg(run, eva, pop_size, dim, c1, c2, w, v_min, v_max);
    return 0;
}
