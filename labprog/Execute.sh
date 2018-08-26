#!/bin/sh
set -e
make clean
make
./batalha-espacial test/teste 0.017
