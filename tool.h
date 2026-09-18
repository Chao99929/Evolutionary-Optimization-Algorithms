#define TOOL_H

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

class Tool{
public:
    Tool(){
        unsigned int seed = generateSeedFromTimestamp();
        mt19937 init(seed);
        this->gen = init;
    }

    double rand_normal(const double mean, const double stddev){
         // normal_distribution
        normal_distribution<double> distr(mean, stddev);
        return (distr(gen));
    }

    double rand_cauchy(const double a, const double b){
        cauchy_distribution<double> distr(a, b);
        return distr(gen);
    }

    double rand_double(double min, double max){
        if (min > max){
            // return error
            int temp = min;
            min = max;
            max = temp;
        }
        uniform_real_distribution<double> dis(min, max);
        return dis(gen);
    }

    int rand_int(int min, int max){
        if (min > max){
            // return error
            cerr << "Error: rand_int min > max, " << min << " " << max << endl;
        }
        uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    double searchMin(vector<double> x){
        
        for( int i=0;  i<x.size()-1; i++){
            if(x[i]<x[i+1]){
                swap(x[i], x[i+1]);
            }
            
        }
        
        return x[(x.size())-1];
    }
    double searchMax(vector<double> x){
        
        for( int i=0; i<x.size()-1; i++){
            if(x[i]>x[i+1]){
                swap(x[i], x[i+1]);
            }
        }
        return x[(x.size())-1];
    }
private:
    unsigned int generateSeedFromTimestamp(){
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return static_cast<unsigned int>(timestamp.count());
    }

    mt19937 gen;
};