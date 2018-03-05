## MathContextAwareLibrary
Mathematical library that includes a series of functions with different implementations with varying precision.

# Quick build and run

These commands build and run the mathematical library for a basic c application allowing to use all the library functions inside the source code (main.c).

```
make clean
make
make main
./main
```

To see how this library works in a bigger application, we include a fast fourier transform application (FFT) using the library. To build and run, you just need to execute the following commands:

```
cd FFT
make clean
make lib
make main
./fft
```
