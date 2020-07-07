#ifndef CYLINDER_H
#define CYLINDER_H

#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "Plane.h"
#include "Disk.h"

#include <vector>

using namespace std;

class Cylinder
{
    Disk wall1, wall2;
    Coords hitsLateral[2], hitsWalls[2];
    vector<Coords> allHits;
    bool hitLateral1,hitLateral2, hitWall1, hitWall2;
    Coords s1s2vector;
    double radius;
    
    bool HitPositionIsBetweenWalls(Coords position);
    
public:
    void SetCylinder(Coords s1, Coords s2, double r);
    void SetCylinder(double s1x, double s1y, double s1z, double s2x, double s2y, double s2z, double r);
    
    Disk GetWall1();
    Disk GetWall2();
    Coords GetAxisVector();
    double GetRadius();
    
    bool HitsLateral(Particle particle);
    bool HitsWalls(Particle particle);
    bool HitsCylinder(Particle particle);
    int GetNumberOfHits();
    vector<Coords> GetHitPositions();
    
    void Print();
    
    Cylinder(double s1x=-1, double s1y=0, double s1z=0, double s2x=1, double s2y=0, double s2z=0, double r=1);
    Cylinder(Coords p1, Coords p2, double r);
};

#endif
