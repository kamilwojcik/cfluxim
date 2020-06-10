#ifndef PLANE_H
#define PLANE_H

#include "Coords.h"



class Plane
{
    double A,B,C,D;
    Coords normalVec;
    
    bool IsDefinitionGood(double, double, double, double);
    
public:
    
    void SetPlane(double a=0, double b=0, double c=1, double d=0); //XY by default
    void SetNormalVecDirection(bool direction); //you may change the normal vector direction
    
    double operator[](int index);
    Coords GetNormalVector();
    
    void Print();
    
    Plane();
    Plane(double a, double b, double c, double d, bool direction = true);
    
    bool BelongsToPlane(Coords point);
};

#endif
