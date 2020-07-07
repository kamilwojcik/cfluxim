#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "Cylinder.h"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


void Cylinder::SetCylinder(Coords s1, Coords s2, double r)
{
    s1s2vector = s2 - s1;
    wall1.SetDisk(s1, s1s2vector ,r);
    wall2.SetDisk(s2, -s1s2vector, r);
    radius = r;
    
    return;
}

void Cylinder::SetCylinder(double s1x, double s1y, double s1z, double s2x, double s2y, double s2z, double r)
{
    Coords s1(s1x,s1y,s1z);
    Coords s2(s2x,s2y,s2z);
    
    s1s2vector = s2 - s1;
    wall1.SetDisk(s1, s1s2vector ,r);
    wall2.SetDisk(s2, -s1s2vector, r);
    radius = r;
    
    return;
}

Disk Cylinder::GetWall1()
{
    return wall1;
}

Disk Cylinder::GetWall2()
{
    return wall2;
}

Coords Cylinder::GetAxisVector()
{
    return s1s2vector;
}

double Cylinder::GetRadius()
{
    return radius;
}

bool Cylinder::HitPositionIsBetweenWalls(Coords hitPosition)
{
    //////////////////////////////////////////
    //
    //
    //              +----------------------+
    //              |   * - _              |
    //             r|         * - _        |
    // cylinder     |   diameter     * - _ |
    // -------------+--------------------->+----
    // axis       s1|           s1s2vector |s2
    //              |                      |
    //         wall1|                      |
    //              +----------------------+
    //
    // if distances from hit position to s1 and s2 
    // are both smaller than diameter, then it lays between
    // disks wall1 and wall2
    
    double diameter = sqrt(pow(radius,2.) + scalarProduct(s1s2vector, s1s2vector));
    
    return distance(hitPosition, wall1.GetCenter()) <= diameter && distance(hitPosition, wall2.GetCenter()) <=diameter;
}


bool Cylinder::HitsWalls(Particle particle)
{
    hitWall1= wall1.HitsDisk(particle);
    if (hitWall1)
    {
        hitsWalls[0]=wall1.GetHitPosition();
    }
    
    hitWall2= wall2.HitsDisk(particle);
    if (hitWall2)
    {
        hitsWalls[1]=wall2.GetHitPosition();
    }
    
    return hitWall1 || hitWall2;
}

bool Cylinder::HitsLateral(Particle particle)
{
    //explanation:
    //
    // particle_pos(t) := (pos_x + momentum_x * t, pos_y + momentum_y * t, pos_z + momentum_z * t)
    //
    // Let's assume line l, given by point S and vector vec:
    // x = S_x + vec_x * t'
    // y = S_y + vec_y * t'
    // z = S_z + vec_z * t'
    //
    // Distance between point K and line l:
    //
    // sk is a vector from K to S
    //
    //           || sk x vec ||
    // d(K,l) = ----------------  = radius
    //             || vec ||
    //
    //where x means cross product (vector product)
    //
    // Hit position on the cylindrical surface MUST be distanced from the cylinder axis l (given by s1 and s1s2vector) by radius;
    //
    // Therefore: d(particle_pos(t), l) = radius
    //
    // after a few transformation, one can find t1 and t2 arguments for particle_pos(t) corresponding to hit positions with quadric equation
    //
    // at^2 + bt + c = 0
    //
    // At this stage only the distance from axis is checked. What about hitting the walls or missing it?
    // To check if the hit position is not between walls, HitPositionIsBetweenWalls(Coords hitPosition) must be used.
    //
    
    hitLateral1=false;
    hitLateral2=false;

    Coords pMom = particle.GetMomentum().GetCarthesian();
    Coords pPos = particle.GetPosition();
    Coords s1 = wall1.GetCenter();
    Coords v = vectorProduct(pMom, s1s2vector);
    Coords w = vectorProduct(pPos,s1s2vector)+vectorProduct(s1s2vector, s1);
    double a = scalarProduct(v,v);
    double b = 2.* scalarProduct(v,w);
    double c = scalarProduct(w,w) - pow(radius, 2) * scalarProduct(s1s2vector, s1s2vector);
    
    double delta = b*b - 4.*a*c;
    
    if (delta==0)
    {
        double t = -b / (2.*a);
        hitsLateral[0] = pPos + (pMom *t);

        if (HitPositionIsBetweenWalls(hitsLateral[0])) hitLateral1=true;
    }
    if (delta>0)
    {
        double t1 = (-b - sqrt(delta) ) / (2.*a);
        double t2 = (-b + sqrt(delta) ) / (2.*a);
        hitsLateral[0] = pPos + (pMom * t1);
        hitsLateral[1] = pPos + (pMom * t2);
        
        if (HitPositionIsBetweenWalls(hitsLateral[0])) hitLateral1=true;
        if (HitPositionIsBetweenWalls(hitsLateral[1])) hitLateral2=true;
    }
    
    return hitLateral1 || hitLateral2;
}
    
bool Cylinder::HitsCylinder(Particle particle)
{
    bool walls = HitsWalls(particle);
    bool lateral = HitsLateral(particle); //both functions must be executed!
    //return HitsWalls() || HitsLateral(); -> does not execute HitsLateral(); if HitWalls() == true !!!
    
    return walls || lateral;
}

vector<Coords> Cylinder::GetHitPositions()
{
    allHits.clear();
    if (hitWall1) allHits.push_back(hitsWalls[0]);
    if (hitWall2) allHits.push_back(hitsWalls[1]);
    if (hitLateral1) allHits.push_back(hitsLateral[0]);
    if (hitLateral2) allHits.push_back(hitsLateral[1]);
    return allHits;
}

void Cylinder::Print()
{
    cout<<"Cylinder walls:"<<endl;
    wall1.Print();
    wall2.Print();
    cout<<"Radius: "<<radius<<endl;
}

Cylinder::Cylinder(Coords p1, Coords p2, double r)
{
    SetCylinder(p1,p2,r);
}

Cylinder::Cylinder(double s1x, double s1y, double s1z, double s2x, double s2y, double s2z, double r)
{
    SetCylinder(s1x, s1y, s1z, s2x, s2y, s2z, r);
}
