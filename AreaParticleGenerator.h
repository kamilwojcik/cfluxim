#ifndef AREAPARTICLEGEN_H
#define AREAPARTICLEGEN_H

#include <iostream>
#include <string>

#include "TTree.h"

#include "Rectanghe.h"
#include "ParticleGenerator.h"
#include "FluxList.h"

class AreaParticleGen
{
    Rectangle rectangle;
    ParticleGenerator partGen;
    FluxList flist;
    TTree * outtree;
    
    
public:
    void SetTree();
    void LoadMomentumQuantileHisto(TH1D * momQuantile);
    void LoadFluxVsThetaHisto(TH1D * fluxVsTheta);
    void SetRectangle();
    void SetTimeSec();
    void SetTimeHours();
    
    void GenerateParticles();
    void Save();
    
    
    
};























#endif
