#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <random>
using namespace std;

typedef struct particle{
    vector<double> solution;
    double fitness;
    vector<double> velocity;
    vector<double> agent_best;
    double agent_best_fitness;
};

template <typename T, typename U> inline T Random_with_Normaldis(T C, T S, U &RG){
    normal_distribution<T> P(C, S);
    return P(RG);
}
template <typename T, typename U> inline T Random_with_Cauchydis(T C, T S, U &RG){
    cauchy_distribution<T> P(C, S);
    return P(RG);
}
template <typename T, typename U> inline T RandomReal_with_uniform(T BMin, T BMax, U &RG){
    uniform_real_distribution<T> R(BMin, BMax);
    return R(RG);
}

class PSO{
    public:
        void RunAlg(int, int, int, int, double, double, double, double, double);
    private:
    int Trun;
    int mnfes;
    int nfes;
    int p_size;
    int dim;
    double c1;
    double c2;
    double w;
    double v_min;
    double v_max;

    vector<particle> population;
    vector<double> global_best_solution;
    double global_best_fitness = DBL_MAX;

    mt19937_64 generator;

    void Initialization();
    void UpdateVelocity();
    void UpdatePosition();
    void Evaluate( vector<double>&, double& );
    void Reset();
    void BoundarySolution( double& );
    void BoundaryVelocity( double& );

};

void PSO::RunAlg( int run, int eva, int pop_size, int dimension, double C1, double C2, double omaga, double V_min, double V_max){
    Trun = run;
    mnfes = eva;
    p_size = pop_size;
    dim = dimension;
    c1 = C1;
    c2 = C2;
    w = omaga;
    v_min = V_min;
    v_max = V_max;

    double result = 0.0;
    for( int crun = 0; crun < Trun; crun++ ){

        Reset();
        Initialization();

        while( nfes < mnfes ){
            UpdateVelocity();
            UpdatePosition();
        }

        cout << "Run " << crun + 1 << ": " << global_best_fitness << endl;
        result += global_best_fitness;
    }

    cout << "Average fitness: " << result / Trun << endl;
}

void PSO::BoundarySolution( double& x ){

    if( x < -32.0 ) x = -32.0;
    if( x > 32.0 ) x = 32.0;

}

void PSO::BoundaryVelocity( double& v ){

    if( v < v_min ) v = v_min;
    if( v > v_max ) v = v_max;

}

void PSO::Reset(){

    nfes = 0;
    global_best_solution.assign( dim, 0.0 );
    global_best_fitness = DBL_MAX;

}

void PSO::Initialization(){

    population.resize( p_size );

    for( int i = 0; i < p_size; i++ ){

        population[i].solution.resize( dim );
        population[i].velocity.resize( dim );
        population[i].agent_best.assign( dim, 0.0 );
        population[i].agent_best_fitness = DBL_MAX;

        for( int j=0; j < dim; j++ ){
            population[i].solution[j] = RandomReal_with_uniform( -32.0, 32.0, generator );
            population[i].velocity[j] = RandomReal_with_uniform( v_min, v_max, generator );
        }
        Evaluate( population[i].solution, population[i].fitness );

        population[i].agent_best = population[i].solution;
        population[i].agent_best_fitness = population[i].fitness;
        if(population[i].fitness < global_best_fitness){
            global_best_solution = population[i].solution;
            global_best_fitness = population[i].fitness;
        }

    }

}

void PSO::Evaluate( vector<double>& solution, double& fitness ){

    // Ackley function
    const double a = 20.0;
    const double b = 0.2;
    const double c = 2.0 * M_PI;
    double sum1 = 0.0;
    double sum2 = 0.0;
    for( int i = 0; i < dim; i++ ){
        sum1 += solution[i] * solution[i];
        sum2 += cos(c * solution[i]);
    }
    fitness = -a * exp(-b * sqrt(sum1 / dim)) - exp(sum2 / dim) + a + exp(1.0);

    nfes++;
}

void PSO::UpdateVelocity(){

    for( int i = 0; i < p_size; i++ ){

        for( int j = 0; j < dim; j++ ){

            double r1 = RandomReal_with_uniform( 0.0, 1.0, generator );
            double r2 = RandomReal_with_uniform( 0.0, 1.0, generator );
            population[i].velocity[j] = w * population[i].velocity[j] + c1 * r1 * (population[i].agent_best[j] - population[i].solution[j]) + c2 * r2 * (global_best_solution[j] - population[i].solution[j]);

            // BoundaryVelocity( population[i].velocity[j] );

        }
    }

}

void PSO::UpdatePosition(){

    for( int i = 0; i < p_size; i++ ){
        for( int j=0; j<dim; j++ ){
            population[i].solution[j] += population[i].velocity[j];
            BoundarySolution( population[i].solution[j] );
        }
        Evaluate( population[i].solution, population[i].fitness );

        if( population[i].fitness < global_best_fitness ){
            global_best_solution = population[i].solution;
            global_best_fitness = population[i].fitness;
            if( population[i].fitness < population[i].agent_best_fitness ){
                population[i].agent_best = population[i].solution;
                population[i].agent_best_fitness = population[i].fitness;
            }
        }

    }

}
