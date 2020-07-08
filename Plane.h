#ifndef PLANE_H
#define PLANE_H

#include "Coords.h"
#include "Particle.h"
#include "Momentum.h"


class Plane
{
    double A,B,C,D;
    
    bool IsDefinitionGood(double, double, double, double);
    
public:
    
    void SetPlane(double a, double b, double c, double d); 
    void SetPlane(Coords & normalVector, Coords & point);
    void ChangeNormalVecDirection();
    
    double operator[](int index);
    Plane operator=(Plane instance_to_copy);
    Coords GetNormalVector();
    
    void Print();
    
    Plane(double a=0, double b=0, double c=1, double d=0); //XY by default
    Plane(Coords & normalVector, Coords & point);
    
    bool BelongsToPlane(Coords point);
    bool HitsPlane(Particle particle);
    Coords GetHitPosition(Particle particle);
};

#endif
