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

class Solver_2opt : public TSP_Solver{

public:
    Solver_2opt( vector< vector<double> > D):TSP_Solver(D){
    }


    virtual void solve(){

        this->Ls.clear();
        this->tours.clear();
        for(int i = 0; i < this->N; ++i){
            vector<int> tour = this->NN(i);
            apply_2opt(tour);
            double L = calc_L(tour);
            if(this->min_L > L){
                this->min_L = L;
                this->solution = tour;
            }
            this->Ls.push_back(L);
        }

        sort(this->Ls.begin(), this->Ls.end());

        double sum = 0;
        double s_sum = 0;
        int n = this->Ls.size();
        for(int i = 0; i < n; ++i){
            sum += this->Ls.at(i);
            s_sum += this->Ls.at(i)*this->Ls.at(i);
        }
        double ave = sum/n;
        double std_dev = sqrt(s_sum/n - ave*ave);

        cout << "min:" << this->Ls.at(0) << " max:" << this->Ls.at(n-1) << " ave:" << ave << " std_dev:" << std_dev << "\n";
    }

};

