#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct  6 15:12:34 2019

@author: cesaredecal

Exercise no. 3
Data Fitting

"""

import numpy as np
import pylab as py
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
from scipy.interpolate import lagrange

# Points provided by the chemistry experiment
# We store the x and y values in numpy arrays
x = np.array([-1, -0.96, -0.86, -0.79, 0.22, 0.50, 0.93])
y = np.array([-1.000, -0.151, 0.894, 0.986, 0.895, 0.500, -0.306])
xnew = np.linspace(-1, 1, 1000) # For plotting

# Draw the points
py.plot(x, y, 'bo', label='Point')

# Compute interpolating polynomial with Lagrange method
poly = lagrange(x, y)
plt.plot(xnew, poly(xnew), 'r', label='Interpolating Polynomial')

# Compute natural cubic spline
# ‘natural’: The second derivative at curve ends are zero
s = CubicSpline(x, y, bc_type='natural')

plt.plot(xnew, s(xnew), 'k-', label='Natural Cubic Spline', lw=1)

plt.legend()
plt.show()
