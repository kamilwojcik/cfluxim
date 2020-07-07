#include "Disk.h"
#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "Plane.h"

#include <cmath>
#include <iostream>

#define PI 3.14159265

using namespace std;

void Disk::SetDisk(Coords central_point, Coords normal_vec, double r)
{
        center=central_point;
        
        double D = - scalarProduct(center, normal_vec);
        plane.SetPlane(normal_vec[0], normal_vec[1], normal_vec[2], D);
        radius=r;
        
        area=PI*r*r;
        
        return;
}

void Disk::SetDisk(double c_x, double c_y, double c_z, double A, double B, double C, double r)
{
    center.SetCoords(c_x, c_y, c_z);
    double D = - (A*c_x + B*c_y + C*c_z);
    plane.SetPlane(A,B,C,D);
    radius = r;
    area = PI*r*r;
    
    return;
}


void Disk::ChangeNormalVecDirection()
{
    plane.ChangeNormalVecDirection();
    return;
}

double Disk::GetArea()
{
    return area;
}

double Disk::GetRadius()
{
    return radius;
}

Coords Disk::GetNormalVector()
{
    return plane.GetNormalVector();
}

Coords Disk::GetCenter()
{
    return center;
}

Plane Disk::GetPlane()
{
    return plane;
}

bool Disk::HitsDisk(Particle particle)
{
    bool ans = plane.HitsPlane(particle);
    if (ans)
    {
        hitPosition=plane.GetHitPosition(particle);
        if (distance(hitPosition, center) > radius) ans=false;
    }
    return ans;
}

Coords Disk::GetHitPosition()
{
    return hitPosition;
}

void Disk::Print()
{
    cout<<"Disk\nCenter: "<<endl;
    center.Print();
    cout<<"Radius: "<<radius<<endl;
    plane.Print();

    return;
}


///////////////////////////////
// constructor


Disk::Disk(double c_x, double c_y, double c_z, double A, double B, double C, double r)
{
    SetDisk(c_x, c_y, c_z, A, B, C, r);
}

Disk::Disk(Coords central_point, Coords normal_vec, double r)
{
    SetDisk(central_point, normal_vec, r);
}
