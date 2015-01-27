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

int main(){
    srand(171);
    vector<string> filename;
    filename.push_back("eil51");
    int beta[] = { 2,3,4,5};
  
    for(int i = 0; i < 4; ++i){
    stringstream ss;
    ss.str("");
    ss.clear(stringstream::goodbit);
    ss << "benchmark_problem\\" << filename.at(0).c_str() << ".tsp";
    cout << ss.str() << "\n";
    TSP_Problem p(ss.str());
    Solver_AS solver(p.get_D(), 1000, 1, beta[i]);
    
    solver.solve();
    cout << beta[i] << ":" << solver.get_Tours().at(0).L << "\n";

    }


    return 0;
}