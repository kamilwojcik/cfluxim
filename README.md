# cfluxim
A simple cosmic ray simulation tool

## More details

Only muons are implemented at the moment, but implementation of other particles is possible, if needed.  
It is precisely described in the [presentation](https://github.com/kamilwojcik/cfluxim/blob/mcord/presentation/presentation.pdf)

# Dependencies

A few classes of CERN's ROOT framework is used. See the [ROOT](https://root.cern/) website.

# Components

`CuboidGenerator.cpp` - generates particles and saving in ROOT tree.  
`FluxAnalyzer.cpp` - takes generated particles as an input and creates some histograms needed for simple quality check.  
`TrackAnalyzer.cpp` - takes generated particles as an input and performs analysis of tracks regarding defined detector geometry.

`classes` directory contains classes .h and .cpp files  
`flux_config` directory contains histograms that define muon flux

`test` directory contains not very professional, very simple tests for classes.  
`presentation` directory contains Latex presentation (code, images and pdf output)  

# Installation

instalaction bash scripts for all cpp files are provided.

Dear ROOT user, remember to source `thisroot.sh` before installation ;)

# License

MIT
