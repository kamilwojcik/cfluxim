#include "Plane.h"
#include "Coords.h"

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
        SetNormalVecDirection(true);
    }
    else cout<<"Bad plane definition! Setting default: z = 0"<<endl;
        
    return;
}


void Plane::SetNormalVecDirection(bool direction)
{
    if (direction) normalVec.SetCoords(A, B, C);
    else normalVec.SetCoords(-A, -B, -C);

    return;
}

/////////////////////////
//get


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

Plane Plane::operator=(Plane instance_to_copy)
{
    A=instance_to_copy.A;
    B=instance_to_copy.B;
    C=instance_to_copy.C;
    D=instance_to_copy.D;
    normalVec=instance_to_copy.normalVec;
    return instance_to_copy;
}

Coords Plane::GetNormalVector()
{
    return normalVec;
}

///////////////////////////
//print

void Plane::Print()
{
    cout<<"Plane: "<<A<<"x + "<<B<<"y + "<<C<<"z + "<<D<<" = 0"<<endl;
    cout<<"Normal vector: ";
    normalVec.Print();
    
    return;
}



//////////////////////////////
//other
bool Plane::BelongsToPlane(Coords point)
{
    return A*point[0] + B*point[1] + C*point[2] + D == 0;
}

///////////////////////////
//constructors

Plane::Plane()
{
    SetPlane();
}

Plane::Plane(double a, double b, double c, double d, bool direction)
{
    SetPlane(); //initializes with defaults;
    SetPlane(a,b,c,d); //if definition ok -> setting the plane
    SetNormalVecDirection(direction);
}
