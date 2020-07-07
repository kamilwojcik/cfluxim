#include <iostream>
#include "../Coords.h"
#include "../Plane.h"
#include "../Rectangle.h"
#include "../Particle.h"

using namespace std;

int main (int argc, char *argv[])
{
    cout<<"Plane z=10:"<<endl;
    Coords upL0(-1,1,10);
    Coords doR0(1,-1,10);
    
    Rectangle r0(upL0, doR0);
    
    r0.Print();
    
    cout<<"\nPlane x=10:"<<endl;
    Coords upL1(10,3,0);
    Coords doR1(10,-3,-5);
    
    Rectangle r1(upL1, doR1);
    
    r1.Print();
    
    cout<<"\nRelative (2,3,0) to absolute in the x=10 rectangle"<<endl;
    Coords rel(2,3,0);
    Coords abs=r1.RelativeToAbsolute(rel);
    abs.Print();
    
    cout<<"Back to relative"<<endl;
    rel=r1.AbsoluteToRelative(abs);
    rel.Print();
    
    
    cout<<"\nMomentum transformation from absolute to YZ"<<endl;
    Momentum mom0(1,1,-10, eCoordinateSystem::carthesian);
    mom0.Print();
    cout<<"\nafter transformation"<<endl;
    Momentum mom1=r1.VecToRelative(mom0);
    mom1.Print();
    
    cout<<"\n...and back:"<<endl;
    r1.VecToAbsolute(mom1).Print();
    
    
    
    cout<<"\ndefault:"<<endl;
    Rectangle r2;
    r2.Print();
    
    cout<<"\nUnsupported plane:"<<endl;
    Coords upL2(5,3,0);
    Coords doR2(0,-3,5);
    r2.SetRectangle(upL2, doR2);
    cout<<"print"<<endl;
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
    
    cout<<"\nHit position in the default rectangle x:0-1, y:0-1, z:0"<<endl;
    Coords upL3(0,1,0);
    Coords doR3(1,0,0);
    Rectangle r3(upL3, doR3);
    r3.Print();
    
    cout<<"Particle#1:"<<endl;
    p1.Print();
    
    cout<<"Hits the rectangle: "<<r3.HitsRectangle(p1)<<endl;
    cout<<"Hit position: ";
    r3.GetHitPosition().Print();
    cout<<"Hit position (relative): ";
    r3.AbsoluteToRelative(r3.GetHitPosition()).Print();
    
    return 0;
}
