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
#include "AS_TSP.hpp"


using namespace std;

#pragma once


class Solver_MMAS : public Solver_AS{
private:
    double t_min;
    double t_max;
public:
    Solver_MMAS(vector< vector<double> > D, double t_min, double t_max, int steps = 1000, double alpha = 1, double beta = 2, double rho = 0.5)
    :Solver_AS( D, steps, alpha, beta, rho){
        this->t_max = t_max;
        this->t_min = t_min;


    }

    void set_Tau0(){
        this->tau0 = (double)1/(this->rho*calc_Lnn());
        this->T.assign(this->N, vector<double>(this->N, this->tau0));
    }

    virtual void solve(){
        int t = 0;
        while(t < this->steps){
            this->tours.clear();
            this->ants_T.assign(this->N, vector<double>(this->N, 0));
            for(int i = 0; i < this->M; ++i){
                int start = i%this->N;
                Tour tmp = generate_Tour(start);
                apply_2opt(tmp);
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

        Tour t = this->tours.at(0);
        Solver_AS::add_Tau(t);

        for(int i = 0; i < this->N; ++i)
            for(int j = 0; j < this->N; ++j)
                this->T[i][j] = (1-this->rho)*this->T[i][j] + this->ants_T[i][j];

    }


    double  Thresholding(double x){
        return (x > this->t_max)?t_this->t_max:(x < this->t_min)?this->t_min:x;
    }




};