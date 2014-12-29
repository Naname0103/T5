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
    vector< vector<double> > ants_T;

    int steps;
    vector<int> init_index;


public:
    Solver_AS( vector< vector<double> > D, int steps = 1000, double alpha = 1, double beta = 2, double rho = 0.5):TSP_Solver(D){
        this->alpha = alpha;
        this->beta = beta;
        this->M = 100;//this->N;
        this->rho = rho;
        this->steps = steps;
        set_Tau0();
  
        this->T.assign(this->N, vector<double>(this->N, this->tau0));
        this->P.assign(this->N, vector<double>(this->N, 0));
        this->ants_T.assign(this->N, vector<double>(this->N, 0));

        set_P();

        for(int i = 0; i < this->N; ++i)
            this->init_index.push_back(i);
    }

    void set_Tau0(){
        double t = 0;
        for(int i = 0; i < this->N; ++i){
            t += NN(i).L;
        }
        t/=(double)this->N;
        this->tau0 = (double)this->M/t;
    }



    void set_P(){
        for(int i = 0; i < this->N; ++i){
            for(int j = 0; j < this->N; ++j){
                this->P[i][j] = pow(this->T[i][j], alpha)*pow(1.0/this->D[i][j], beta);
            }
        }
    }


    virtual void solve(){
        int t = 0;
        while(t < this->steps){
            this->tours.clear();
            this->ants_T.assign(this->N, vector<double>(this->N, 0));
            for(int i = 0; i < this->M; ++i){
                int start = i%this->N;
                Tour tmp = generate_Tour(start);
                add_Tau(tmp);
                this->tours.push_back(tmp);
            }

            update_Tau();
            set_P();
            sort(this->tours.begin(), this->tours.end());
            if(this->solution.L > this->tours.at(0).L){
                this->solution = this->tours.at(0);
                t = 0;
            }else{
                ++t;
            }


            cout << this->tours.at(0).L << "\n";
        }

    }

    void update_Tau(){


        for(int i = 0; i < this->N; ++i)
            for(int j = 0; j < this->N; ++j)
                this->T[i][j] = (1-this->rho)*this->T[i][j] + this->ants_T[i][j];

    }

    void add_Tau( Tour t){

        for(int i = 0; i < this->N; ++i){
            this->ants_T[t.tour.at(i)][t.tour.at( (i+1)%this->N)] += 1.0/(double)t.L;  
        }

    }


    Tour generate_Tour(int start){
        Tour tmp;
        vector<int> index = this->init_index;
        tmp.L = 0;
        tmp.tour.push_back(start);
        index.erase(index.begin()+start);
        int prv = start;
        while(!index.empty()){
            int selected = select_City( prv, index);
            int nxt = index.at(selected);
            tmp.L += (int)(this->D[prv][nxt] + 0.5);
            tmp.tour.push_back(nxt);
            index.erase(index.begin() + selected);

            prv = nxt;

        }
        tmp.L += (int)(this->D[prv][start] + 0.5);


        return tmp;
    }

    int select_City(int prv, vector<int> index){
        double p_sum = 0;
        for(int i = 0; i < index.size(); ++i)
            p_sum += this->P[prv][index.at(i)];

        double r = randdouble();
        double tmp = 0;
        for(int i = 0; i < index.size(); ++i){
            if(tmp < r && r <= tmp+this->P[prv][index.at(i)]/p_sum )
                return i;
            tmp += this->P[prv][index.at(i)]/p_sum;
        }

        return 0;
    }


};