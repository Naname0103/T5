#include <iostream>


using namespace std;

class super{

    
public:

    super(){
        set();
    }


    virtual void set(){
        cout << "set_super" << "\n";
    }


};

class sub : public super{

    sub():super(){
        set();
    }


    virtual void set(){
        cout << "set_sub" << "\n";
    }


};




int main(){
    super s();



    return 0;
}