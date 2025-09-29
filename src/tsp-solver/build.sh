#!/bin/sh

gcc "Travelling Salesman Problem Solver.cpp" -o tsp-solver $(pkg-config allegro-5 allegro_main-5 allegro_font-5 --libs --cflags)
