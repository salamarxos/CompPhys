#!/usr/bin/env bash

make clean
make
./monte
python3 plot_function.py hist.dat

