#!/bin/bash

for i in {990..850..-1}
do
    ./two_ray.exe $i >> output.txt
done
for i in {849..749..-2}
do
    ./two_ray.exe $i >> output.txt
done
for i in {749..200..-5}
do
    ./two_ray.exe $i >> output.txt
done