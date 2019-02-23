#!/bin/bash

g++ solve.cpp

for i in {1..10}
do
    python ./gendata.py > upload/data${i}.in
    ./a.out < upload/data${i}.in > upload/data${i}.out
done

