# SubShift
SubShift is a simple tool to shift .srt subtitle files from specific time points on.

## Why?
I found myself searching for a simple CLI tool that would enable me to quickly modify .srt files by putting some dead air at specific points of .srt files.
There were a few nice tools created to modify those files, but either they didn't have the option to put a delay at specific point in the subtitle file,
or they were written in JS.
I wanted to have a tool that doesn't require any runtime dependencies (like e.g. node.js).

## Building
clone this repo
```
cd SubShift
mkdir build
cd build
chmod u+x ../build.sh
../build.sh
```

The build script is simple and uses g++, so feel free to build it however else you like

## Usage
```
> ./subshift --help
SubShift is a simple tool to shift .srt subtitle files from specific time points on.
Usage: ./subshift [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i,--input TEXT             Input file (.srt)
  -o,--output TEXT            Output file (.srt)
  -b,--begin TEXT             Starting time point from which to begin the delay. Format: 0:04:20:000
  -s,--shift-by-seconds INT   Shift by n seconds forward
  -v,--verbose                Log debug info to output
```
Example:
```
./subshift -i test.srt -o test_shifted.srt -b 0:10:40:000 -s 3
```
This will delay the subtitles by 3 seconds, but only after the 0:10:40 mark.

## Future plans
* Add option to have a positive or negative delay (e.g. +10s / -10s)
* Use ffmpeg to scour the movie file for potential dead air (like a shortened fade to black), which is an often cause of needing to shift the subtitles.
* Related to the above - use those points as recomputation points from which to scan for next spoken line
(via ffmpeg and voice activation) and shift the rest of the subtitles accordingly
