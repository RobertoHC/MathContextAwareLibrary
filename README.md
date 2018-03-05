# MathContextAwareLibrary
Mathematical library that includes a series of functions with different implementations with varying precision.

## VarEMU installation

[VarEMU](https://github.com/nesl/varemu) is an emulation testbed for Variability-Aware Software that allow us to build and run application in an ARM architecture. To build and run the presented examples properly is a pre-requisite to install this tool following all the instructions in the repository.

## Quick build and run

These commands build and run the mathematical library for a basic c application allowing to use all the library functions inside the source code (*main.c*).

```
make clean
make
make main
```

To execute the generated file *main*, it must be done in an ARM architecture. Follow the instructions inside the VarEMu repository to see how to set the enviroment to run this file and execute it with the following command: 

```
./main
```

To see how this library works in a bigger application, we include a fast fourier transform application (FFT) using the library. To build and run, you just need to execute the following commands:

```
cd FFT
make clean
make lib
make
```
And to execute the generated file *fft*, we use VareEMU as in the previous example and execute it with the command:

```
./fft
```
