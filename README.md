# cfluxim
A simple tool for generating cosmic ray particle flux regarding the given distributions of momentum angle and energy.

## More precysely

the program generates cosmic ray muons that tasses through the cube of given edge length, in a given time.

Other kinds of particles can be defined and calculated separately - you will need to prepare two input histograms: momentum distribution and flux intensity vs zenith angle.

Output is a collection of particles with defined position and momentum vector, saved in a ROOT TTree.
(see: [TTree class reference](https://root.cern.ch/doc/master/classTTree.html)

## Dependencies

A few classes of CERN's ROOT framework is used. See the [ROOT](https://root.cern/) website.

## Installation

works fine on my computer ;) First, you need to install the [ROOT](https://root.cern.ch/downloading-root) framework. Then,
just run compileCfluxim.sh

## License

MIT
