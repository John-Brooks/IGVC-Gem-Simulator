# IGVC Gem Simulator
## Description
IGVC-Gem-Simulator is a lightweight simulation of basic vehicle dynamics and IGVC Self Drive competition scenarios. The primary motivation in creating this software is to facilitate training of a reinforcement agent which can perform the tasks of a driving agent in the competition. However, it could also be used to test a traditional driving agent algorithm. 

## Build Instructions

The simulator is dependent on tinyxml2.0 for loading .svg files. After cloning do not forget to run `git submodule init` `git submodule update`

### Windows:
1) Download the 64-bit SDL2 development library and extract it to C:\SDL2 
https://www.libsdl.org/download-2.0.php
2) "Install" SDL2 by dropping the 64-bit dll SDL2.dll in C:\Windows\System32
3) Open the cloned repository folder from VS2019 (File-->Open-->CMake...)

### Linux (not yet tested):
Typical CMake build steps. From the cloned repo directory...
1) `mkdir build`
2) `cd build`
3) `cmake ..`
4) `make`
