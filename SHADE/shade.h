#ifndef SHADE_H
#define SHADE_H

#include <fstream>
#include "../tool.h"
#include "../Problem.h"
#include <queue>
#include <iostream>
#include <cstdio>
#include <vector>
#include <random>
#include <math.h>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Shade{

public:

    void RunALG(int, int, int, int, int, int);

private:
    int _Fun;
    int _Run;
    int _PopulationSize;
    int _Generation;
    int _EvaluationTime;
    int _CountEvaluation;
    int _Dimention;
    int _HistorySize;
    int _k;
    int _r;
    double _sumEachRunMinFitness;
    
    vector<double> _SF, _SCR;

    typedef struct History{
        double _MCR, _MF;
    } _History;
    vector<_History> _HS;

    typedef struct Particle{
        vector<double> _array;
        double _inCR, _inF, _inP;
        double _fitness;
    } _Particle;
    
    vector<_Particle> _U, _V;
    vector<_Particle> _X, _A;

    Tool tool;
    Problem problem;
    
    
    void Init();
    void Evaluation();
    void Reset();
    static bool compareFitness(const _Particle &, const _Particle &);

    
};

void Shade::RunALG(int Fun, int Run, int Gen, int Dim, int NP, int H)
{
    _Fun = Fun;
    _Run = Run;
    _PopulationSize = NP;
    _EvaluationTime = Gen;
    _Generation = Gen;
    _Dimention = Dim;
    _HistorySize = H;
    _sumEachRunMinFitness = 0;
    _r = 1;
    
    while (Run--){
        cout << "-------------------Run" << _r << "---------------------" << endl;
        Init();
        Evaluation();
        Reset();
        _r++;
    }
    
}
void Shade::Init(){
    _X.resize(_PopulationSize);
    _HS.resize(_HistorySize);
    _SCR.resize(_PopulationSize);
    _SF.resize(_PopulationSize);
    _U.resize(_PopulationSize);
    _V.resize(_PopulationSize);
    
    _k = 0;
    _A.resize(0);
    
    //initialize population
    for( int i=0; i<_PopulationSize; i++){
        _X[i]._array.resize(_Dimention);
        _U[i]._array.resize(_Dimention);
        _V[i]._array.resize(_Dimention);
        
        for( int j=0; j<_Dimention; j++){
            _X[i]._array[j] = tool.rand_double(problem.GetBound(_Fun)._lower, problem.GetBound(_Fun)._upper);
        }
        //_X[i]._fitness = Ackley(_X[i]);
        _X[i]._fitness = problem.Run(_Fun, _X[i]._array);
        _CountEvaluation++;
        _X[i]._inCR = _X[i]._inF = 0;
    }
    
    //Initialize history
    for( int i=0; i<_HistorySize; i++){
        _HS[i]._MCR = 0.5;
        _HS[i]._MF = 0.5;
    }

}

void Shade::Evaluation(){
    
    _CountEvaluation = 0;
    double _min = problem.GetBound(_Fun)._upper;

    
    ofstream outputFile("output.txt");
    while(_CountEvaluation < _EvaluationTime){
        vector<double> deltaF; // to store fitness to calculate mean
        deltaF.clear();

        _SCR.clear();
        _SF.clear();
    
        for( int i=0; i<_PopulationSize; i++){
            
            
            int ri = tool.rand_int(0, _HistorySize-1);

            double t;
        
            t = tool.rand_normal(_HS[ri]._MCR, 0.1);
            if(t > 1)
                t =1;
            else if(t < 0)
                t = 0;
            _X[i]._inCR = t;
            

            
            t = tool.rand_cauchy(_HS[ri]._MF, 0.1);
            if(t > 1)
                t = 1;
            while( t <= 0){
                t = tool.rand_cauchy(_HS[ri]._MF, 0.1);
            }
            _X[i]._inF = t;
            double Pmin = (2/_PopulationSize);
            //Pi maximun is 0.2
            if(Pmin > 0.2){
                Pmin = 0.2;
            }else{
                Pmin = tool.rand_double(Pmin, 0.2);
            }
            _X[i]._inP = Pmin;
            //cout<<Pmin<<endl;
            //Mutation current to pbest
            double r1, r2;
            do{
                r1 = tool.rand_int(0, _PopulationSize-1);
            }while(r1 == i);

            do{
                r2 = tool.rand_int(0, (_PopulationSize + _A.size())-1);
                if(r2 > _PopulationSize){

                    bool flag = 0;

                    for( int j=0; j<_Dimention; j++){
                        if(_A[ r2-_PopulationSize]._array[j] != _X[i]._array[j]){
                            flag = 1;
                            break;
                        }
                    }
                    for( int j=0; j<_Dimention; j++){
                        if(_A[ r2-_PopulationSize]._array[j] != _X[r1]._array[j]){
                            flag = 1;
                            break;
                        }
                    }
                    if(flag){
                        break;
                    }else{
                        continue;
                    }
                }
            }while( r2 == i || r2 == r1);
            double f = _X[i]._inF;

            vector<Particle> srt;
            srt.resize(_PopulationSize);
            srt = _X;

            sort(srt.begin(), srt.end(), compareFitness);

            

            int best;
            do{
                best = (rand()%_PopulationSize);
            }while(((double)best)/_PopulationSize > _X[i]._inP);
            //cout<<"*************"<<best<<endl;
            for( int j=0; j<_Dimention; j++){
                if(r2 < _PopulationSize){
                    _V[i]._array[j] = _X[i]._array[j] + f*( srt[best]._array[j] - _X[i]._array[j] ) + f*(_X[r1]._array[j] - _X[r2]._array[j]);
                }else{
                    _V[i]._array[j] = _X[i]._array[j] + f*( srt[best]._array[j] - _X[i]._array[j] ) + f*(_X[r1]._array[j] - _X[r2-_PopulationSize]._array[j]);
                }

                //邊界處理(by paper)
                if( _V[i]._array[j] > problem.GetBound(_Fun)._upper ){
                    _V[i]._array[j] = ( _X[i]._array[j] + problem.GetBound(_Fun)._upper )/2;
                }else if( _V[i]._array[j] < problem.GetBound(_Fun)._lower ){
                    _V[i]._array[j] = ( _X[i]._array[j] + problem.GetBound(_Fun)._lower )/2;
                }
            }
            //Crossover
            int jrand = tool.rand_int(0, _Dimention - 1);
            for (int j = 0; j < _Dimention; j++){
                if (j == jrand || tool.rand_double(0, 1) < _X[i]._inCR){
                    _U[i]._array[j] = _V[i]._array[j];
                }else{
                    _U[i]._array[j] = _X[i]._array[j];
                }
            }
        }

        //Selection
        for( int i=0; i<_PopulationSize; i++){

            /*
            for( int j=0; j<_Dimention; j++){
                cout<<_X[i]._array[j]<<" ";
            }
            cout<<endl;

            */
            //_U[i]._fitness = Ackley(_U[i]);
            _U[i]._fitness = problem.Run(_Fun, _U[i]._array);
            _CountEvaluation++;
            if(_U[i]._fitness <= _X[i]._fitness){
                

                if(_U[i]._fitness < _X[i]._fitness){
                    _A.push_back(_X[i]);
                    _SCR.push_back(_X[i]._inCR);
                    _SF.push_back(_X[i]._inF);
                    deltaF.push_back(_X[i]._fitness - _U[i]._fitness);
                }
                _X[i]._array = _U[i]._array;
                _X[i]._fitness = _U[i]._fitness;

                if(_X[i]._fitness < _min){
                    _min = _X[i]._fitness;
                }
            }
        }
        //cout<<"--------------------"<<endl;
        while (_A.size() > _PopulationSize){
            // randomly remove one element from A
            if (_A.size()>=1) {
                int remove = tool.rand_int(0, _A.size() - 1);
                _A.erase(_A.begin() + remove);
            }
        }

        if (_SCR.size() != 0 && _SF.size() != 0){
            // prepare param
            double WK = 0;
            for (int t = 0; t < _SCR.size(); t++){
                WK += deltaF[t];
            }

            double mCR, mF, sum, douSum;
            mCR = mF = sum = douSum = 0;
            for (int t = 0; t < _SCR.size(); t++){
                // mean weight Scr
                mCR += (deltaF[t] / WK) * _SCR[t];
                // Lehmer mean
                douSum += (deltaF[t] / WK) * _SF[t] * _SF[t];
                sum += (deltaF[t] / WK) * _SF[t];
            }
            mF = douSum / sum;
            
            _HS[_k]._MCR = mCR;
            _HS[_k]._MF = mF;

            _k++;
            if (_k == _HistorySize)
                _k = 0;

            //cout<<_CountEvaluation<<" "<<_EvaluationTime<<endl;

        }
        
        outputFile<<_min<<endl;
    }
    
    outputFile.close();
    _sumEachRunMinFitness += _min;
    cout<<"-----------------"<<endl<<"Best Fitness : "<<_min<<endl;
    cout<<"Average of Fitness :"<<_sumEachRunMinFitness/(_r)<<endl;
}


void Shade::Reset(){
    
    _X.clear();
    _A.clear();
    _U.clear();
    _V.clear();
}

bool Shade::compareFitness(const _Particle &a, const _Particle &b){
    return a._fitness < b._fitness;
}


#endif