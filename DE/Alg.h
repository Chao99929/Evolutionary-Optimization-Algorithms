#ifndef ALG_H
#define ALG_H
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <random>
using namespace std;

class Alg
{
public:
    void RunALG(int, int, int, int, double, double);

private:
    // Input from Command-line Argument
    int Run;
    int EvaluationTime;
    int Dimension;
    int PopulationSize;
    double MutationFactor;
    double CrossoverRate;
    double sumEachRunMin;
    int nfes;
    int mnfes;

    void Reset();
    vector< vector<double> > Init();
    vector< vector<double> > Mutation(vector< vector<double> >, vector<double>);
    vector< vector<double> > Crossover(vector< vector<double> >, vector< vector<double> >);

    pair< vector< vector<double> >, vector<double> > Evaluation(vector< vector<double> >, vector< vector<double> >, vector<double>);
    double Ackley(vector< double> );
    double gen_rand(int, int);

};

#endif
