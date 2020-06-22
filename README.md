# cfluxim
A simple tool for generating cosmic ray particle flux regarding the given distributions of momentum angle and energy.
NOT READY YET!

## What this tool can do

It calculates the number of cosmic ray particles coming from a given solid angle and passing through a surface or a cube, regarding the zenith angle.

The momentum magnitude is randomly generated using cumulative distribution historgam. The angular momentum coordinates are generated randomly within a given range.

Each kind of particles can be defined and calculated separately.

Output is a collection of particles with defined position and momentum vector, saved as a root tree.
(see: [TTree class reference](https://root.cern.ch/doc/master/classTTree.html)

## Dependances

A few classes of CERN's ROOT framework is used. See the [ROOT](https://root.cern/) website.

## Installation

works fine on my computer ;) First, you need to install the [ROOT](https://root.cern.ch/downloading-root)
just run compileCfluxim.sh

## License

MIT
