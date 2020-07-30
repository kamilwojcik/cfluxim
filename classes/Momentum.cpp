#include "Momentum.h"
#include "Coords.h"


///////////////////////////////
//set

void Momentum::SetCarthesian(double p_x, double p_y, double p_z)
{
    carthesian.SetCoords(p_x, p_y, p_z);
    spherical=carthesianToSpherical(carthesian);

    return;
}

void Momentum::SetSpherical(double p_r, double p_theta, double p_phi)
{
    spherical.SetCoords(p_r, p_theta, p_phi);
    carthesian=sphericalToCarthesian(spherical);
    
    return;
}

void Momentum::Set(Coords coords)
{
    eCoordinateSystem system = coords.GetCoordinateSystem();
    
    switch(system)
    {
        case eCoordinateSystem::spherical:
            spherical=coords;
            carthesian=sphericalToCarthesian(coords);
            break;
            
        case eCoordinateSystem::carthesian:
            carthesian=coords;
            spherical=carthesianToSpherical(coords);
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

Coords& Momentum::GetSpherical()
{
    return spherical;
}

double Momentum::GetMagnitude()
{
    return spherical[0];
}


/////////////////////////////////////
//print

void Momentum::PrintSpherical()
{
    std::cout<<"Momentum ";
    spherical.Print();
    
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
    PrintSpherical();
    PrintCarthesian();
    
    return;
}


/////////////////////////////////////
//constructors

Momentum::Momentum(double p1, double p2, double p3, eCoordinateSystem system)
{
    spherical.SetSystem(eCoordinateSystem::spherical);
    
    switch(system)
    {
        case eCoordinateSystem::spherical:
            SetSpherical(p1, p2, p3);
            break;
            
        case eCoordinateSystem::carthesian:
            SetCarthesian(p1, p2, p3);
            break;
    }
}

Momentum::Momentum(Coords coords)
{
    spherical.SetSystem(eCoordinateSystem::spherical);
    
    switch(coords.GetCoordinateSystem())
    {
        case eCoordinateSystem::spherical:
            spherical=coords;
            carthesian=sphericalToCarthesian(coords);
            break;
            
        case eCoordinateSystem::carthesian:
            carthesian=coords;
            spherical.SetSystem(eCoordinateSystem::spherical);
            spherical=carthesianToSpherical(coords);
            break;
    }
}

Momentum::Momentum(const Momentum& other)
{
        spherical=other.spherical;
        carthesian=other.carthesian;
}


////////////////////////////////////
//operators


Momentum& Momentum::operator=(Momentum& instance_to_copy)
{
    spherical=instance_to_copy.spherical;
    carthesian=instance_to_copy.carthesian;
    
    return instance_to_copy;
}
