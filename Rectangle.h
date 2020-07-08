#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Coords.h"
#include "Particle.h"
#include "Plane.h"

////////////////////////////////////////////////////////////////////////////
// class Rectangle = plane + 4 points that defines the rectangular area.
//
// Rectangle is defined by two opposite vertices of the rectangle 'upLeft' and 'downRight':
//
//
//   V1____________________V2
//    |                    |
//    |                    |
//    |                    |
//    |____________________|
//   V4                    V3
// Surface area is calculated automatically after setting V1 and V2
// 
//
// Spherical coordinates are NOT supported for by this class.
//
// METHODS:
//
// Coords RelativeToAbsolute(Coords) method transforms (x,y,z=0) relative position
// coordinate on the rectangle to the (X,Y,Z) absolute position
//
// Coords AbsoluteToRelative(Coords) method does the opposite.
//
// THIS IS A SIMPLEST IMPLEMENTATION: each edge is parallel to one of the axis
// (only XY, XZ, YZ planes are supported, no rotations)
//


class Rectangle
{
    Plane plane;
    Coords v1,v2,v3,v4, hitPosition;
    double surfaceArea, edge1, edge2;
    
    bool CalculateEdgesAndPlane();
    
public:
    void SetDefault();
    bool SetRectangle(Coords & vertice1, Coords & vertice2, Coords & vertice3, Coords & vertice4);
    void ChangeNormalVecDirection();
    
    Coords RelativeToAbsolute(Coords relative);
    Coords AbsoluteToRelative(Coords absolute);
    //Momentum VecToAbsolute(Momentum);
    //Momentum VecToRelative(Momentum);
    
    double GetSurfaceArea();
    Coords GetVertice(int index);
    Plane  GetPlane();
    
    Coords GetHitPosition(); //returns absolute hit position
    bool HitsRectangle(Particle particle);
    
    Rectangle operator=(Rectangle instance_to_copy);
    
    void Print();
    
    Rectangle();
    Rectangle(Coords & vertice1, Coords & vertice2, Coords & vertice3, Coords & vertice4);
};

#endif
