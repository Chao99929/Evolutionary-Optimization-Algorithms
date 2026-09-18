#include "Alg.h"
#include "../tool.h"

void Alg::RunALG(int _Run, int _EvaluationTime, int _Dimension, int _PopulationSize, double _MutationFactor, double _CrossoverRate)
{

    Run = _Run;
    EvaluationTime = _EvaluationTime;
    Dimension = _Dimension;
    PopulationSize = _PopulationSize;
    MutationFactor = _MutationFactor;
    CrossoverRate = _CrossoverRate;
    sumEachRunMin = 0;
    vector< vector<double> > X(PopulationSize, vector<double>(Dimension));

    ofstream outputFile("output.txt");


    cout<<"_____________________________________________________"<<endl;
    cout<<"Run : "<<Run<<", EvoluationTime : "<< EvaluationTime<< ", Dimension : "<< Dimension<<", PopulationSize : "<<PopulationSize<<", MutationFactor : "<<MutationFactor<<", CrossoverRate : "<<CrossoverRate<<endl;
    cout<<"_____________________________________________________"<<endl;

    srand(time(0));
    double min;

    for (int z = 1; z < Run+1; z++)
    {
        //reset evaluation 次數
        Reset();
        //給定初始解
        X = Init();

        vector<double> BestFitness(PopulationSize);

        vector< double > sortFitness;
        for( int j=0; j<PopulationSize; j++){
            BestFitness[j] = Ackley(X[j]);
        }

        double min = BestFitness[0];
        mnfes = EvaluationTime;
        //Evaluation (計算次數)
        for(int g = 0; g<_EvaluationTime; g++){
            //Mutation
            vector< vector<double> > V = Mutation(X, BestFitness);

            //Crossover
            vector< vector<double> > U = Crossover(X, V);

            //Selection
            pair< vector< vector<double> >, vector<double> > Target = Evaluation(X, U, BestFitness);

            X = Target.first;
            BestFitness = Target.second;

            //Find the minimum of each iteration and write into txt

            for( int i=1; i<PopulationSize; i++){
                if(min > BestFitness[i]){
                    min = BestFitness[i];

                }
            }

            outputFile<<min<<endl;

        }

        sumEachRunMin += min;
        cout<<"Run : "<<z<<endl;
        cout<<"----------------------"<<endl<<"aveMin : "<<sumEachRunMin/z<<endl;;
        cout<<"MIN : "<<min<<endl;
        outputFile.close();

    }

}

pair< vector< vector<double> >, vector<double> > Alg::Evaluation(vector< vector<double> > x, vector< vector<double> > u, vector<double> BF)
{
    pair< vector< vector<double> >, vector<double> > result;
    vector< vector<double> > t(PopulationSize+1, vector<double>(Dimension));

    for( int i=0; i<PopulationSize; i++){

        double Fu = Ackley(u[i]);
        if( Fu < BF[i] ){
            t[i] = u[i];
            BF[i] = Fu;
        }else{
            t[i] = x[i];
        }
    }
    result = make_pair(t, BF);
    return result;
}

void Alg::Reset()
{
    nfes = 0;
}

vector< vector< double > > Alg::Init()
{

    vector< vector< double > > x(PopulationSize, vector< double >(Dimension));
    for( int i=0; i<PopulationSize; i++){
        for( int j=0; j<Dimension; j++){

            x[i][j] = gen_rand(-32, 32);

        }
    }

    return x;
}

vector< vector<double> > Alg::Mutation(vector< vector<double> > x, vector<double> BF){
    vector< vector<double> > v(PopulationSize, vector<double>(Dimension));
    vector< vector<double> > sortXByFitness(PopulationSize, vector<double>(Dimension));
    sortXByFitness = x;
    for( int i=PopulationSize-1; i>0; i--){
        for( int j=0; j<PopulationSize-1; j++){
            if( BF[j] > BF[j+1]){
                swap(sortXByFitness[j], sortXByFitness[j+1]);
            }
        }
    }
    double P = 0.05;
    int tempp;
    do{
        tempp = (rand()%PopulationSize);
    }while(((double)tempp)/PopulationSize > P);

    for( int i=0; i<PopulationSize; i++){
        for( int j=0; j<Dimension; j++){
            int sum = 0;
            int r1, r2, r3;
            do{
                r1 = rand()%PopulationSize;
            }while(r1 == i);
            do{
                r2 = rand()%PopulationSize;
            }while(r2 == i || r2 == r1);
            v[i][j] = x[i][j] + MutationFactor*(sortXByFitness[tempp][j]-x[i][j]) + MutationFactor*(x[r1][j]-x[r2][j]);
            //確認邊界
            if(v[i][j] >= 32){
                v[i][j] = (x[i][j] + 32)/2;
            }
            if(v[i][j] <= -32){
                v[i][j] = (x[i][j] + -32)/2;
            }
        }
    }
    return v;
}

vector< vector<double> > Alg::Crossover(vector< vector<double> > x, vector< vector<double> > v){

    double rZtO;
    int jrand;

    vector< vector<double> > u(PopulationSize, vector<double>(Dimension));

    for( int i=0; i<PopulationSize; i++){

        jrand = rand()%Dimension;
        for( int j=0; j<Dimension; j++){
            //random 0~1
            rZtO = gen_rand(0, 1);

            if(rZtO<=CrossoverRate || j == jrand){
                u[i][j] = v[i][j];
            }else{
                u[i][j] = x[i][j];
            }

        }
    }

    return u;
}

double  Alg::Ackley(vector<double> x) {
    double a = 20.0;
    double b = 0.2;
    double c = 2 * M_PI;
    int dim = x.size();

    double sum1 = 0.0;
    double sum2 = 0.0;

    nfes++;

    for (int i = 0; i < dim; ++i) {
        sum1 += x[i] * x[i];
        sum2 += cos(c * x[i]);
    }

    return -a * exp(-b * sqrt(sum1 / dim)) - exp(sum2 / dim) + a + exp(1);
}

double Alg::gen_rand(int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
