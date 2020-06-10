#include <iostream>
#include "../Coords.h"
#include "../Plane.h"

using namespace std;

int main (int argc, char *argv[])
{
    cout<<"Planr M:"<<endl;
    Plane M(1,2,2.5,4);
    M.Print();
    
    cout<<"\nPlane P:"<<endl;
    Plane P(0,0,0,1);
    P.Print();
    
    cout<<"\nChanging normal vector direction for M:"<<endl;
    M.SetNormalVecDirection(false);
    M.Print();
    
    cout<<"Scalar products of normal vectors:"<<endl;
    cout<<"Plane N:"<<endl;
    Plane N(1,2,2.5,4);
    N.Print();
    cout<<"M and N normal vectors scalar product should be -11.25. It is: "<<scalarProduct(N.GetNormalVector(), M.GetNormalVector())<<endl;
    
    cout<<"Checking if planes are perpendicular (normal vectors scalar product = 0)"<<endl;
    P.Print();
    Plane R(6.4,-2,0,-5.1);
    R.Print();
    cout<<"M and N normal vectors scalar product: "<<scalarProduct(P.GetNormalVector(),R.GetNormalVector())<<endl; 
    
    cout<<"\nBelongsToPlane() test\n"<<endl;
    Coords point(1,1,1);
    point.Print();
    cout<<"Belongs to P? Answer: "<<P.BelongsToPlane(point)<<endl;
    point.SetCoords(3.14,64,0);
    point.Print();
    cout<<"Belongs to P? Answer: "<<P.BelongsToPlane(point)<<endl;
    
    
    
    return 0;
}
