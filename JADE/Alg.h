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
#include <utility>
#include <algorithm>
using namespace std;

class Alg
{
public:
    void RunALG(int, int, int, int, int);

private:
    // Input from Command-line Argument
    int Fun;
    int Run;
    int MAX_NFE;
    int Dimension;
    int PopulationSize;
    int NFE;

};

#endif
