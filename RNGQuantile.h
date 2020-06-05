#ifndef RNGQANTILE_H
#define RNGQANTILE_H


#include <iostream>
#include <string>

#include "TH1D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TCanvas.h"


class RNGQuantile 
{
    std::string description;
    
    TH1D* quantileHisto;
    TH1D* distributionHisto;
    TCanvas *cnv;
    TFile *file;

protected:
    
    bool ready;
    TRandom3 *rng;
    
public:

    void SetDescription(std::string descr);
    void OpenQuantileFile(std::string filename);
    void SaveDistribution(std::string filename="RNGdistribution.root");
    void SaveDistributionPng(std::string filename="RNGdistribution.png");
    
    double GetRandom();
    
    void Print();
    
    RNGQuantile();
    RNGQuantile(std::string filename, std::string descr="RNGQuantile");
    
    ~RNGQuantile();
};

#endif
