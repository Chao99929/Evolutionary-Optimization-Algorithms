#ifndef LSHADE_H
#define LSHADE_H

#include "../tool.h"
#include "../Problem.h"
#include <fstream>
#include <queue>
#include <iostream>
#include <cstdio>
#include <vector>
#include <random>
#include <math.h>
#include <algorithm>
using namespace std;

class Lshade
{
public:
    void RunALG(int, int, int, int, int, int, int);

private:
    int _Run;
    int _NP;
    int _Gen;
    int _Arch;
    int _Dim;
    int _Fess;
    int _H;
    int _NPmin;
    int _NPnow;
    int _k;
    int _Fun;
    int _FessNow;
    double _sumEachRunMinFitness;
    double _min;
    vector<double> _SF, _SCR;

    typedef struct History
    {
        double _MCR, _MF;
        bool EndFlag;
    } _History;
    vector<_History> _HS;

    typedef struct Particle
    {
        vector<double> _array;
        double _inCR, _inF, _inP;
        double _fitness;
        int _index;
    } _Particle;
    _Particle _U, _V;
    vector<_Particle> _X, _A;

    void Init();
    void Evaluation();
    void Reset();

    int selectTopPBest(vector<_Particle>, double);
    void CheckBorder(_Particle &, _Particle &);
    static bool compareFitness(const _Particle &, const _Particle &);

    Tool tool;
    Problem problem;
};
void Lshade::RunALG(int Fun, int Run, int Fess, int Dim, int NP, int NPmin, int H)
{
    _Run = Run;
    _NP = NP;
    _Gen = 0;
    _Dim = Dim;
    _Arch = 0;
    _Fess = Fess;
    _H = H;
    _NPmin = NPmin;
    _NPnow = _NP;
    _Fun = Fun;

    int count  = 1;
    _sumEachRunMinFitness = 0;
    while (_Run--)
    {
        _min = problem.GetBound(_Fun)._upper;
        cout << "-------------------Run" << Run - _Run << "---------------------" << endl;

        Init();
        Evaluation();
        Reset();
        cout<<"-----------------"<<endl<<"Best Fitness : "<<_min<<endl;
        cout<<"Average of Fitness :"<<_sumEachRunMinFitness/(count)<<endl;
        count++;
    }
    cout << "end" << endl;
}

void Lshade::Init()
{

    _A.resize(0);
    _X.resize(_NP);
    _k = 0;
    _HS.resize(_H);
    _FessNow = 0;
    _NPnow = _NP;
    for (int i = 0; i < _H; i++)
    {
        _HS[i]._MCR = 0.5;
        _HS[i]._MF = 0.5;
        _HS[i].EndFlag = 0;
    }

    int dim = _Dim;
    // random init _X
    for (int i = 0; i < _NP; i++)
    {
        _X[i]._array.resize(dim);
        for (int j = 0; j < dim; j++)
        {
            _X[i]._array[j] = tool.rand_double(problem.GetBound(_Fun)._lower, problem.GetBound(_Fun)._upper);
        }
        _X[i]._fitness = problem.Run(_Fun, _X[i]._array);
        _X[i]._index = i;
        _X[i]._inCR = _X[i]._inF = 0;
    }
    // init var
    _U._array.resize(dim);
    _V._array.resize(dim);
    _U._fitness = _V._fitness = 0;
    _SCR.resize(_NP);
    _SF.resize(_NP);
}

void Lshade::Evaluation()
{
    _Gen=0;

    ofstream outputFile("output.txt");

    while (_FessNow < _Fess)
    {
        // check in Evaluation times
        if (_FessNow+_NPnow > _Fess)
            break;

        vector<double> deltaF; // to store fitness to calculate mean
        deltaF.clear();
        _SCR.clear();
        _SF.clear();
        for (int i = 0; i < _NPnow; i++)
        {
            // init CR & F & P
            int index = tool.rand_int(0, _H - 1);
            if (_HS[index].EndFlag) // new: EndFlag For CRi
            {
                _X[i]._inCR = 0;
            }
            else
            {
                _X[i]._inCR = tool.rand_normal(_HS[index]._MCR, 0.1);
                if (_X[i]._inCR > 1)
                {
                    _X[i]._inCR = 1;
                }
                else if (_X[i]._inCR < 0)
                {
                    _X[i]._inCR = 0;
                }
            }
            do
            {
                _X[i]._inF = tool.rand_cauchy(_HS[index]._MF, 0.1);
                if (_X[i]._inF >= 1)
                {
                    _X[i]._inF = 1;
                }
            } while (_X[i]._inF <= 0);

            if (2.0/_NPnow > 0.2){
                _X[i]._inP = 0.2;
            }
            else {
                _X[i]._inP = tool.rand_double(2.0/_NPnow, 0.2);
            }

            // Random choose three place to mutation
            int best, r1, r2, flag = 0;
            best = selectTopPBest(_X, _X[i]._inP);
            do
            {
                r1 = tool.rand_int(0, _NPnow - 1);
            } while (r1 == i);
            do
            {
                r2 = tool.rand_int(0, _NPnow + _A.size() - 1);
                if (r2 >= _NPnow)
                {
                    bool checkFlag = 0;
                    for (int j = 0; j < _Dim; j++)
                    {
                        if (_A[r2 - _NPnow]._array[j] != _X[i]._array[j])
                        {
                            checkFlag = 1;
                            break;
                        }
                    }
                    for (int j = 0; j < _Dim; j++)
                    {
                        if (_A[r2 - _NPnow]._array[j] != _X[r1]._array[j])
                        {
                            checkFlag = 1;
                            break;
                        }
                    }
                    if (checkFlag == 0) { continue; }
                    else {
                        r2 -= _NPnow;
                        flag = 1;
                        break;
                    }
                }
            } while (r2 == i || r2 == r1);

            // mutation & check boundary
            for (int j = 0; j < _Dim; j++)
            {
                double F = _X[i]._inF;
                if (flag == 0)
                {
                    _V._array[j] = _X[i]._array[j] + F * (_X[best]._array[j] - _X[i]._array[j]) + F * (_X[r1]._array[j] - _X[r2]._array[j]);
                }
                else
                {
                    _V._array[j] = _X[i]._array[j] + F * (_X[best]._array[j] - _X[i]._array[j]) + F * (_X[r1]._array[j] - _A[r2]._array[j]);
                }
                CheckBorder(_V, _X[i]);
            }
            // crossover
            int jrand = tool.rand_int(0, _Dim - 1);
            for (int j = 0; j < _Dim; j++)
            {
                if (j == jrand || tool.rand_double(0, 1) < _X[i]._inCR)
                {
                    _U._array[j] = _V._array[j];
                }
                else
                {
                    _U._array[j] = _X[i]._array[j];
                }
            }
            // Selection
            _U._fitness = problem.Run(_Fun, _U._array);
    
            if (_X[i]._fitness >= _U._fitness)
            {
                if (_X[i]._fitness > _U._fitness)
                {
                    _A.push_back(_X[i]);
                    _SCR.push_back(_X[i]._inCR);
                    _SF.push_back(_X[i]._inF);
                    deltaF.push_back(_X[i]._fitness - _U._fitness);
                }
                _X[i]._array = _U._array;
                _X[i]._fitness = _U._fitness;

                if(_X[i]._fitness < _min){
                    _min = _X[i]._fitness;
            }
            }
        }

        // Update HS
        if (_SCR.size() != 0 && _SF.size() != 0)
        {
            // prepare param
            double mCR, mF, WKdenominator, numerator, denominator;
            mCR = mF = WKdenominator = numerator = denominator = 0;

            for (int t = 0; t < _SCR.size(); t++)
            {
                WKdenominator += deltaF[t];
            }

            // Update MCR
            double maxSCR = *max_element(_SCR.begin(), _SCR.end());
            if (_HS[_k].EndFlag || maxSCR == 0)
            {
                _HS[_k].EndFlag = 1;
            }
            else
            {
                for (int t = 0; t < _SCR.size(); t++)
                {
                    // mean weight Scr
                    mCR += (deltaF[t] / WKdenominator) * _SCR[t];
                }
                _HS[_k]._MCR = mCR;
            }

            // Update MF
            for (int t = 0; t < _SCR.size(); t++)
            {
                // Lehmer mean
                numerator += (deltaF[t] / WKdenominator) * _SF[t] * _SF[t];
                denominator += (deltaF[t] / WKdenominator) * _SF[t];
            }
            mF = numerator / denominator;
            _HS[_k]._MF = mF;

            _k++;
            if (_k == _H)
                _k = 0;
        }

        // new: Population Reduction, Update NPnow
        _FessNow += _NPnow;

        int _NPnext = (int) round((((_NPmin - _NP) / (double)_Fess) *  (double)_FessNow) + _NP );

        if (_NPnext > _NPmin){
            if (_NPnow > _NPnext) {
                _NPnow = _NPnext;
                _Arch = _NPnext;
                sort(_X.begin(), _X.end(), compareFitness);
                _X.resize(_NPnext);
            }
        }

        // Resize Archive size
        while (_A.size() > _Arch)
        {
            // randomly remove one element from A
            int remove = tool.rand_int(0, _A.size() - 1);
            _A.erase(_A.begin() + remove);
        }

        // show data
        double tmp = _X[0]._fitness;
        for (int p = 1; p < _NPnow; p++)
        {
            if (tmp > _X[p]._fitness)
                tmp = _X[p]._fitness;
        }

        _Gen++;
        outputFile<<_min<<endl;

    }
    outputFile.close();
    _sumEachRunMinFitness += _min;
}

void Lshade::Reset()
{
    _X.clear();
    _A.clear();
    _U._array.clear();
    _V._array.clear();

}

void Lshade::CheckBorder(_Particle &check, _Particle &old)
{
    for (int i = 0; i < _Dim; i++)
    {
        if (check._array[i] < problem.GetBound(_Fun)._lower)
        {
            check._array[i] = (problem.GetBound(_Fun)._lower + old._array[i]) / 2;
        }
        if (check._array[i] > problem.GetBound(_Fun)._upper)
        {
            check._array[i] = (problem.GetBound(_Fun)._upper + old._array[i]) / 2;
        }
    }
}

bool Lshade::compareFitness(const _Particle &a, const _Particle &b)
{
    return a._fitness < b._fitness;
}

int Lshade::selectTopPBest(vector<_Particle> X, double p)
{
    vector<_Particle> tmp = X;
    sort(tmp.begin(), tmp.end(), compareFitness);
    int place;
    place = p * _NPnow;
    place = tool.rand_int(0, place);
    return tmp[place]._index;
}

#endif
