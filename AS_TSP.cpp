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
    srand(17);
    vector<string> filename;
    filename.push_back("eil51");
    // filename.push_back("pr76");
    // filename.push_back("rat99");
    // filename.push_back("kroA100");
    // filename.push_back("ch130");


    for(int i = 0; i < filename.size(); ++i){
        stringstream ss;
        ss.str("");
        ss.clear(stringstream::goodbit);
        ss << "benchmark_problem\\" << filename.at(i).c_str() << ".tsp";
        cout << ss.str() << "\n";
        TSP_Problem p(ss.str());
        Solver_AS solver(p.get_D(), 1000);

        
        solver.solve();

        ss.str("");
        ss.clear(stringstream::goodbit);
        ss << filename.at(i).c_str() << ".csv";
        ofstream ofs(ss.str().c_str());

        vector<Tour> ts = solver.get_Tours();
        ofs << ts.at(0).L;
        for(int j = 1; j < ts.size(); ++j)
            ofs << "," << ts.at(j).L;

        p.out_Tour(solver.get_Solution());
    }


    return 0;
}