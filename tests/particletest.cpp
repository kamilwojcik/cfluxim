#include "fluxsym.h"
#include <iostream>

using namespace std;

int main(void)
{
    
    Momentum A(1,3.2,4);
    Momentum B(5,3.1,1,eCoordinateSystem::polar);

    Coords pos(1,2,3.3);
    int id=0;
    
    A.Print();
    B.Print();
    
    Particle part1(pos, B, id);
    Particle part2(1,2,3,2,1,1,1,eCoordinateSystem::carthesian);
    Particle part3(pos[0],pos[1],pos[2],B.GetPolar()[0],B.GetPolar()[1],B.GetPolar()[2],2);
    
    part1.Print();
    part2.Print();
    part3.Print();
        
}
