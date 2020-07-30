# cfluxim
A simple cosmic ray simulation tool

## More details

Only muons are implemented at the moment, but implementation of other particles is possible, if needed.  
The tool is precisely described in the [presentation](https://github.com/kamilwojcik/cfluxim/blob/mcord/presentation/presentation.pdf)

# Dependencies

A few classes of CERN's ROOT framework is used. See the [ROOT](https://root.cern/) website.

# Components

`CuboidGenerator.cpp` - generates particles and saving in ROOT tree.  
`FluxAnalyzer.cpp` - takes generated particles as an input and creates some histograms needed for simple quality check.  
`TrackAnalyzer.cpp` - takes generated particles as an input and performs analysis of tracks regarding defined detector geometry.

`classes` directory contains classes .h and .cpp files  
`flux_config` directory contains histograms that define muon flux

`test` directory contains very simple tests for classes. I know these tests are not very professional, but it's better than nothing anyway ;)  
`presentation` directory contains Latex presentation (code, images and pdf output)  

# How to compile

Bash scripts for all components and tests are provided. Remember to source your `thisroot.sh` before compilation.

You may run one of the scripts to compile a single module or test, or:
- to compile all components at once, run `compileAllComponents.sh`
- to compile all tests at once, enter `test` directory and run `compileAllTests.sh`

# License

MIT. [Full text here.](https://github.com/kamilwojcik/cfluxim/blob/mcord/LICENSE)
