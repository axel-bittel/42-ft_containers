#!/usr/bin/env bash

source fct.sh && main $*
echo
echo "Time test : Vector"
c++ ../test_vector.cpp -I../
./a.out
echo "Time test : Map"
c++ ../test_map.cpp -I../
./a.out
rm -rf a.out