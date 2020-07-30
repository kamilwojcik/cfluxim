#include <iostream>
#include "../classes/Coords.h"
#include "../classes/Plane.h"
#include "../classes/Rectangle.h"
#include "../classes/Particle.h"

using namespace std;

int main (int argc, char *argv[])
{
    cout<<"Plane z=10:"<<endl;
    Coords v1(-2,2,10);
    Coords v2(2,2,10);
    Coords v3(2,-2,10);
    Coords v4(-2,-2,10);
    
    Rectangle r0(v1,v2,v3,v4);
    cout<<endl;
    
    r0.Print();
    
    cout<<"\nRelative (2,3,0) to absolute"<<endl;
    Coords rel(2,3,0);
    Coords abs=r0.RelativeToAbsolute(rel);
    abs.Print();
    
    cout<<"Back to relative"<<endl;
    rel=r0.AbsoluteToRelative(abs);
    rel.Print();
    
    cout<<"\ndefault:"<<endl;
    Rectangle r2;
    r2.Print();
    
    cout<<"\nUnsupported plane:"<<endl;
    Coords v5(-2,-2,0);
    r2.SetRectangle(v1,v2,v3,v5);
    cout<<"print plane:"<<endl;
    r2.Print();
    
    cout<<"\nSet Default"<<endl;
    r2.SetDefault();
    r2.Print();
    
    cout<<"\nHit position in the default rectangle"<<endl;
    cout<<"Particle#1:"<<endl;
    Particle p1;
    p1.SetPosition(0,0,1);
    p1.SetMomentum(5.000,0,-10,eCoordinateSystem::carthesian);
    p1.SetPID(1);
    p1.Print();
    
    cout<<"Hits the rectangle: "<<r2.HitsRectangle(p1)<<endl;
    cout<<"Hit position: ";
    r2.GetHitPosition().Print();
    
    
    return 0;
}
