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

        this->tours.clear();
        for(int i = 0; i < this->N; ++i){
            Tour tour = this->NN(i);
            
            double L = apply_2opt(tour);
            this->tours.push_back(tour);
        }

        sort(this->tours.begin(), this->tours.end());

        double sum = 0;
        double s_sum = 0;
        int n = this->tours.size();
        for(int i = 0; i < n; ++i){
            sum += this->tours.at(i).L;
            s_sum += this->tours.at(i).L*this->tours.at(i).L;
        }
        double ave = sum/n;
        double std_dev = sqrt(s_sum/n - ave*ave);

        cout << "min:" << this->tours.at(0).L << " max:" << this->tours.at(n-1).L << " ave:" << ave << " std_dev:" << std_dev << "\n";
        this->solution = this->tours.at(0);
    }

};

