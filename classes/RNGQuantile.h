#ifndef RNGQANTILE_H
#define RNGQANTILE_H


#include <iostream>
#include <string>

#include "TH1D.h"
#include "TRandom3.h"
#include "TCanvas.h"


class RNGQuantile 
{
    std::string description;
    
    TH1D* quantileHisto;
    TH1D* distributionHisto;
    TCanvas *cnv;

protected:
    
    bool ready;
    TRandom3 *rng;
    
public:

    void SetDescription(std::string descr);
    void SetMomentumQuantileHisto(TH1D * momQuantile);
    void SaveDistribution(std::string filename="RNGdistribution.root");
    void SaveDistributionPng(std::string filename="RNGdistribution.png");
    void ResetDistribution();
    
    double GetRandom();
    
    void Print();
    
    RNGQuantile();
    RNGQuantile(TH1D * momQuantile, std::string descr="RNGQuantile");
    
    ~RNGQuantile();
};

#endif
