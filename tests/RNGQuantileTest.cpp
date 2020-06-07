#include <iostream>
#include <string>
#include "TH1D.h"

#include "../RNGQuantile.h"

using namespace std;

int main (int argc, char *argv[])
{
    RNGQuantile qrng;
    qrng.Print();
    qrng.SetDescription("aaa");
    qrng.Print();
    qrng.OpenQuantileFile("hQuantile.root");
    for (int i=0; i<5000; i++) qrng.GetRandom();
    qrng.SaveDistributionPng();
    
    
    return 0;
}
