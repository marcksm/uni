#!/bin/bash
make clean
make
for (( i = 50; i <= 100; i = i + 5 ))
do
  echo "Testing for p = $i%... "
  ./ex10 $i > $i.dat
  echo "Generating graphs for p = $i%... "
  gnuplot -e "perc='Probabilidade de alcance $i%'; in='$i.dat'; out='$i.png'" gnuplot_in.plg
done
