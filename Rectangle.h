#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Coords.h"
#include "Particle.h"
#include "Plane.h"

////////////////////////////////////////////////////////////////////////////
// class Rectangle = plane + two points that defines the rectangular area.
//
// Rectangle is defined by two opposite vertices of the rectangle 'upLeft' and 'downRight':
//
// upLeft
//    *____________________
//    |                    |
//    |                    |
//    |                    |
//    |____________________|
//                         * downRight
// Surface area is calculated automatically after setting V1 and V2
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
    Coords upLeft, downRight, hitPosition, hitRelative;
    double surfaceArea, edge1, edge2;
    
    bool CalculateEdgesAndPlane();
    
public:
    void SetDefault();
    bool SetRectangle(Coords & UpLeft, Coords & DownRight);
    //void SetNormalVecDirection(bool direction);
    
    Coords RelativeToAbsolute(Coords relative);
    Coords AbsoluteToRelative(Coords absolute);
    Momentum VecToAbsolute(Momentum);
    Momentum VecToRelative(Momentum);
    
    double GetSurfaceArea();
    Coords GetUpLeft();
    Coords GetDownRight();
    Plane  GetPlane();
    
    Coords GetHitPosition(); //returns absolute hit position
    bool HitsRectangle(Particle particle);
    
    Rectangle operator=(Rectangle instance_to_copy);
    
    void Print();
    
    Rectangle();
    Rectangle(Coords&, Coords&);
};

#endif
