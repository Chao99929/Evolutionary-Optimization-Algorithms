#define PROBLEM_H

#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>

using namespace std;

typedef struct Bound{
        double _lower;
        double _upper;
}_Bound;

class Problem{
public:
    
    
    double Run(int, vector<double>);
    
    _Bound GetBound(int);
    
private:
    double rand_double(double min, double max);
    double Sphere_F1(vector<double> x);//1
    double Schwefel_F2(vector<double> x);//2
    double Schwefel_F3(vector<double> x);//3
    double Schwefel_F4(vector<double> x);//4
    double Rosenbrock_F5(vector<double> x);//5 execute error
    double Step_F6(vector<double> x);//6 execute error
    double QuarticWithNoise_F7( vector<double> x);//7 execute error
    //F8 minimum !=0
    double Schwefel_F8(vector<double> x);//8
    double Rastrigin_F9(vector<double> x);//9
    double Ackley_F10(vector<double> x);//10
    double Weierstrass(vector<double> x );//
    double Griewank_F11(vector<double> x);//11 execute error
    double Penalized_F12(vector<double> x);//12
    double Penalized_F13(vector<double> x);//13

    unsigned int generateSeedFromTimestamp(){
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return static_cast<unsigned int>(timestamp.count());
    }
    mt19937 gen;



};

double Problem::Run(int flag, vector<double> x){
    double Fitness;
    switch (flag){
        case 1:
            Fitness = Sphere_F1(x);
            break;

        case 2:
            Fitness = Schwefel_F2(x);
            break;

        case 3:
            Fitness = Schwefel_F3(x);
            break;
        case 4:
            Fitness = Schwefel_F4(x);
            break;

        case 5:
            Fitness = Rosenbrock_F5(x);
            break;

        case 6:
            Fitness = Step_F6(x);
            break;
        case 7:
            Fitness = QuarticWithNoise_F7(x);
            break;

        case 8:
            Fitness = Schwefel_F8(x);
            break;

        case 9:
            Fitness = Rastrigin_F9(x);
            break;

        case 10:
            Fitness = Ackley_F10(x);
            break;

        case 11:
            Fitness = Griewank_F11(x);
            break;

        case 12:
            Fitness = Penalized_F12(x);
            break;

        case 13:
            Fitness = Penalized_F13(x);
            break;


    
    default:
        cout<<"Input error"<<endl;
        break;
    }
    return Fitness;
}

_Bound Problem::GetBound(int flag){
    _Bound bound;
    bound._lower = -100;
    bound._upper = 100;
    
    switch (flag)
    {
    case 1:
        bound._lower = -100;
        bound._upper = 100;
        break;

    case 2:
        bound._lower = -10;
        bound._upper = 10;
        break;
    
    case 3:
        bound._lower = -100;
        bound._upper = 100;
        break;
    
    case 4:
        bound._lower = -100;
        bound._upper = 100;
        break;

    case 5:
        bound._lower = -30;
        bound._upper = 30;
        break;

    case 6:
        bound._lower = -100;
        bound._upper = 100;
        break;
    
    case 7:
        bound._lower = -1.28;
        bound._upper = 1.28;
        break;

    case 8:
        bound._lower = -500;
        bound._upper = 500;
        break;

    case 9:
        bound._lower = -5.12;
        bound._upper = 5.12;
        break;

    case 10:
        bound._lower = -32;
        bound._upper = 32;
        break;
    
    case 11:
        bound._lower = -600;
        bound._upper = 600;
        break;

    case 12:
        bound._lower = -50;
        bound._upper = 50;
        break;

    case 13:
        bound._lower = -50;
        bound._upper = 50;
        break;


    default:
        break;
    }
    
    return bound;
}



double  Problem::Ackley_F10(vector<double> x) {
    double a = 20.0;
    double b = 0.2;
    double d = 2 * M_PI;
    int dim = x.size();

    double sum1 = 0.0;
    double sum2 = 0.0;

    for (int i = 0; i < dim; ++i) {
        sum1 += x[i] * x[i];
        sum2 += cos(d * x[i]);
    }
    

    return -a * exp(-b * sqrt(sum1 / dim)) - exp(sum2 / dim) + a + exp(1);
}

double Problem::Sphere_F1(vector<double> x)
{
	double result=0.0;
	for (int i=0; i<x.size(); ++i) {
		result += x[i]*x[i];
	}
	return result;
}

inline double Problem::Schwefel_F2(vector<double> x)
{
    double num = 0;
    for(int i=0; i<x.size(); i++){
        num += floor(x[i]+0.5) * floor(x[i]+0.5);
    }
    return num;
}

inline double Problem::Schwefel_F8(vector<double> x)
{
    double num = 0;
    for (int i=0; i<x.size(); i++){
        num += -x[i]*sin(sqrt(abs(x[i])));
    }
    num += x.size()*418.98288727243369;
    return num;
}

double Problem::Rastrigin_F9(vector<double> x)
{
    double result;
	for (int i=0; i<x.size(); ++i) {
		result += (x[i]*x[i] - 10.0*cos(2.0*M_PI*x[i]) + 10.0);
	}
	return result;
}

double Problem::Weierstrass(vector<double> x)
{
	double result, sum, sum2;
    result=sum=sum2=0;
    double a=0.5;
    double b=3.0;
	int k_max(20);

	for (int j=0; j<=k_max; ++j) {
		sum2 += pow(a,j)*cos(2.0*M_PI*pow(b,j)*(0.5));
	}
	for (int i=0; i<x.size(); ++i) {
		sum = 0.0;
		for (int j=0; j<=k_max; ++j) {
			sum += pow(a,j)*cos(2.0*M_PI*pow(b,j)*(x[i]+0.5));
		}
		result += sum;
	}
	return result - sum2*x.size();
}

double Problem::Griewank_F11(vector<double> x)
{
    double num = 0;
    double t1, t2;
    t1 = t2 = 0;
    for (int i=0; i<x.size(); i++){
        t1 += x[i]*x[i];
        if (i==0){
            t2 += cos(x[i]/sqrt(i+1));
        }
        else{
            t2 *= cos(x[i]/sqrt(i+1));
        }
    }
    num = t1/4000 - t2 + 1;
    return num;
}

inline double Problem::Penalized_F12(vector<double> x)
{
    double pi = 3.14159265358979323846;
    double num = 0;

    num = 10 * sin(pi * (1 + (x[0] + 1) / 4)) * sin(pi * (1 + (x[0] + 1) / 4));

    for (int i = 0; i < x.size() - 1; ++i) {
        double yi = 1 + (x[i] + 1) / 4;
        double yi_next = 1 + (x[i + 1] + 1) / 4;
        num += (yi - 1) * (yi - 1) * (1 + 10 * sin(pi * yi_next) * sin(pi * yi_next));
    }

    double yD = 1 + (x[x.size() - 1] + 1) / 4;
    num += (yD - 1) * (yD - 1);

    // 懲罰項
    for (int i = 0; i < x.size(); ++i) {
        double xi = x[i];
        if (xi > 10) {
            num += 100 * pow(xi - 10, 4);
        } else if (xi < -10) {
            num += 100 * pow(-xi - 10, 4);
        }
    }

    return pi / x.size() * num;
}

inline double Problem::Penalized_F13(vector<double> x)
{

        double pi = 3.14159265358979323846;
        double num = 0;

        num = 10 * sin(pi * (1 + (x[0] + 1) / 4)) * sin(pi * (1 + (x[0] + 1) / 4));

        for (int i = 0; i < x.size() - 1; ++i) {
            double yi = 1 + (x[i] + 1) / 4;
            double yi_next = 1 + (x[i + 1] + 1) / 4;
            num += (yi - 1) * (yi - 1) * (1 + 10 * sin(pi * yi_next) * sin(pi * yi_next));
        }

        double yD = 1 + (x[x.size()* - 1] + 1) / 4;
        num += (yD - 1) * (yD - 1);

        // 懲罰項
        for (int i = 0; i < x.size(); ++i) {
            double xi = x[i];
            if (xi > 10) {
                num += 100 * pow(xi - 10, 4);
            } else if (xi < -10) {
                num += 100 * pow(-xi - 10, 4);
            }
        }

        return pi / x.size() * num;
}

double Problem::Schwefel_F3(vector<double> x)
{
	double sum1, sum2;
    sum1=sum2=0.0;

	for (int i=0; i<x.size(); ++i) {
		sum2 = 0.0;
		for (int j=0; j<=i; ++j) {
			sum2 += x[j];
		}
		sum1 += sum2*sum2;
	}
	return sum1;
}

double Problem::Schwefel_F4(vector<double> x)
{
    double max = 0.0;

    for( int i=0; i<x.size(); i++){
        if(abs(x[i]) > max)
            max = abs(x[i]);
    }
    return max;
}

double Problem::Rosenbrock_F5(vector<double> x)
{
	double result = 0.0;

	for (int i=0; i<x.size()-1; ++i) {
		result += 100.0*pow((x[i]*x[i]-x[i+1]),2.0) + 1.0*pow((x[i]-1.0),2.0);
	}
	return result;
}

double Problem::Step_F6(vector<double> x)
{
    double sum1 = 0.0;

    for( int i=0; i<x.size(); i++){
        sum1 += pow( (x[i]+0.5), 2.0);
    }
    return sum1;
}

double Problem::QuarticWithNoise_F7(vector<double> x)
{
    
    double num = 0;
    for(int i=0; i<x.size(); i++){
        num += i*(x[i]*x[i]*x[i]*x[i]);
    }
    double tmp=0;
    do {
        tmp = rand_double(0,1);
    } while (tmp==1);
    num += tmp;
    return num;

}



double Problem::rand_double(double min, double max){
    if (min > max){
        // return error
        int temp = min;
        min = max;
        max = temp;
    }
    uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}