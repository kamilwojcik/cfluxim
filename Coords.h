#ifndef COORDS_H
#define COORDS_H

#include <iostream>
#include <cmath>

enum class eCoordinateSystem
{
    spherical = 0,
    carthesian = 1
};

class Coords
{
        eCoordinateSystem coord_system;
        double a1, a2, a3;   //in spherical: r, phi, theta; in carthesian: x, y, z
    
        void CheckRadius();
        
    public:
        void SetSystem(eCoordinateSystem system);
        void SetCoords(double c1, double c2, double c3);
        void Move(double c1, double c2, double c3);
        
        void Print();
        eCoordinateSystem GetCoordinateSystem();
        
        double operator[](int index);
        Coords operator=(Coords instance_to_copy);
        Coords operator+(Coords to_add);
        Coords operator-();
        Coords operator-(Coords to_substract);
        Coords operator*(double scalar);
    
        Coords(double x=0, double y=0, double z=0, eCoordinateSystem system  = eCoordinateSystem::carthesian);
        Coords(const Coords& instance_to_copy);
};

Coords sphericalToCarthesian(Coords spherical);

Coords carthesianToSpherical(Coords carthesian);

double scalarProduct(Coords v1, Coords v2); //or dot procuct

Coords vectorProduct(Coords v1, Coords v2); //or cross product

double tripleProduct(Coords v1, Coords v2, Coords v3);

double norm(Coords v1);

double distance(Coords p1, Coords p2); //Euclidean metric

Coords operator*(double scalar, Coords vector);


#endif
