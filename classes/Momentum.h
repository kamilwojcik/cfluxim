#ifndef MOMENTUM_H
#define MOMENTUM_H

#include "Coords.h"
#include <cmath>

class Momentum
{
        Coords carthesian;
        Coords spherical;
        
    public:    
        void SetCarthesian(double p_x, double p_y, double p_z);
        void SetSpherical(double p_mag, double p_phi, double p_theta);
        void Set(Coords coords);
        
        
        Coords& GetCarthesian();
        Coords& GetSpherical();
        double GetMagnitude();
        
        void PrintSpherical();
        void PrintCarthesian();
        void Print();
        
        
        Momentum(double p1=0, double p2=0, double p3=0, eCoordinateSystem system  = eCoordinateSystem::carthesian);
        Momentum(Coords coords);
        Momentum(const Momentum& object_to_copy);
        
        Momentum& operator=(Momentum& instance_to_copy);
};

#endif
