#include "Momentum.h"
#include "Coords.h"


///////////////////////////////
//set

void Momentum::SetCarthesian(double p_x, double p_y, double p_z)
{
    carthesian.SetCoords(p_x, p_y, p_z);
    polar=carthesianToPolar(carthesian);

    return;
}

void Momentum::SetPolar(double p_r, double p_phi, double p_theta)
{
    polar.SetCoords(p_r, p_phi, p_theta);
    carthesian=polarToCarthesian(polar);
    
    return;
}

void Momentum::Set(Coords coords)
{
    eCoordinateSystem system = coords.GetCoordinateSystem();
    
    switch(system)
    {
        case eCoordinateSystem::polar:
            polar=coords;
            carthesian=polarToCarthesian(coords);
            break;
            
        case eCoordinateSystem::carthesian:
            carthesian=coords;
            polar=carthesianToPolar(coords);
            break;
    }
    
    return;
}



//////////////////////////////
//get



Coords& Momentum::GetCarthesian()
{
    return carthesian;
}

Coords& Momentum::GetPolar()
{
    return polar;
}

double Momentum::GetMagnitude()
{
    return polar[0];
}


/////////////////////////////////////
//print

void Momentum::PrintPolar()
{
    std::cout<<"Momentum ";
    polar.Print();
    
    return;
}

void Momentum::PrintCarthesian()
{
    std::cout<<"Momentum ";
    carthesian.Print();
    
    return;
}

void Momentum::Print()
{
    PrintPolar();
    PrintCarthesian();
    
    return;
}


/////////////////////////////////////
//constructors

Momentum::Momentum(double p1, double p2, double p3, eCoordinateSystem system)
{
    polar.SetSystem(eCoordinateSystem::polar);
    switch(system)
    {
        case eCoordinateSystem::polar:
            SetPolar(p1, p2, p3);
            break;
            
        case eCoordinateSystem::carthesian:
            SetCarthesian(p1, p2, p3);
            break;
    }
}

Momentum::Momentum(Coords coords)
{
    polar.SetSystem(eCoordinateSystem::polar);
    
    switch(coords.GetCoordinateSystem())
    {
        case eCoordinateSystem::polar:
            polar=coords;
            carthesian=polarToCarthesian(coords);
            break;
            
        case eCoordinateSystem::carthesian:
            carthesian=coords;
            polar.SetSystem(eCoordinateSystem::polar);
            polar=carthesianToPolar(coords);
            break;
    }
}

Momentum::Momentum(const Momentum& other)
{
        polar=other.polar;
        carthesian=other.carthesian;
}


////////////////////////////////////
//operators


Momentum& Momentum::operator=(Momentum& instance_to_copy)
{
    polar=instance_to_copy.polar;
    carthesian=instance_to_copy.carthesian;
    
    return instance_to_copy;
}
