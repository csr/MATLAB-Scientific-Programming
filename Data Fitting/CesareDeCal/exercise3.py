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

# Create array of 1000 equi-distant points
xnew = np.linspace(min(x), max(x), 1000)

# Increase plot size
plt.figure(dpi=130)

# Set axis labels
plt.xlabel('x')
plt.ylabel('f(x)')

# Let's first plot the points
plt.plot(x, y, 'bo', label='Data')

# Compute Interpolating Polynomial with Lagrange method
poly = lagrange(x, y)
print('Lagrange Polynomial:\n', poly)

plt.plot(xnew, poly(xnew), '-', label='Interpolating Polynomial')

# Get max precision possibile
np.set_printoptions(precision=100)

# Print coefficients
print('Coefficients of interpolating polynomial:', Polynomial(poly).coef)

# Compute Natural Cubic Spline
ncspline = CubicSpline(x, y, bc_type='natural')
print('Coefficients of cubic spline:', ncspline.c)

# Make y axis a  little taller to show legend
plt.ylim(-1.3, 1.7)
plt.plot(xnew, ncspline(xnew), 'r', label='Natural Cubic Spline')

# Final tweaks to plot
plt.legend(loc=1, prop={'size': 8})
plt.show()