#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "TSP_Problem.hpp"

using namespace std;

#pragma once


double randdouble(){

    return rand()/(RAND_MAX+1.0);
}

int randint(int min, int max){

   return (int)((max-min+1)*randdouble() + min);
}


struct Tour{

    vector<int> tour;
    double L;
};



class TSP_Solver{

protected:
    int N;
    vector< vector<double> > D;
    vector<Tour> tours;
    Tour solution;


public:
    TSP_Solver( ){
    }
    ~TSP_Solver( ){
    }

    TSP_Solver( vector< vector<double> > D){
        this->D = D;
        this->N = D.size();
        this->solution = NN();
        min_L = calc_L(this->solution);
        
    }



    Tour NN(int start = 0){
        vector<int> index;
        Tour t;
        int i = 0;
        for(i = 0;i < this->N; ++i)
            index.push_back(i);
        t.tour.clear();
        t.tour.push_back( start);
        index.erase(index.begin() + start);

        i = 0;
        while(!index.empty()){
            double min = 999999;
            int next = 0;
            for(int j = 0; j < index.size(); ++j){
                double d = this->D[ data.at(i) ][index.at(j)];
                if(min > d){
                    min = d;
                    next = j;
                }
            }

            t.tour.push_back( index.at(next) );
            index.erase(index.begin() + next);
            ++i;
        }
        return data;
    }

    double apply_2opt(vector<int> &tour){
        while(true){
            int min_j, min_k;
                double diff = 0;
                for(int j = 0; j < tour.size()-1; ++j){
                    for(int k = j+2; k < tour.size(); ++k){

                        double d1 = this->D[ tour.at(j)  ][ tour.at(j+1) ] + this->D[ tour.at(k)  ][ tour.at( (k+1)%tour.size()) ];
                        double d2 = this->D[ tour.at(j)  ][ tour.at(k) ] + this->D[ tour.at(j+1)  ][ tour.at( (k+1)%tour.size()) ];
    
                        if(d1 > d2){
                            double tmp_diff =d1 - d2;
                            if(diff < tmp_diff){
                                min_j = j;
                                min_k = k;

                                diff = tmp_diff;
                            }

                        }


    
                    }
                }
    
                if(diff > 0){
                    reverse(tour.begin()+min_j+1, tour.begin()+min_k+1);
                    // print_Data();
                }
                else
                    break;
        }


       return  calc_L( tour);
    }



    double calc_L( Tour &_data){
        double _L = 0;
        for(int i = 0; i < _data.tour.size(); ++i){
            
            _L += (int)( this->D[  _data.tour.at(i)  ][  _data.tour.at( (i+1)%_data.tour.size())  ] + 0.5);
        }
        _data.L = _L;
        return _L;

    }



    virtual void solve() = 0;

    Tour get_Solution(){
        return this->solution;
    }



    void print_Soltion(){


        cout << this->min_L << "\n";
        cout << this->solution.tour.at(0);
        cout << ","<< this->solution.tour.at(1);
        for(int i = 2; i < this->solution.tour.size(); ++i){
            cout << ","<<this->solution.tour.at(i);

        }

        cout << "\n";

    }

    void print_Tour(){

        cout << this->solution.tour.at(0);
        cout << "-(" << this->D[  this->solution.tour.at(0)  ][  this->solution.tour.at(1)  ] << ")->";
        cout << this->solution.tour.at(1);
        for(int i = 2; i < this->solution.tour.size(); ++i){
            cout << "-(" << this->D[  this->solution.tour.at(i-1)  ][  this->solution.tour.at(i)  ] << ")->";
            cout <<this->solution.tour.at(i);

        }

        cout << "\n";

    }



};
