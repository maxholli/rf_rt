#!/bin/bash

for i in {5..150..1}
do
    ./two_ray.exe $i >> output.txt
done
for i in {152..250..2}
do
    ./two_ray.exe $i >> output.txt
done
for i in {255..600..5}
do
    ./two_ray.exe $i >> output.txt
done