#include <iostream>
#include <vector>
#include <iostream>
#include <cmath>

#include "../classes/Coords.h"
#include "../classes/Plane.h"
#include "../classes/Particle.h"
#include "../classes/Disk.h"
#include "../classes/Cylinder.h"

using namespace std;

int main (int argc, char *argv[])
{
    Coords s1(-1,0,2);
    Coords s2(1,0,2);
    
    Cylinder tpc(s1,s2,1);
    tpc.Print();
    
    Particle p1(-2,0,1.5,1,0,0,0,eCoordinateSystem::carthesian); //2 hits in walls, track parallel to the cylinder axis
    Particle p2(0,0,4,0,0,-1,0,eCoordinateSystem::carthesian); //2 hits in lateral surface
    Particle p3(0,1,3.5,0,0,-1,0,eCoordinateSystem::carthesian);
    Particle p4(-0.5,0,4,1,0,-1,0,eCoordinateSystem::carthesian);
    Particle p5(0,2,3,0,0,-2,0,eCoordinateSystem::carthesian);
    
    cout<<"\np1 - 2 hits in walls, track parallel to the cylinder axis "<<endl;
    p1.Print();
    cout<<"HitsCylinder: "<<tpc.HitsCylinder(p1)<<endl;
    vector<Coords> hits = tpc.GetHitPositions();
    cout<<"Hits: "<<hits.size()<<endl;
    for (auto i : hits) i.Print();
    
    cout<<"\np2 - vertical track, 2 hits in lateral area, x=0, y=0"<<endl;
    p2.Print();
    cout<<"HitsCylinder: "<<tpc.HitsCylinder(p2)<<endl;
    hits = tpc.GetHitPositions();
    cout<<"Hits: "<<hits.size()<<endl;
    for (auto i : hits) i.Print();
    
    cout<<"\np3 - one hit in lateral area, vertical track"<<endl;
    p3.Print();
    cout<<"HitsCylinder: "<<tpc.HitsCylinder(p3)<<endl;
    hits = tpc.GetHitPositions();
    cout<<"Hits: "<<hits.size()<<endl;
    for (auto i : hits) i.Print();
    
    cout<<"\np4 - two hits: one hit in lateral, one in wall"<<endl;
    p4.Print();
    cout<<"HitsCylinder: "<<tpc.HitsCylinder(p4)<<endl;
    hits = tpc.GetHitPositions();
    cout<<"Hits: "<<hits.size()<<endl;
    for (auto i : hits) i.Print();
    
    cout<<"\np5 - no hits"<<endl;
    p5.Print();
    cout<<"HitsCylinder: "<<tpc.HitsCylinder(p5)<<endl;
    hits = tpc.GetHitPositions();
    cout<<"Hits: "<<hits.size()<<endl;
    for (auto i : hits) i.Print();
    
    
    
    return 0;
}
