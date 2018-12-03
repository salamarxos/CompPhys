# plot the h(t)
# Created by Martin Gren 2014-10-25.

# imports
import matplotlib.pyplot as plt
import numpy as np
import sys

# input file
filename = sys.argv[1]

# import data
data = np.loadtxt(filename)

# initial size of plot window
plt.figure(figsize=(8,6))

# plot
plt.hist(data[:,1],bins=30)

# labels
plt.xlabel('Generated Numbers', fontsize=20)
plt.ylabel('Frequency', fontsize=20)

# set tick fontsize
plt.yticks(fontsize=12)
plt.xticks(fontsize=12)

# display the plot

plt.savefig('hist.pdf')
plt.show()
