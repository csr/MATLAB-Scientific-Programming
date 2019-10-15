#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Cesare De Cal
Data Fitting
Exercise 3

"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
from scipy.interpolate import lagrange
from numpy.polynomial.polynomial import Polynomial

# Points provided by the chemistry experiment
# We store the x and y values in numpy arrays
x = np.array([-1, -0.96, -0.86, -0.79, 0.22, 0.50, 0.93])
y = np.array([-1.000, -0.151, 0.894, 0.986, 0.895, 0.500, -0.306])

xnew = np.linspace(-1, 1, 1000)

plt.figure(dpi=130)

#plt.title('Interpolating Polynomial')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend(loc='best')
plt.ylim(-1.3, 1.5)

# Let's first plot the points
plt.plot(x, y, 'bo', label='Experiment Data')

# Compute Interpolating Polynomial with Lagrange method
poly = lagrange(x, y)
plt.plot(xnew, poly(xnew), '-', label='Interpolating Polynomial')
np.set_printoptions(precision=100)
print('Coefficients of interpolating polynomial:', Polynomial(poly).coef)

# Calculate absolute and relative error

# Compute Natural Cubic Spline
ncspline = CubicSpline(x, y, bc_type='natural')
print('Coefficients of cubic spline:', ncspline.c)

#plt.title('Natural Cubic Spline')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend(loc='best')
plt.ylim(-1.3, 1.5)
plt.plot(xnew, ncspline(xnew), 'r', label='Natural Cubic Spline', lw=1) # what's lw=1?

# Final tweaks to plot
plt.legend(loc=1, prop={'size': 8})
plt.show()

