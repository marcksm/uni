#!/bin/bash

h=$1

for arq in ls *.png; do
    echo $arq >> rel.txt
    for k in 1 2 3; do
        echo $k >> rel.txt;

        echo "compress(\"$arq\", $k)" | octave-cli;
        
        echo -e "\nbilinear" >> rel.txt
        echo "decompress(\"compressed.png\", 1, $k, $h)" | octave-cli;
        echo "calculateError (\"$arq\", \"decompressed.png\")" | octave-cli >> rel.txt;

        echo -e "\nbicubica" >> rel.txt
        
        echo "decompress(\"compressed.png\", 1, $k, $h)" | octave-cli;
        echo "calculateError (\"$arq\", \"decompressed.png\")" | octave-cli >> rel.txt;
    done;
    echo -e "\n\n\n" >> rel.txt;
done;
