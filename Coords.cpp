#include "Coords.h"

#define PI 3.1415927
#define PItimes2 6.2831853

/////////////////////////////////////////////
//functions

Coords sphericalToCarthesian(Coords spherical)
{
    double x,y,z;
    x = spherical[0]*std::sin(spherical[1])*std::cos(spherical[2]);
    y = spherical[0]*std::sin(spherical[1])*std::sin(spherical[2]);
    z = spherical[0]*std::cos(spherical[1]);
    
    //std::cout<<"r="<<spherical[0]<<" phi="<<spherical[1]<<" theta="<<spherical[2]<<std::endl;
    //std::cout<<"x="<<x<<" y="<<y<<" z="<<z<<std::endl;
    
    Coords carthesian_coords(x,y,z);
    return carthesian_coords;
}

Coords carthesianToSpherical(Coords carthesian)
{
    double r, theta, phi;
    r = std::sqrt( carthesian[0]*carthesian[0] + carthesian[1]*carthesian[1] + carthesian[2]*carthesian[2] );
    theta = atan2( std::sqrt( carthesian[0]*carthesian[0] + carthesian[1]*carthesian[1] ), carthesian[2] );
    phi = atan2( carthesian[1],  carthesian[0] );
    
    if ( carthesian[0] == 0 && carthesian[1] == 0 && carthesian[2] == 0 ) theta=0;
    
    Coords spherical_coords(r, theta, phi, eCoordinateSystem::spherical);
    return spherical_coords;
}

double scalarProduct(Coords v1, Coords v2)
{
    if ( v1.GetCoordinateSystem() != v2.GetCoordinateSystem() )
    {
        std::cout<<"WARNING!"<<std::endl;
        std::cout<<"       Scalar product: coordinate system mismatch!"<<std::endl;
    }
    
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

Coords vectorProduct(Coords v1, Coords v2)
{
    if ( v1.GetCoordinateSystem() != v2.GetCoordinateSystem() )
    {
        std::cout<<"WARNING!"<<std::endl;
        std::cout<<"       Scalar product: coordinate system mismatch!"<<std::endl;
    }
    
    Coords vecProduct(v1[1]*v2[2]-v1[2]*v2[1], v1[2]*v2[0]-v1[0]*v2[2], v1[0]*v2[1]-v1[1]*v2[0]);
    return vecProduct;
}

double tripleProduct(Coords v1, Coords v2, Coords v3)
{
    if ( v1.GetCoordinateSystem() != v2.GetCoordinateSystem() )
    {
        std::cout<<"WARNING!"<<std::endl;
        std::cout<<"       Scalar product: coordinate system mismatch!"<<std::endl;
    }
    double tripleprod = v1[0]*v2[1]*v3[2] + v3[0]*v1[1]*v2[2] + v1[2]*v2[0]*v3[1] - v1[0]*v2[2]*v3[1] - v1[1]*v2[0]*v3[2] - v1[2]*v2[1]*v3[0];
    return tripleprod;
}


double norm(Coords v1)
{
    return sqrt( scalarProduct( v1, v1 ) );
}

double distance(Coords p1, Coords p2)
{
    return sqrt(pow(p2[0]-p1[0],2) + pow(p2[1]-p1[1],2) + pow(p2[2]-p1[2],2));
}

Coords operator*(double scalar, Coords vector)
{
    return vector*scalar;
}

///////////////////////////////////////////
//class methods


void Coords::CheckRadius()
{
    if ( coord_system==eCoordinateSystem::spherical )
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
        case eCoordinateSystem::spherical:
        std::cout<<"spherical: r="<< a1 <<" theta="<<a2<<" (deg: "<< a2*180./PI <<")"<<" phi="<<a3<<" (deg: "<< a3*180./PI <<")"<<std::endl;
        break;
        
        case eCoordinateSystem::carthesian:
        std::cout<<"carthesian: x="<<a1<<" y="<<a2<<" z="<<a3<<std::endl;
        break;
    }
    
    return;
}


/////////////////////////
//get

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


Coords Coords::operator=(Coords instance_to_copy)
{
    a1=instance_to_copy.a1;
    a2=instance_to_copy.a2;
    a3=instance_to_copy.a3;
    coord_system=instance_to_copy.coord_system;
    
    return instance_to_copy;
}

Coords Coords::operator+(Coords to_add)
{
    Coords to_be_returned;
    if (coord_system == eCoordinateSystem::carthesian && to_add.coord_system == coord_system)
    {
        to_be_returned.SetCoords(a1+to_add.a1, a2+to_add.a2, a3+to_add.a3);
    }
    else if (coord_system == eCoordinateSystem::spherical && to_add.coord_system == coord_system)
    {
        to_be_returned = sphericalToCarthesian(to_add);
        Coords this_carthesian = sphericalToCarthesian(*this);
        to_be_returned.a1 += this_carthesian.a1;
        to_be_returned.a2 += this_carthesian.a2;
        to_be_returned.a3 += this_carthesian.a3;
        to_be_returned = carthesianToSpherical(to_be_returned);
    }
    else
    {
        std::cout<<"Warning: coordinate system mismatch!"<<std::endl;
        to_be_returned = sphericalToCarthesian(to_add);
        Coords this_carthesian = sphericalToCarthesian(*this);
        to_be_returned.a1 += this_carthesian.a1;
        to_be_returned.a2 += this_carthesian.a2;
        to_be_returned.a3 += this_carthesian.a3;
        to_be_returned = carthesianToSpherical(to_be_returned);
    }
    return to_be_returned;
}


Coords Coords::operator-()
{
    Coords to_be_returned;
    if (coord_system == eCoordinateSystem::carthesian)
    {
        to_be_returned.SetCoords(-a1,-a2,-a3);
    }
    else
    {
        double phi = a3 + PI;
        to_be_returned.SetSystem(eCoordinateSystem::spherical);
        if (phi > PItimes2) phi -= PItimes2;
        to_be_returned.SetCoords(a1,PI-a2,phi);
    }
    return to_be_returned;
}


Coords Coords::operator-(Coords to_substract)
{
    
    Coords to_be_returned(*this +  (-to_substract));
    
    return to_be_returned;
}

Coords Coords::operator*(double scalar)
{
    Coords to_be_returned(*this);
    if (coord_system == eCoordinateSystem::carthesian)
    {
        to_be_returned.a1 *= scalar;
        to_be_returned.a2 *= scalar;
        to_be_returned.a3 *= scalar;
    }
    else to_be_returned.a1 *= scalar;
    
    return to_be_returned;
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
