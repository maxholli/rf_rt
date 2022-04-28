#!/bin/bash

for i in {5..150..1}
do
    ./free_space.exe $i >> output.txt
    # echo $i
done
for i in {152..250..2}
do
    ./free_space.exe $i >> output.txt
    # echo $i
done
for i in {255..600..5}
do
    ./free_space.exe $i >> output.txt
    # echo $i
done