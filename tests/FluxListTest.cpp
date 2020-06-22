#include "../FluxList.h"
#include <iostream>

#include "TFile.h"
#include "TH1D.h"


using namespace std;

int main(void)
{
    FluxList flst;
    
    flst.Print();
    
    TFile * file= TFile::Open("uFluxTheta.root");
    cout<<"Opening uFluxTheta file: "<<"uFluxTheta.root"<<endl;
    file->Print();
    
    TH1D * uFlux = (TH1D*)file->Get("uFluxTheta");
    
    flst.SetFluxVsThetaHisto(uFlux);
    flst.SetArea(1,1.571,0);
    flst.Print();
    flst.Recalculate();
    flst.Print();
    flst.Save();
    
    return 0;
}
