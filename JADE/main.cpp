#include "Alg.h"
#include "stdlib.h"

int main(int argc, char *argv[]){
    int Fun = atoi(argv[1]);
    int Run = atoi(argv[2]);     // 執行次數
    int MAX_NFE = atoi(argv[3]);    // 世代數
    int Dimension = atoi(argv[4]); //維度
    int PopulationSize = atoi(argv[5]);

    Alg algorithm;
    algorithm.RunALG(Fun, Run, MAX_NFE, Dimension, PopulationSize);
}
//./jade.exe  50 300000 30 100
//./jadeTest.exe  50 300000 30 100
