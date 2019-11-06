# -*- coding: utf-8 -*-
#
# Cesare De Cal
# Data Fitting Exercise 3
# Python program that can be executed to report whether particular
# python packages are available on the system.

import matplotlib.pyplot as plt

x = [0.0, 0.6, 1.5, 1.7, 1.9, 2.1, 2.3, 2.6, 2.8, 3.0, 3.6, 4.7, 5.2, 5.7, 5.8, 6.0, 6.4, 6.9, 7.6, 8.0]
y = [-0.80, -0.34, 0.59, 0.59, 0.23, 0.10, 0.28, 1.03, 1.50, 1.44, 0.74, -0.82, -1.27, -0.92, -0.92, -1.04, -0.79, -0.06, 1.00, 0.00]

# Increase plot size
plt.figure(dpi=130)

plt.scatter(x, y)
plt.show()
