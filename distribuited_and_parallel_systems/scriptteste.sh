#!/bin/bash
rm *.ppm;
make && for x in `ls entradas`; do
    echo $x;
    ./EP entradas/$x out$x 1 1;
done;
