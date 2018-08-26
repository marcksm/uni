#!/bin/bash

funcs="[-1,1,-1,1] [1,2,3,4] [1,-2,0,0] [1,-6,8,-2,0,0] [3, 1, 0, -2, 3, 0] [1,0,0,1,0] [1,0,1,0]"

mkdir imagens

for func in $funcs; do
    echo "Função $func"
    echo "newton_basins ($func, 400)" | octave-cli
    gnuplot plot_basins.gp
    mv newton_basins.png imagens/$i.png
done;
