#!/bin/bash


# 145
for i in {5..150..1}
do
    ./two_ray.exe $i 50000000 >> output3.txt 2>> errout.txt
done

# 49
for i in {152..250..2}
do
    ./two_ray.exe $i 50000000 >> output3.txt 2>> errout.txt
done

# for i in {224..250..2}
# do
#     ./two_ray.exe $i >> output3.txt 2>> errout.txt
# done

# 69 
for i in {255..600..5}
do
    ./two_ray.exe $i 100000000 >> output3.txt 2>> errout.txt
done

# 39
for i in {610..1000..10}
do
    ./two_ray.exe $i 100000000 >> output3.txt 2>> errout.txt
done