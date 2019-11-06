# -*- coding: utf-8 -*-
#
# Cesare De Cal
# Data Fitting Exercise 3
# Python program that can be executed to report whether particular
# python packages are available on the system.

import numpy as np
import scipy
import matplotlib.pyplot as plt

x = [0.0, 0.6, 1.5, 1.7, 1.9, 2.1, 2.3, 2.6, 2.8, 3.0, 3.6, 4.7, 5.2, 5.7, 5.8, 6.0, 6.4, 6.9, 7.6, 8.0]
y = [-0.80, -0.34, 0.59, 0.59, 0.23, 0.10, 0.28, 1.03, 1.50, 1.44, 0.74, -0.82, -1.27, -0.92, -0.92, -1.04, -0.79, -0.06, 1.00, 0.00]

# Increase plot size
plt.figure(dpi=130)

# coefficients
lambdas = [-0.530105183842687, 0.837166463073442, -2.720645879111871, -0.785685549556168]

def basisFunction(x, i):
    return scipy.special.binom(3, i)*pow(x, i)*pow(1-x, 3-i)

def myFunction(x):
    firstTerm = lambdas[0]*basisFunction(x, 0)
    secondTerm = lambdas[1]*basisFunction(x, 1)
    thirdTerm = lambdas[2]*basisFunction(x, 2)
    fourthTerm = lambdas[2]*basisFunction(x, 3)
    return firstTerm + secondTerm + thirdTerm + fourthTerm

linSpace = np.linspace(min(x), max(x), 1000)

functionYValues = []

for i, val in enumerate(linSpace): 
    functionYValues.append(myFunction(val))

plt.scatter(x, y)
plt.plot(linSpace, functionYValues)
plt.show()
