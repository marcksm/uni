#!/bin/bash
make clean && make
clear
echo Compiling...
echo Testing...

for pista in 500 1000 2000
do 
    for ciclistas in 10 50 120
    do 
        for i in {0..29..1}
        do
            echo "d:$pista n:$ciclistas"
            /usr/bin/time -f %M-%E 2>> resultados.out ./ep2 $pista $ciclistas u 1> /dev/null
        done
    done
done
