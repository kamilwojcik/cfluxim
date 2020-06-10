#include <iostream>
#include "../Coords.h"

using namespace std;

int main (int argc, char *argv[])
{
    Coords a(1,3,-4);
    Coords b(2,3,4,eCoordinateSystem::spherical);
    
    a.Print();
    a.Move(0,1,2);
    a.Print();
    b.Print();
    a.SetSystem(eCoordinateSystem::spherical);
    a.Print();
    std::cout<<"a[1]="<<a[1]<<std::endl;
    b.SetSystem(eCoordinateSystem::carthesian);
    a=b;
    a.Print();
    
    Coords c;
    c.Print();
    cout<<"Print a: "<<endl;
    a.Print();
    cout<<"copy of a: "<<endl;
    Coords d(a);
    d.Print();
    
    cout<<"move b and set to spherical: "<<endl;
    b.Move(-3,4,-1);
    b.SetSystem(eCoordinateSystem::spherical);
    b.Print();
    
    cout<<"d=b; b: "<<endl;
    d=b;
    d.Print();
    
    Coords e(1,1,1.41421);
    cout<<"e: "<<endl;
    e.Print();
    
    Coords f=carthesianToSpherical(e);
    f.Print();
    
    f.SetCoords(2,0.785398,0.785398);
    f.Print();
    Coords h=sphericalToCarthesian(f);
    h.Print();
    
    eCoordinateSystem system = f.GetCoordinateSystem();
    if (system == eCoordinateSystem::spherical) cout<<"Spherical"<<endl;

    cout<<"\nScalar product tests"<<endl;
    Coords v1(-1,-2,0);
    v1.Print();
    Coords v2(5,-8,10);
    v2.Print();
    cout<<"v1 dot v2: "<<scalarProduct(v1,v2)<<endl;
    cout<<"\n With coordinate system mismatch:"<<endl;
    v2.SetSystem(eCoordinateSystem::spherical);
    v1.Print();
    v2.Print();
    cout<<"v1 (carthesian) dot v2 (spherical): "<<scalarProduct(v1,v2)<<endl;
    
    return 0;
}
