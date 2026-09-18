#include "Alg.h"
#include "stdlib.h"
int main(int argc, char *argv[])
{
    int Run = atoi(argv[1]);     // 執行次數
    int EvaluationTime = atoi(argv[2]);    // 世代數
    int Dimension = atoi(argv[3]); //維度
    int PopulationSize = atoi(argv[4]);
    double MutationFactor = atof(argv[5]);
    double CrossoverRate = atof(argv[6]);

    Alg algorithm;
    algorithm.RunALG(Run, EvaluationTime, Dimension, PopulationSize, MutationFactor, CrossoverRate);
}
