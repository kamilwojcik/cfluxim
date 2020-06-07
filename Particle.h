#ifndef PARTICLE_H
#define PARTICLE_H

#include "Momentum.h"
#include "Coords.h"


class Particle
{
        int PID;
        Coords position; //in carthesian, polar position is not supported
        Momentum momentum;
    
    public:
        void SetPosition(Coords& pos);
        void SetPosition(double x, double y, double z);
        void SetMomentum(Momentum& p);
        void SetMomentum(double p1, double p2, double p3, eCoordinateSystem system=eCoordinateSystem::polar);
        void SetPID(int id=0);
        void Set(Coords& pos, Momentum& p, int id=0);
        void Set(double pos_x=0, double pos_y=0, double pos_z=0, double p1=0, double p2=0, double p3=0, int id=0, eCoordinateSystem system=eCoordinateSystem::polar);
        
        Coords& GetPosition();
        Momentum& GetMomentum();
        int GetPID();
        double GetPosition(int index);
        
        void Print();
        
        Particle(Coords& pos, Momentum& p, int id=0);
        Particle(double pos_x=0, double pos_y=0, double pos_z=0, double p1=0, double p2=0, double p3=0, int id=0, eCoordinateSystem system=eCoordinateSystem::polar);
};


#endif
