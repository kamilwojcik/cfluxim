#ifndef AREA_H
#define AREA_H

#include "Coords.h"
#include "Particle.h"

////////////////////////////////////////////////////////////////////////////
// class Area contains the plane definition in Carthesian coordinate system
// and the definition of the area contained in the surface
//
// Area is defined by two opposite vertices of the rectangle 'upLeft' and 'downRight':
//
// upLeft
//    *____________________
//    |                    |
//    |                    |
//    |                    |
//    |____________________|
//                         * downRight
// The plane is defined by the equation: Ax + By + Cz + D = 0
// and is calculated automatically after setting V1 and V2
//
// Spherical coordinates are NOT supported for by this class.
//
// METHODS:
//
// Coords RelativeToAbsolute(Coords) method transforms (x,y,z=0) relative coordinates
// on the area to the (x,y,z) absolute coordinates
//
// Coords AbsoluteToRelative(Coords) method does the opposite.
//
// It also includes a normal vector to the plane
//

class Area
{
    double A,B,C,D;
    Coords upLeft, downRight, normalVec;
    double surfaceArea;
    
    void CalculateSurfaceArea();
    
public:
    bool SetArea(Coords UpLeft, Coords DownRight);
    void SetNormalVecDirection(bool direction);
    
    Coords RelativeToAbsolute(Coords relative);
    Coords AbsoluteToRelative(Coords absolute);
    
    double GetA();
    double GetB();
    double GetC();
    double GetD();
    double GetSurfaceArea();
    Coords GetUpLeft();
    Coords GetDownRight();
    
    void Print();
    
    Area();
    Area(Coords, Coords);
};

#endif
