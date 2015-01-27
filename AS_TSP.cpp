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
    int seeds[10] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
    
    vector<string> filename;
    filename.push_back("eil51");
    filename.push_back("pr76");
    filename.push_back("rat99");
    filename.push_back("kroA100");
    filename.push_back("ch130");


    for(int i = 0; i < filename.size(); ++i){
        double sum, sq_sum;
        int best_j = 0;
        int best_L = 100000000;
        vector<Tour> best_tours;
        sum = 0;
        sq_sum = 0;



        stringstream ss;
        ss.str("");
        ss.clear(stringstream::goodbit);
        ss << "benchmark_problem\\" << filename.at(i).c_str() << ".tsp";
        cout << ss.str() << "\n";
        TSP_Problem p(ss.str());

        for(int j = 0; j < 10; ++j){
            srand(seeds[j]);
            
            Solver_AS solver(p.get_D(), 1000, 1, 4);
    
            
            solver.solve();
            double L = solver.get_Solution().L;
            sum += L;
            cout << " " << L << "\n";
            sq_sum += L*L;

            if(L < best_L){
                best_tours = solver.get_Best_Tours();
                best_j = j;
                best_L = L;             
            }

            
            
        }

        sum /= 10.0;
        sq_sum /= 10.0;

        cout << "  best seed:" << seeds[best_j] << "\n";
        cout << "  best L:" << best_L << "\n";
        cout << "  mean:" << sum << "\n"; 
        cout << "  variance:" << sq_sum - sum*sum << "\n";

        
        ss.str("");
        ss.clear(stringstream::goodbit);
        ss << filename.at(i).c_str() << ".csv";
        ofstream ofs(ss.str().c_str());

        ofs << best_tours.at(0).L;
        for(int k = 1; k < best_tours.size() - 900; ++k)
            ofs << "," << best_tours.at(k).L;

        p.out_Tour(best_tours.at( best_tours.size()-1 ));


        

    }


    return 0;
}