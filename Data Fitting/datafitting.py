# -*- coding: utf-8 -*-
#
# Cesare De Cal
# Data Fitting Exercise 3
# Python program that can be executed to report whether particular
# python packages are available on the system.

import numpy as np
from scipy import interpolate
import pylab as py

x = np.r_[0:10:11j] # also np.linspace(0,10,11)
y = np.exp(-x/4)*x   

# Creating interpolating function by passing x and y points
f = interpolate.interp1d(x,y)
xnew = np.r_[0:10:100j]
    
py.figure(1)
py.clf()
py.plot(x,y,'ro',xnew,f(xnew),'b-')
    