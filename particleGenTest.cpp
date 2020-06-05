#include "cfluxim.h"
#include <iostream>

using namespace std;

int main(void)
{
    
    ParticleGenerator pGen;
    pGen.Print();
    pGen.SetDescription("Test");
    pGen.Print();
    
    
    return 0;
}
