#ifndef RNGQANTILE_H
#define RNGQANTILE_H


#include <iostream>
#include <string>

#include "TH1D.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TF1.h"


class RNGQuantile 
{
    std::string description;
    
    TF1 * momentumQuantileFunction;
    
    TH1D* distributionHisto;
    TCanvas *cnv;
    double scale, ymin;
    
protected:
    
    bool ready;
    TRandom3 *rng;
    
public:

    void SetDescription(std::string descr);
    void SetMomentumQuantileFunction(TF1 * momQuantile);
    void SaveDistribution(std::string filename="RNGdistribution.root");
    void SaveDistributionPng(std::string filename="RNGdistribution.png");
    void ResetDistribution();
    
    double GetRandom();
    
    void Print();
    
    RNGQuantile();
    RNGQuantile(TF1 * momQuantile, std::string descr="RNGQuantile");
    
    ~RNGQuantile();
};

#endif
