#!/bin/sh
set -e
make clean
make
./batalha-espacial test/teste6 0.0017
