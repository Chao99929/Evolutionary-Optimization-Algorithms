#include "shade.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){
    int Fun = atoi(argv[1]);     //問題
    int Run = atoi(argv[2]);     // 執行次數
    int EvaluationTime = atoi(argv[3]);    // 世代數
    int Dimension = atoi(argv[4]); //維度
    int PopulationSize = atoi(argv[5]);
    int HistorySize = atoi(argv[6]);

    Shade shade;
    shade.RunALG(Fun, Run, EvaluationTime, Dimension, PopulationSize, HistorySize);
    return 0;
}
// ./shade.exe  50 300000 30 100 100
