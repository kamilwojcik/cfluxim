#include "Rectangle.h"
#include "Particle.h"
#include "Coords.h"

#include <iostream>
#include <cmath>

using namespace std;


void Rectangle::SetDefault()
{
    upLeft.SetCoords(-0.5,0.5,0);
    downRight.SetCoords(0.5,-0.5,0);
    CalculateEdgesAndPlane();
    return;
}

bool Rectangle::CalculateEdgesAndPlane()
{
    bool success=true;
    double A,B,C,D;
    if ( upLeft[2] == downRight[2] and upLeft[0] != downRight[0] and upLeft[1] != downRight[1] ) //XY plane
    {
        edge1 = downRight[0] - upLeft[0]; //dx
        edge2 = upLeft[1] - downRight[1]; //dy
        A=B=0;
        C=1;
        D=-upLeft[2];
    }
    else if ( upLeft[1] == downRight[1] and upLeft[0] != downRight[0] and upLeft[2] != downRight[2] ) //XZ plane
    {
        edge1 = downRight[0] - upLeft[0]; //dx
        edge2 = upLeft[2] - downRight[2]; //dz
        A=C=0;
        B=1;
        D=-upLeft[1];
    }
    else if ( upLeft[0] == downRight[0] and upLeft[1] != downRight[1] and upLeft[2] != downRight[2] ) //YZ plane
    {
        edge1 = downRight[1] - upLeft[1]; //dy
        edge2 = upLeft[2] - downRight[2]; //dz
        B=C=0;
        A=1;
        D=-upLeft[0];
    }
    else
    {
        cout<<"Warning: unsupported plane!"<<endl;
        success=false;
    }
    surfaceArea = abs( edge1*edge2 );
    plane.SetPlane(A,B,C,D);
    
    return success;
}


bool Rectangle::SetRectangle(Coords & ULeft, Coords & DRight)
{
        upLeft=ULeft;
        downRight=DRight;
        return CalculateEdgesAndPlane();        
}

/*
void Rectangle::ChangeNormalVecDirection(bool direction)
{
    plane.SetNormalVecDirection(direction);
}
*/
Coords Rectangle::RelativeToAbsolute(Coords relative)
{
    Coords absolute;
    if ( plane[0] == 0 and plane[1] == 0 ) //XY plane
    {
        absolute.SetCoords( upLeft[0]+relative[0], upLeft[1]-edge2+relative[1], upLeft[2] );
    }
    
    else if ( plane[0] == 0 and plane[2] == 0 ) //XZ plane
    {
        absolute.SetCoords( upLeft[0]+relative[0], upLeft[1], upLeft[2]-edge2+relative[1] );
    }
    else if ( plane[1] == 0 and plane[2] == 0 ) //YZ plane
    {
        absolute.SetCoords( upLeft[0], upLeft[1]+relative[0], upLeft[2]-edge2+relative[1] );
    }
    
    return absolute;
}


Coords Rectangle::AbsoluteToRelative(Coords absolute)
{
    Coords relative;
    if ( plane[0] == 0 and plane[1] == 0 ) //XY plane
    {
        relative.SetCoords( absolute[0]-upLeft[0], upLeft[1]-absolute[1], 0);
    }
    else if ( plane[0] == 0 and plane[2] == 0 ) //XZ plane
    {
        relative.SetCoords( absolute[0]-upLeft[0], upLeft[2]-absolute[2], 0);
    }
    else if ( plane[1] == 0 and plane[2] == 0 ) //YZ plane
    {
        relative.SetCoords( absolute[1]-upLeft[1], upLeft[2]-absolute[2], 0);
    }
    
    return relative;
}


Momentum Rectangle::VecToRelative(Momentum absolute) //not testes
{
    Momentum relative;
    if ( plane[0] == 0 and plane[1] == 0 ) //XY plane
    {
        relative=absolute;
    }
    else if ( plane[0] == 0 and plane[2] == 0 ) //XZ plane
    {
        relative.SetCarthesian( absolute.GetCarthesian()[0] , absolute.GetCarthesian()[2], -absolute.GetCarthesian()[1] );
    }
    else if ( plane[1] == 0 and plane[2] == 0 ) //YZ plane
    {
        relative.SetCarthesian( -absolute.GetCarthesian()[2] , absolute.GetCarthesian()[1], absolute.GetCarthesian()[0] );
    }
    
    return relative;
}

Momentum Rectangle::VecToAbsolute(Momentum relative) //not tested
{
    Momentum absolute;
    if ( plane[0] == 0 and plane[1] == 0 ) //XY plane
    {
        absolute=relative;
    }
    else if ( plane[0] == 0 and plane[2] == 0 ) //XZ plane
    {
        absolute.SetCarthesian( relative.GetCarthesian()[0] , -relative.GetCarthesian()[2], relative.GetCarthesian()[1] );
    }
    else if ( plane[1] == 0 and plane[2] == 0 ) //YZ plane
    {
        absolute.SetCarthesian( relative.GetCarthesian()[2] , relative.GetCarthesian()[1], -relative.GetCarthesian()[0] );
    }
    
    return absolute;
}

    
double Rectangle::GetSurfaceArea()
{
    return surfaceArea;
}

Coords Rectangle::GetUpLeft()
{
    return upLeft;
}

Coords Rectangle::GetDownRight()
{
    return downRight;
}

Plane Rectangle::GetPlane()
{
    return plane;
}


Coords Rectangle::GetHitPosition()
{
    return hitPosition;
}

bool Rectangle::HitsRectangle(Particle particle)
{
    bool ans = false;
        
    if ( plane.HitsPlane(particle) )
    {
        hitPosition = plane.GetHitPosition(particle);
        hitRelative = AbsoluteToRelative(hitPosition);
        if (hitRelative[0] <= edge1 && hitRelative[0] >= 0 && hitRelative[1] <= edge2 && hitRelative[1] >= 0) ans = true;
    }
    return ans;
}

Rectangle Rectangle::operator=(Rectangle instance_to_copy)
{
    plane=instance_to_copy.plane;
    upLeft=instance_to_copy.upLeft;
    downRight=instance_to_copy.downRight;
    surfaceArea=instance_to_copy.surfaceArea;
    return instance_to_copy;
}

void Rectangle::Print()
{
    
    cout<<"Rectangle in ";
    if ( plane[0] == 0 and plane[1] == 0 ) cout<<"XY plane"<<endl;
    else if ( plane[0] == 0 and plane[2] == 0 ) cout<<"XZ plane"<<endl;
    else if ( plane[1] == 0 and plane[2] == 0 ) cout<<"YZ plane"<<endl;
    else cout<<"[error: unsupported] plane"<<endl;
    cout<<"upLeft: ";
    upLeft.Print();
    cout<<"downRight:";
    downRight.Print();
    cout<<"Edge1: "<<edge1<<"  edge2: "<<edge2<<"  surface area: "<<surfaceArea<<endl;
    plane.Print();
    
    return;
}
    
Rectangle::Rectangle()
{
    SetDefault();
}

Rectangle::Rectangle(Coords & ULeft, Coords & DRight)
{
    SetRectangle(ULeft, DRight);
}
