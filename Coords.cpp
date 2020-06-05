#include "Coords.h"

#define PI 3.14159265

/////////////////////////////////////////////
//functions

Coords polarToCarthesian(Coords polar)
{
    double x,y,z;
    z = polar[0]*std::sin(polar[2]);
    x = polar[0]*std::cos(polar[2])*std::cos(polar[1]);
    y = polar[0]*std::cos(polar[2])*std::sin(polar[1]);
    Coords carthesian_coords(x,y,z);
    return carthesian_coords;
}

Coords carthesianToPolar(Coords carthesian)
{
    double r, phi, theta;
    r = std::sqrt( carthesian[0]*carthesian[0] + carthesian[1]*carthesian[1] + carthesian[2]*carthesian[2] );
    phi = atan2( carthesian[1],  carthesian[0] );
    theta = atan( carthesian[2]/std::sqrt( carthesian[0]*carthesian[0] + carthesian[1]*carthesian[1] ) );
    
    if ( carthesian[0] == 0 && carthesian[1] == 0 && carthesian[2] == 0 ) theta=0;
    
    Coords polar_coords(r, phi, theta, eCoordinateSystem::polar);
    return polar_coords;
}



///////////////////////////////////////////
//class methods


void Coords::CheckRadius()
{
    if ( coord_system==eCoordinateSystem::polar )
        if (a1<0)
        {
            std::cout<<"r must be positive! Setting r=0"<<std::endl;
            a1=0;
        }
        
    return;
}


void Coords::SetSystem(eCoordinateSystem system)
{
    coord_system=system;
    CheckRadius();
    
    return;
}
        

void Coords::Move(double c1, double c2, double c3)
{
    a1+=c1;
    a2+=c2;
    a3+=c3;
    CheckRadius();
    
    return;
}


void Coords::SetCoords(double c1, double c2, double c3)
{
    a1=c1;
    a2=c2;
    a3=c3;
    CheckRadius();
    
    return;
}


void Coords::Print()
{
    switch(coord_system)
    {
        case eCoordinateSystem::polar:
        std::cout<<"polar: r="<< a1 <<" phi="<<a2<<" (deg: "<< a2*180/PI <<")"<<" theta="<<a3<<" (deg: "<< a3*180/PI <<")"<<std::endl;
        break;
        
        case eCoordinateSystem::carthesian:
        std::cout<<"carthesian: x="<<a1<<" y="<<a2<<" z="<<a3<<std::endl;
        break;
    }
    
    return;
}

eCoordinateSystem Coords::GetCoordinateSystem()
{
    return coord_system;
}

double Coords::operator[](int index)
{
    if ( index == 0 ) return a1;
    else if ( index == 1 ) return a2;
    else if ( index == 2 ) return a3;
    else
    {
        std::cout<<"Index out of range!"<<std::endl;
        return 0;
    }
}


const Coords& Coords::operator=(const Coords& instance_to_copy)
{
    a1=instance_to_copy.a1;
    a2=instance_to_copy.a2;
    a3=instance_to_copy.a3;
    coord_system=instance_to_copy.coord_system;
    
    return instance_to_copy;
}

    
Coords::Coords(double c1, double c2, double c3, eCoordinateSystem system)
{
    a1=c1;
    a2=c2;
    a3=c3;
    SetSystem(system);
}


Coords::Coords(const Coords& instance_to_copy)
{
    a1=instance_to_copy.a1;
    a2=instance_to_copy.a2;
    a3=instance_to_copy.a3;
    coord_system=instance_to_copy.coord_system;
}
