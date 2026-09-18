#include "Alg.h"
#include "../Problem.h"
#include "../tool.h"

using namespace std;
void Alg::RunALG(int _Fun, int _Run, int _Generation, int _Dimension, int _PopulationSize){
    Fun = _Fun;
    Run = _Run;
    MAX_NFE = _Generation;
    Dimension = _Dimension;
    PopulationSize = _PopulationSize;

    Problem problem;
    Tool tool;
    double sumEachRunMin = 0;

    std::cout<<"_____________________________________________________"<<endl;
    std::cout<<"Run : "<<Run<<", Evaluation Time : "<< MAX_NFE<< ", Dimension : "<< Dimension<<", PopulationSize : "<<PopulationSize<<endl;
    std::cout<<"_____________________________________________________"<<endl;

    for( int z=1; z<=Run; z++){

        ofstream outputFile("output.txt");


        int countEvaluation = 0;
        //用來放較差的population
        vector< vector<double> > Archive;
        Archive.clear();
        //初始crossover rate and mutation factor
        vector<double> mcr(PopulationSize);
        vector<double> mf(PopulationSize);
        double min = problem.GetBound(Fun)._upper;
        for( int i=0; i<PopulationSize; i++){
            mcr[i] = 0.5;
            mf[i] = 0.5;
        }

        //BestFiness : 當前最佳Finess, size = population
        vector<double> currentFitness(PopulationSize);

        //Inital
        vector< vector< double > > X(PopulationSize, vector< double >(Dimension));
        vector<double> curFitness(PopulationSize);
        vector< vector< double > > sortX(PopulationSize, vector< double >(Dimension));
        vector< double > sortFitness(PopulationSize);

        //initial population
        for( int i=0; i<PopulationSize; i++){
            for( int j=0; j<Dimension; j++){
                X[i][j] = tool.rand_double(problem.GetBound(Fun)._lower, problem.GetBound(Fun)._upper);
            }
            curFitness[i] = problem.Run(Fun, X[i]);
            NFE++;
        }

        vector< vector<double> > XNextG(PopulationSize, vector<double>(Dimension));
        //run generation
        XNextG = X;
        NFE = 0;
        while(NFE < MAX_NFE){

            //The set of all successful crossover and mutation probability
            vector<double> scr;
            vector<double> sf;

            scr.clear();
            sf.clear();

            X = XNextG;

            for( int i=0; i<PopulationSize; i++){
                double CR;
                double F;

                //normal_distribution<double> distru(mcr[i], 0.1);
                do{
                    CR= tool.rand_normal(mcr[i], 0.1);
                }while(CR > 1.0 || CR < 0.0);
                //generation mutatuon factor of each population
                //cauchy_distribution<double> dis(mf[i], 0.1);
                //編劇處理
                do{
                    F= tool.rand_cauchy(mf[i], 0.1);
                }while( F> 1.0 || F < 0);

                //sort to pick up 100P%
                sortX = X;
                sortFitness = curFitness;
                pair< vector< vector<double> >, vector<double> > srt;
                for( int i=PopulationSize-1; i>0; i--){
                    for( int j=0; j<PopulationSize-1; j++){
                        if( sortFitness[j] > sortFitness[j+1]){
                            swap(sortX[j], sortX[j+1]);
                            swap(sortFitness[j], sortFitness[j+1]);
                        }
                    }
                }
                double P = 0.05;
                int tempp;
                do{
                    tempp = (rand()%PopulationSize);
                }while(((double)tempp)/PopulationSize > P);

                //random choose r1, r2 for mutation; r1 from P, r2 from P+Archive
                double r1, r2;
                do{
                    r1 = rand()%PopulationSize;
                }while(r1 == i);

                do{
                    r2 = rand()%(PopulationSize+(Archive.size()));
                }while(r2 == i || r2 == r1);

                //Find V (mutation)
                vector< vector<double> > V(PopulationSize, vector<double>(Dimension));
                //main function of JADE mutation
                for( int j=0; j<Dimension; j++){

                    if(r2<PopulationSize){
                        V[i][j]= X[i][j] + F*(sortX[tempp][j] - X[i][j]) + F*(X[r1][j] - X[r2][j]);

                    }else{
                        V[i][j]= X[i][j] + F*(sortX[tempp][j] - X[i][j]) + F*(X[r1][j] - Archive[r2-PopulationSize][j]);

                    }
                    //確認邊界
                    if(V[i][j] >= problem.GetBound(Fun)._upper){
                        V[i][j] = (X[i][j] + problem.GetBound(Fun)._upper)/2;

                    }
                    if(V[i][j] <= problem.GetBound(Fun)._lower){
                        V[i][j] = (X[i][j] + problem.GetBound(Fun)._lower)/2;

                    }
                }

                //random choose jrand
                int jrand = rand()%Dimension;
                //Crossover
                vector< vector<double> > U(PopulationSize, vector<double>(Dimension));

                for( int j=0; j<Dimension; j++){
                    //random 0~1
                    double rZtO = tool.rand_double(0, 1);

                    if(rZtO<=CR || j == jrand){
                        U[i][j] = V[i][j];
                    }else{
                        U[i][j] = X[i][j];
                    }

                }

                //Selection
                double Fu = problem.Run(Fun, U[i]);
                NFE++;
                countEvaluation++;
                if(curFitness[i] <= Fu){
                    XNextG[i] = X[i];
                }else{
                    XNextG[i] = U[i];
                    curFitness[i] = Fu;
                    if(curFitness[i] < min)
                        min = curFitness[i];
                    if(Archive.size() >= PopulationSize){
                        int removeA = rand()%(Archive.size());
                        Archive.erase(Archive.begin()+removeA);
                    }
                    Archive.push_back(X[i]);
                    scr.push_back(CR);
                    sf.push_back(F);
                }

            }

            //rate of parameter adatation
            double c = 0.1;
            double meanA = 0;
            double sum = 0;
            for( int i=0; i<scr.size(); i++){
                sum = sum + scr[i];
            }
            if(scr.size() == 0){
                meanA = 0;
            }else{
                meanA = sum/(scr.size());
            }
            for( int i=0; i<PopulationSize; i++){
                mcr[i] = (1-c)*mcr[i] + c*meanA;
                if(mcr[i]>1){
                    mcr[i] = 1;
                }else if(mcr[i] < 0){
                    mcr[i] = 0;
                }
            }

            //mutation factor
            sum = 0;
            double sum2 = 0;
            double meanL = 0;

            for( int i=0; i<sf.size(); i++){
                sum = sum + sf[i];
                sum2 = sum2 + pow(sf[i], 2);
            }

            if(sum == 0){
                meanL = 0;
            }else{
                meanL = sum2/sum;
            }
            for( int i=0; i<PopulationSize; i++){
                mf[i] = (1-c)*mf[i] + c*meanL;
                if(mf[i]>1){
                    mf[i] = 1;
                }else if(mf[i] < 0){
                    mf[i] = 0;
                }
            }

            outputFile<<min<<endl;


        }

        sumEachRunMin += min;
        std::cout<<"Run : "<<z<<endl;
        std::cout<<"-----------------"<<endl<<"Best Fitness : "<<min<<endl<<"aveFitness : "<<sumEachRunMin/z<<endl;
        std::cout<<countEvaluation<<endl;

        outputFile.close();
    }

}

