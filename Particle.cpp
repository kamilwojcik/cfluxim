#include "Particle.h"
#include "Coords.h"
#include "Momentum.h"

#include <iostream>


////////////////////////////////////
//set


void Particle::SetPosition(Coords& pos)
{
    position=pos;
    position.SetSystem(eCoordinateSystem::carthesian);
    
    return;
}

void Particle::SetPosition(double x, double y, double z)
{
    position.SetCoords(x,y,z);
    
    return;
}

void Particle::SetMomentum(Momentum& p)
{
    momentum=p;
    
    return;
}

void Particle::SetMomentum(double p1, double p2, double p3, eCoordinateSystem system)
{
    system == eCoordinateSystem::polar ? momentum.SetPolar(p1,p2,p3) : momentum.SetCarthesian(p1,p2,p3);
    
    return;
}

void Particle::SetPID(int id)
{
    PID=id;

    return;
}
void Particle::Set(Coords& pos, Momentum& p, int id)
{
    SetPosition(pos);
    SetMomentum(p);
    
    return;
}

void Particle::Set(double pos_x, double pos_y, double pos_z, double p1, double p2, double p3, int id, eCoordinateSystem system)
{
    SetPosition(pos_x,pos_y,pos_z);
    SetMomentum(p1,p2,p3,system);
    SetPID(id);
    return;
}



////////////////////////////////////
//Get




Coords& Particle::GetPosition()
{    
    return position;
}

double Particle::GetPosition(int index)
{    
    return position[index];
}

Momentum& Particle::GetMomentum()
{
    return momentum;
}


int Particle::GetPID()
{
    return PID;
}


////////////////////////////////////
//print

void Particle::Print()
{
    std::cout<<"Particle PID: "<<PID<<std::endl<<"Position: ";
    position.Print();
    momentum.Print();
    
    return;
}



/////////////////////////////////////
//constructors

Particle::Particle(Coords& pos, Momentum& p, int id)
{
    Set(pos, p, id);
}

Particle::Particle(double pos_x, double pos_y, double pos_z, double p1, double p2, double p3, int id, eCoordinateSystem system)
{
    Set(pos_x, pos_y, pos_z, p1, p2, p3, id, system);
}
