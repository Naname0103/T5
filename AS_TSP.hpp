#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "TSP_Problem.hpp"
#include "TSP_Solver.hpp"

using namespace std;

#pragma once

// class Ant{
// private:
//     int location;
//     double pheromone;
//     vector<int> tour;

// public:
//     Ant(int location){
//         this->location = location;
//         this->pheromone = 0;
//     }


//     void set_Tour( vector< vector<double> > D, vector< vector<double> > T){



//     }



// };



class Solver_AS : public TSP_Solver{
private:
    double alpha;
    double beta;
    double rho;
    double tau0;
    int M;
    vector< vector<double> > T;
    vector< vector<double> > P;

    int steps;
    vector<int> init_index;


public:
    Solver_AS( vector< vector<double> > D, int steps, double alpha = 1, double beta = 2, double rho = 0.5):TSP_Solver(D){
        this->alpha = alpha;
        this->beta = beta;
        this->M = this->N;
        this->rho = rho;
        this->steps = steps;
        set_Tau0();
        this->T.assign(this->N, vector<double>(this->N, this->tau0));
        this->P.assign(this->N, vector<double>(this->N, 0));
        set_P();

        for(int i = 0; i < this->N; ++i)
            init_index.push_back(i);
    }

    void set_Tau0(){
        double t = 0;
        for(int i = 0; i < this->N; ++i){

            NN(i);
            t += set_L();


        }
        t/=(double)this->N;
        this->tau0 = this->M/t;
    }


    void set_P(){
        for(int i = 0; i < this->N; ++i){
            for(int j = 0; j < this->N; ++j){
                this->P[i][j] = pow(this->T[i][j], alpha)*pow(1/this->D[i][j], beta);
            }
        }
    }

    

    virtual void update(){
        int t = 0;
        while(t < this->steps){
            this->Ls.clear();
            tours.clear();
            for(int i = 0; i < this->M; ++i){
                int start = 0;
                vector<int> tmp = generate_Tour(start);

                tours.push_back(tmp);
            }
            ++t;
        }


    }


    vector<int> generate_Tour(int start){
        vector<int> tmp;
        vector<int> index = this->init_index;

        tmp.push_back(start);
        index.erase(index.begin()+start);

        while(!index.empty()){




        }



        return 
    }

    int select_City(int location, vector<int> index){
        double p_sum = 0;
        for(int i = 0; i < index.size(); ++i)
            p_sum += this->P[location][index.at(i)];

        double r = randdouble();
        double tmp = 0;
        for(int i = 0; i < index.size(); ++i){
            if(tmp < r && r <= tmp+this->P[location][index.at(i)]/p_sum )
                return index.at(i);
            tmp += tmp+this->P[location][index.at(i)]/p_sum;
        }

        return 0;
    }


}