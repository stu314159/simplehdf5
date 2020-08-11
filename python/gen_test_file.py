#!/usr/bin/env python
"""
generate an hdf5 file in the format of a tLBM restart file to test
reading functionality in tLBM.

usage:
>>aprun ./gen_test_file.py N
N = number of data points within each data set for the test restart file

"""
import sys
sys.path.insert(1,'.')

import numpy as np
import h5py
import argparse

parser = argparse.ArgumentParser(prog="gen_test_file.py",
                                description="generate test restart file.")
parser.add_argument('N',type=int);
args = parser.parse_args()
N = args.N


# create test data sets for ux, uy, uz, and pressure.
ux = np.linspace(0.,1.,N,dtype=np.float32);
uy = np.linspace(2.,3.,N,dtype=np.float32);
uz = np.linspace(3.,4.,N,dtype=np.float32);
pressure = np.linspace(10.,20.,N,dtype=np.float32);


f = h5py.File('restart.h5','w-') # open file in write mode; fail if file exists
velo_group = f.create_group("velocity")
x_velo = velo_group.create_dataset("x",data=ux);
y_velo = velo_group.create_dataset("y",data=uy);
z_velo = velo_group.create_dataset("z",data=uz);

pres_group = f.create_group("density")
presmag = pres_group.create_dataset("rho",data=pressure)

f.close()

