#!/bin/bash
make clean
make
for (( i = 50; i <= 300; i = i + 50 ))
do
  echo "Testing for V = $i... "
  ./ep5 $i > $i.dat
  echo "Generating graphs for V = $i... "
  gnuplot -e "perc='Para vértice V = $i'; in='$i.dat'; out='$i.png'" gnuplot_in.plg
done
