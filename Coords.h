#ifndef COORDS_H
#define COORDS_H

#include <iostream>
#include <cmath>

enum class eCoordinateSystem
{
    polar = 0,
    carthesian = 1
};

class Coords
{
        eCoordinateSystem coord_system;
        double a1, a2, a3;   //in polar: r, phi, theta; in carthesian: x, y, z
    
        void CheckRadius();
        
    public:
        void SetSystem(eCoordinateSystem system);
        void SetCoords(double c1, double c2, double c3);
        void Move(double c1, double c2, double c3);
        
        void Print();
        eCoordinateSystem GetCoordinateSystem();
        
        double operator[](int index);
        const Coords& operator=(const Coords &instance_to_copy);
    
        Coords(double x=0, double y=0, double z=0, eCoordinateSystem system  = eCoordinateSystem::carthesian);
        Coords(const Coords& instance_to_copy);
};

Coords polarToCarthesian(Coords polar);

Coords carthesianToPolar(Coords carthesian);


#endif
