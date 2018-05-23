#!/bin/sh
#PBS -l select=1:ncpus=1
#PBS -N log-n
#PBS -j oe
cd ${PBS_O_WORKDIR}

./a.out
