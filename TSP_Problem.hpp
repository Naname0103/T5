#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#pragma once

using namespace std;


inline string ExtractPathWithoutExt(const string &fn)
{
    string::size_type pos;
    if((pos = fn.find_last_of(".")) == string::npos){
        return fn;
    }
 
    return fn.substr(0, pos);
}


string ExtractFileName(const string &path, bool without_extension = true)
{
    string fn;
    string::size_type fpos;
    if((fpos = path.find_last_of("/")) != string::npos){
        fn = path.substr(fpos+1);
    }
    else if((fpos = path.find_last_of("\\")) != string::npos){
        fn = path.substr(fpos+1);
    }
    else{
        fn = path;
    }
 
    if(without_extension && (fpos = fn.find_last_of(".")) != string::npos){
        fn = fn.substr(0, fpos);
    }
 
    return fn;
}


class Position{
private:
    double x;
    double y;

public:
    Position(double x, double y){
        this->x = x;
        this->y = y;
    }

    double get_X(){
        return this->x;
    }
    double get_Y(){
        return this->y;
    }
    double set_X(double x){
        return this->x = x;
    }
    double set_Y(double y){
        return this->y = y;
    }

    Position operator +(Position p){
        return Position(this->x + p.get_X(), this->y + p.get_Y());
    }
    Position operator -(Position p){
        return Position(this->x - p.get_X(), this->y - p.get_Y());
    }

    double d(Position p){
        Position v = (*this-p);
        return sqrt(pow(v.get_X(),2) + pow(v.get_Y(),2));
    }

    void print(){
        cout << "(" << this->x << "," << this->y << ")" << "\n";
    }


};




struct Tour{

    vector<int> tour;
    double L;

    bool operator<(const Tour &right) const{
        return L < right.L;
    }
};



class TSP_Problem{

private:
    string file_name;
    string name;
    string type;
    string comment;
    int N;
    vector<Position> nodes;
    vector< vector<double> > D;

public:
    TSP_Problem( string file_name){
        this->file_name = file_name;
        load_File(file_name);


    }

    bool load_File(string file_name){

        ifstream ifs(file_name.c_str());
        if(!ifs)
            return false;
        string tag("");



        while(ifs >> tag && tag != "NODE_COORD_SECTION"){
            if(tag == "NAME:"){
                string n;
                ifs >> n;
                this->name = n;
            }
            else if(tag == "TYPE:"){
                string t;
                ifs >> t;
                this->type = t;
            }
            else if(tag == "COMMENT:"){
                char dummy;
                string c;
                getline(ifs, c);
                this->comment = c;
            }
            else if(tag == "DIMENSION:"){
                int n;
                ifs >> n;
                this->N = n;
            }
        }



        while(ifs >> tag && tag != "EOF"){
            double x,y;
            ifs >> x >> y;
            Position p(x,y);
            nodes.push_back(p);
        }


        for(int i = 0; i < this->nodes.size(); ++i){
            vector<double> tmp;
            for(int j = 0; j < this->nodes.size(); ++j){
                tmp.push_back(this->nodes.at(i).d(this->nodes.at(j)));
            
            }
            this->D.push_back(tmp);
        }



        return true;
    }

    void print_Properties(){
        cout << this->name << "\n";
        cout << this->type << "\n";
        cout << this->comment << "\n";
        cout << this->N << "\n";
        for(int i = 0; i < this->nodes.size(); ++i)
            this->nodes.at(i).print();

    }


    void out_Tour(Tour t){
        vector<int> tour = t.tour;
        string file_name = (ExtractPathWithoutExt(this->file_name)+".opt.tour");

        ofstream ofs( file_name.c_str() );
        ofs << "NAME: " << ExtractFileName(file_name, false).c_str() << "\n";
        ofs << "COMMENT: " << "\n";
        ofs << "TYPE: " << "TOUR" << "\n";
        ofs << "DIMENSION: " << this->N << "\n";
        ofs << "TOUR_SECTION" << "\n";

        for(int i = 0; i < tour.size(); ++i)
            ofs << tour.at(i)+1 << "\n";

        ofs << -1 << "\n";
        ofs << "EOF";



    }


    void print_D(){
        for(int i = 0; i < this->nodes.size(); ++i){
            cout << this->D[i][0];
            for(int j = 1; j < this->nodes.size(); ++j){
                cout << "," << this->D[i][j];
            }
            cout << "\n";
        }
    }


    vector< vector<double> > get_D(){
        return this->D;
    }



};
