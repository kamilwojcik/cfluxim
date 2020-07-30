#include <iostream>
#include "../classes/Coords.h"

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
    
    cout<<"\nvector product v3 of v1 and v2 (carthesian again)"<<endl;
    v2.SetSystem(eCoordinateSystem::carthesian);
    Coords v3=vectorProduct(v1,v2);
    v3.Print();
    
    cout<<"\nTriple product: "<<tripleProduct(v1,v2,v3)<<endl;
    
    
    cout<<"\nDistance between p1=(1,-3,0) and p2=(-9,8,5):"<<endl;
    Coords p1(1,-3,0);
    Coords p2(-9,8,5);
    cout<<distance(p1,p2)<<"\nand distance between p2 and p1: "<<distance(p2,p1)<<endl;
    
    Coords minus_p1=-p1;
    cout<<"\n-p1: "<<endl;
    minus_p1.Print();
    
    Coords p1p2=p1+p2;
    cout<<"p1 + p2: "<<endl;
    p1p2.Print();
    
    Coords p1_minus_p2 = p1-p2;
    cout<<"p1 - p2: "<<endl;
    p1_minus_p2.Print();
    
    cout<<"\nThe same in spherical:"<<endl;
    Coords p1s=carthesianToSpherical(p1);
    Coords p2s=carthesianToSpherical(p2);
    cout<<"p1s is p1 in spherical: "<<endl;
    p1s.Print();
    cout<<"p2s is p2 in spherical: "<<endl;
    p2s.Print();
    cout<<"p2s to carthesian "<<endl;
    sphericalToCarthesian(p2s).Print();
    cout<<"-p2s"<<endl;
    (-p2s).Print();
    cout<<"-p2s to carthesian: "<<endl;
    sphericalToCarthesian(-p2s).Print();
    
    
    
    Coords minus_p1s=-p1s;
    cout<<"\n-p1s: "<<endl;
    minus_p1s.Print();
    
    cout<<"\np1s + p2 - system mismatch"<<endl;
    (p1s+p2).Print();
    
    cout<<"p1 + p2s - system mismatch"<<endl;
    (p1+p2s).Print();
    
    cout<<"\np1s + p2s"<<endl;
    (p1s+p2s).Print();
    cout<<"p1s + p2s in carthesian:"<<endl;
    sphericalToCarthesian(p1s+p2s).Print();
    
    cout<<"\np1s - p2s"<<endl;
    (p1s-p2s).Print();
    cout<<"p1s - p2s in carthesian:"<<endl;
    sphericalToCarthesian(p1s-p2s).Print();
    
    cout<<"\nMultiplying by a scalar"<<endl;
    cout<<"p1: ";
    p1.Print();
    cout<<"p1*2: ";
    (p1*2.).Print();
    cout<<"2*p1: ";
    (2*p1).Print();
    
    cout<<"\np1s: ";
    p1s.Print();
    cout<<"p1*2: ";
    (p1s*2.).Print();
    
    
    
    return 0;
}
