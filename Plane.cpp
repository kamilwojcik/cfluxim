#include "Plane.h"
#include "Coords.h"
#include "Particle.h"
#include "Momentum.h"

#include <iostream>

using namespace std;


//private

bool Plane::IsDefinitionGood(double a, double b, double c, double d)
{
    return a != 0 or b != 0 or c != 0;
}

//public

/////////////
//set

void Plane::SetPlane(double a, double b, double c, double d)
{
    if (IsDefinitionGood(a,b,c,d))
    {
        A=a;
        B=b;
        C=c;
        D=d;
    }
    else
    {
        cout<<"Bad plane definition! Setting default: z = 0"<<endl;
        A=0;
        B=0;
        C=1;
        D=0;
    }
    return;
}


void Plane::ChangeNormalVecDirection()
{
    
    A = -A;
    B = -B;
    C = -C;
    D = -D;

    return;
}

/////////////////////////
//get

Coords Plane::GetNormalVector()
{
    Coords normalVec(A,B,C);
    return normalVec;
}

double Plane::operator[](int index)
{
    if ( index == 0 ) return A;
    else if ( index == 1 ) return B;
    else if ( index == 2 ) return C;
    else if ( index == 3 ) return D;
    else
    {
        std::cout<<"Index out of range!"<<std::endl;
        return 0;
    }
}

bool Plane::HitsPlane(Particle particle)
{
    return scalarProduct( particle.GetMomentum().GetCarthesian(), GetNormalVector()) != 0;
}


Coords Plane::GetHitPosition(Particle particle)
{
    Coords hitPosition;
    
    if (HitsPlane(particle))
    {
        Coords position = particle.GetPosition();
        Coords momentum = particle.GetMomentum().GetCarthesian();
        
        double t = - ( scalarProduct(GetNormalVector(), position) + D ) / scalarProduct (GetNormalVector(), momentum);
        
        hitPosition = position + momentum*t;
    }
    return hitPosition;
}


Plane Plane::operator=(Plane instance_to_copy)
{
    A=instance_to_copy.A;
    B=instance_to_copy.B;
    C=instance_to_copy.C;
    D=instance_to_copy.D;
    return instance_to_copy;
}


///////////////////////////
//print

void Plane::Print()
{
    cout<<"Plane: "<<A<<"x + "<<B<<"y + "<<C<<"z + "<<D<<" = 0"<<endl;
    cout<<"Normal vector: ";
    GetNormalVector().Print();
    
    return;
}



//////////////////////////////
//other
bool Plane::BelongsToPlane(Coords point)
{
    return scalarProduct(GetNormalVector(), point) + D == 0;
}

///////////////////////////
//constructors

Plane::Plane(double a, double b, double c, double d)
{
    SetPlane(a,b,c,d);
}
