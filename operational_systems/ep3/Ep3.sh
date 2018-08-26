#!/bin/bash

# argumentos: traceFile espaco substitui intervalo testMode

echo "$5" > .tmpfile.tmp
echo "carrega $1" >> .tmpfile.tmp
echo "espaco $2" >> .tmpfile.tmp
echo "substitui $3" >> .tmpfile.tmp
echo "executa $4" >> .tmpfile.tmp

java Ep3 < .tmpfile.tmp


rm .tmpfile.tmp
