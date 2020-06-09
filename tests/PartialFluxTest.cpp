#include "../PartialFlux.h"
#include <iostream>

using namespace std;

int main(void)
{
    PartialFlux dflux;
    
    dflux.Print();
    
    cout<<"\nFlux value: 1000:"<<endl;
    dflux.SetFluxValue(1000);
    dflux.Print();
       
    cout<<"\nTheta range: (0,1):"<<endl;
    dflux.SetThetaRange(0, 1);
    dflux.Print();
    
    cout<<"\nPhi range: (3.1415927, 6.2831853):"<<endl;
    dflux.SetPhiRange(3.1415927, 6.2831853);
    dflux.Print();
    
    cout<<"\nSet area: 1, 0:"<<endl;
    dflux.SetArea(1, 0);
    dflux.Print();
    
    cout<<"\nSet area: 1, 1.0471976:"<<endl;
    dflux.SetArea(1, 1.0471976);
    dflux.Print();
    
    cout<<"\nSet area: 1, 1.0471976:"<<endl;
    dflux.SetArea(1, 1.0471976);
    dflux.Print();
    
    cout<<"\nTheta range: (0,1):"<<endl;
    dflux.SetThetaRange(1.0471976, 2.0471976);
    dflux.Print();
    
    cout<<"\nPID = 5:"<<endl;
    dflux.SetPID(5);
    dflux.Print();
    
    cout<<"\nFilename:"<<endl;
    dflux.SetCumulDistFilename("filename");
    dflux.Print();
    
    
    return 0;
}
