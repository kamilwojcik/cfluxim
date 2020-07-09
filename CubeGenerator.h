#ifndef CUBOIDGEN_H
#define CUBOIDGEN_H

#include "Coords.h"
#include "Momentum.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "FluxList.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Disk.h"
#include "Cylinder.h"

#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TRandom3.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>

//////////////////////////////////////////////////////////////////
// CuboidGenerator - cosmic ray particle generator
//
// Particles of cosmic radiation are generated on the walls
// of the cuboid regarding angular and energy distributions
// of a real cosmic ray.
//
// Cube size: a x b x h  [m]
//
// UP:
//                          Y  ^ 
//                             | wall1
// p1up(-a/2 ,b/2, h)__________|__________ p2up(a/2, b/2, h)
//                  |          |          |
//                  |          |          |
//            wall4 |  ceiling |          | wall2
//                  |          |Z         |
//               ---|----------+----------|--->
//                  |          |          |   X
//                  |          |          |
//                  |          |          |
//                  |__________|__________|
// p4up(-a/2, -b/2, h)         | wall3     p3up(a/2, -b/2, h)
//                             |
//
//
// SIDE:
//                           Z  ^      
//                              | ceiling
// p3up(a/2, -b/2, h) __________|__________ p2up(a/2, b/2, h)
//                   |          |          |
//                   |          |          |
//                   |          |          |
//             wall3 |    wall2 |          | wall1
//                   |          |          |
//                   |          |          |
//                   |          |          |
//               ____|__________|__________|_____> Y
// p3down(a/2, -b/2, 0)         X           p2down(a/2, b/2, 0)
//
//

class CuboidGenerator
{
    Plane ceiling, wall1, wall2, wall3, wall4;
    
    
    
    
};

#endif
