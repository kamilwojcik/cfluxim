#include "fluxsym.h"
#include <iostream>

using namespace std;

int main(void)
{
    
    Momentum A(1,3.2,4);
    Momentum B(5,3.1,0.3,eCoordinateSystem::polar);
    Momentum C;
    Momentum D=B;
    
    cout<<"A: "<<endl;
    A.Print();
    A.PrintPolar();
    A.PrintCarthesian();
    
    cout<<"B: "<<endl;
    B.Print();
    
    cout<<"C: "<<endl;
    C.Print();
    
    cout<<"D: "<<endl;
    D.Print();
    
    D=A;
    cout<<"D: "<<endl;
    D.Print();
    
    
    Coords e(3,2,1.1,eCoordinateSystem::polar);
    cout<<"e: "<<endl;
    e.Print();
    
    Momentum E(e);
    cout<<"E: "<<endl;
    E.Print();
    
    cout<<"\nPrint momentum and position (getters test)"<<endl;
    Coords h=E.GetCarthesian();
    h.Print();
    Coords m=E.GetPolar();
    m.Print();
    
    cout<<"\nE second element: "<<E.GetCarthesian()[1]<<endl;
    
    return 0;
}
