#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct  6 15:12:34 2019

@author: cesaredecal
"""

import numpy as np
from scipy import interpolate
import pylab as py
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt

x = [-1,-0.96,-0.86,-0.79,0.22,0.50,0.93]
y = [-1.000,-0.151,0.894,0.986,0.895,0.500,-0.306]


# con interpolazione hai i
# difetti di runge
# x di ordine pari al numeri di x
# studia errore! fai vedere l'errore assoluto e relativo


xnew = np.r_[-1:1:0.001]
py.figure(1)
py.clf()
py.plot(x,y,'ro')
kind = 'slinear'
f = interpolate.interp1d(x,y,kind=kind,fill_value="extrapolate")
ynew = f(xnew)
py.plot(xnew, ynew, label=kind)

py.legend(loc='lower right')

# Compute natural cubic spline
# ‘natural’: The second derivative at curve ends are zero
s = CubicSpline(x, y, bc_type='natural')
py.plot(x,y,'ro')

fig, ax = plt.subplots(1, 1)
#ax.hold()
ax.plot(x, y, 'bo', label='Data Point')
ax.plot(xnew, s(xnew), 'k-', label='Cubic Spline', lw=1)

for i in range(x.shape[0] - 1):
    segment_x = np.linspace(x[i], x[i + 1], 100)
    # A (4, 100) array, where the rows contain (x-x[i])**3, (x-x[i])**2 etc.
    exp_x = (segment_x - x[i])[None, :] ** np.arange(4)[::-1, None]
    # Sum over the rows of exp_x weighted by coefficients in the ith column of s.c
    segment_y = s.c[:, i].dot(exp_x)
    ax.plot(segment_x, segment_y, label='Segment {}'.format(i), ls='--', lw=3)

ax.legend()
plt.show()
