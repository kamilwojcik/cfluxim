# cfluxim
A simple cosmic ray simulation tool

## More precysely

It is precisely described in the `presentation.pdf' file in `presentation' directory

## Dependencies

A few classes of CERN's ROOT framework is used. See the [ROOT](https://root.cern/) website.

## Structure

CuboidGenerator.cpp - generates particles and saving in ROOT tree.
FluxAnalyzer.cpp - generates some histograms needed for simple quality check of generated particles.
TrackAnalyzer.cpp - analysis of tracks regardint defined detector geometry.

`test' directory contains not very professional, very simple tests for classes.
`presentatyon' directory contains Latex presentation (code, images and pdf output)

## Installation

instalaction bash scripts for all cpp files are provided. Please update the file paths inside before using it!
Dear ROOT user, remember to source `thisroot.sh' before installation ;)

## License

MIT
