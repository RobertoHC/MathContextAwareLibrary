#!/bin/sh
./fft 32 131072 > output_verylarge.txt
./fft 32 131072 -i > output_verylarge.inv.txt
