#include <iostream>
#include "../Coords.h"
#include "../Plane.h"
#include "../Particle.h"
#include "../Disk.h"

using namespace std;

int main (int argc, char *argv[])
{
    Coords s1(0,0,1);
    Coords nvec1(1,1,1);
    
    Disk d1;
    d1.Print();
    d1.SetDisk(s1, nvec1, 2);
    d1.Print();
    
    cout<<"\nParticle";
    Particle part(0,0.,2.,-1.,-1.,-10.,0,eCoordinateSystem::carthesian);
    part.Print();
    
    cout<<"\nHits disk? "<<d1.HitsDisk(part)<<endl;
    
    cout<<"\nHit position:"<<endl;
    d1.GetHitPosition().Print();
    
    cout<<"\nDisk: changing normal vec direction"<<endl;
    d1.ChangeNormalVecDirection();
    d1.Print();
    
    cout<<"\nHits disk? "<<d1.HitsDisk(part)<<endl;
    
    cout<<"\nHit position:"<<endl;
    d1.GetHitPosition().Print();
        
    return 0;
}
