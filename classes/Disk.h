#ifndef DISK_H
#define DISK_H

#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "Plane.h"

#include <cmath>
#include <iostream>


class Disk
{
    Coords center, hitPosition;
    Plane plane;
    double radius, area;
    
public:
    void SetDisk(Coords central_point, Coords normal_vec, double r);
    void SetDisk(double c_x=0, double c_y=0, double c_z=0, double A=0, double B=0, double C=1, double r=1);
    //default: a disk in XY plane, center: (0,0,0), radius=1
    
    void ChangeNormalVecDirection();
    
    double GetArea();
    double GetRadius();
    Coords GetNormalVector();
    Coords GetCenter();
    Plane  GetPlane();
    
    bool HitsDisk(Particle particle);
    Coords GetHitPosition();
    
    void Print();
    
    Disk(double c_x=0, double c_y=0, double c_z=0, double A=0, double B=0, double C=1, double r=1);
    Disk(Coords central_point, Coords normal_vec, double r);
};


#endif
