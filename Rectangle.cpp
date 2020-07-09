#include "Rectangle.h"
#include "Particle.h"
#include "Coords.h"

#include <iostream>
#include <cmath>

using namespace std;


void Rectangle::SetDefault()
{
    v1.SetCoords(-0.5,0.5,0);
    v2.SetCoords(0.5,0.5,0);
    v3.SetCoords(0.5,-0.5,0);
    v4.SetCoords(-0.5,-0.5,0);
    CalculateEdgesAndPlane();
    return;
}

bool Rectangle::CalculateEdgesAndPlane()
{
    bool success=true;
    Coords normalVec=vectorProduct(v4-v1, v2-v1);
    plane.SetPlane(normalVec, v1);
    
    if ( !plane.BelongsToPlane(v2) || !plane.BelongsToPlane(v3) || !plane.BelongsToPlane(v4) )
    {
        cout<<"Warning: unsupported plane!"<<endl;
        success=false;
    }
    
    edge1=distance(v1,v2);
    edge2=distance(v2,v3);
    
    if ( (edge1 != distance(v4,v3) && edge2 != distance(v1, v4)) || scalarProduct(v2-v1, v4-v1) != 0 )
    {
        cout<<"Warning: not a rectangle!"<<endl;
        success=false;
    }
    
    surfaceArea = edge1*edge2;
    
    vec12 = v2-v1;
    vec23 = v3-v2;
    vec34 = v4-v3;
    vec41 = v1-v4;
    
    return success;
}


bool Rectangle::SetRectangle(Coords & vertice1, Coords & vertice2, Coords & vertice3, Coords & vertice4)
{
        v1=vertice1;
        v2=vertice2;
        v3=vertice3;
        v4=vertice4;
        bool ans = CalculateEdgesAndPlane();
        if (!ans) SetDefault();
        return ans;
}


void Rectangle::ChangeNormalVecDirection()
{
    plane.ChangeNormalVecDirection();
    return;
}


Coords Rectangle::RelativeToAbsolute(Coords relative)
{
    Coords absolute = v1 + relative[0]/edge1*(v2-v1) + relative[1]/edge2*(v4-v1); //v1 + relative[0]/edge1*(v2-v1) + relative[1]/edge2*(v4-v1);
    return absolute;
}


Coords Rectangle::AbsoluteToRelative(Coords absolute)
{
    Coords relative(scalarProduct((1./edge1)*(v2-v1),absolute-v1), scalarProduct((1./edge2)*(v4-v1),absolute-v1), 0); 
    return relative;
}

    
double Rectangle::GetSurfaceArea()
{
    return surfaceArea;
}

Coords Rectangle::GetVertice(int index)
{
    if (index == 1) return v1;
    else if (index == 2) return v2;
    else if (index == 3) return v3;
    else if (index == 4) return v4;
    else
    {
        cout<<"GetVertice warning: index out of range!"<<endl;
        return v1;
    }
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
    bool ans=false;
    
    if ( plane.HitsPlane(particle) )
    {
        hitPosition = plane.GetHitPosition(particle);
        ans = scalarProduct(vec12, hitPosition - v1) >= 0 && scalarProduct(vec23, hitPosition - v2) >= 0 && scalarProduct(vec34, hitPosition - v3) >= 0 && scalarProduct(vec41, hitPosition - v4) >= 0;
    }
    return ans;
}

Rectangle Rectangle::operator=(Rectangle instance_to_copy)
{
    plane = instance_to_copy.plane;
    v1 = instance_to_copy.v1;
    v2 = instance_to_copy.v2;
    v3 = instance_to_copy.v3;
    v4 = instance_to_copy.v4;
    surfaceArea = instance_to_copy.surfaceArea;
    edge1 = instance_to_copy.edge1;
    edge2 = instance_to_copy.edge2;
    vec12 = instance_to_copy.vec12;
    vec23 = instance_to_copy.vec23;
    vec34 = instance_to_copy.vec34;
    vec41 = instance_to_copy.vec41;
    
    return instance_to_copy;
}

void Rectangle::Print()
{
    
    cout<<"Rectangle in plane:"<<endl;
    plane.Print();
    cout<<"vertice 1: ";
    v1.Print();
    cout<<"vertice 2: ";
    v2.Print();
    cout<<"vertice 3: ";
    v3.Print();
    cout<<"vertice 4: ";
    v4.Print();
    cout<<"Edge1: "<<edge1<<"  edge2: "<<edge2<<"  surface area: "<<surfaceArea<<endl;
    
    return;
}
    
Rectangle::Rectangle()
{
    SetDefault();
}

Rectangle::Rectangle(Coords & vertice1, Coords & vertice2, Coords & vertice3, Coords & vertice4)
{
    SetRectangle(vertice1, vertice2, vertice3, vertice4);
}
