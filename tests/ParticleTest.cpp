#include "../classes/Particle.h"
#include "../classes/Momentum.h"
#include "../classes/Coords.h"
#include <iostream>

using namespace std;

int main(void)
{
    
    Momentum A(1,3.2,4);
    Momentum B(5,3.1,1,eCoordinateSystem::spherical);

    Coords pos(1,2,3.3);
    int id=0;
    
    A.Print();
    B.Print();
    
    Particle part1(pos, B, id);
    Particle part2(1,2,3,2,1,1,1,eCoordinateSystem::carthesian);
    Particle part3(pos[0],pos[1],pos[2],B.GetSpherical()[0],B.GetSpherical()[1],B.GetSpherical()[2],2);
    
    part1.Print();
    part2.Print();
    part3.Print();
        
}
