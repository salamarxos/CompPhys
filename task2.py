# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
import matplotlib.pyplot as plt

randoms=np.random.uniform(0,2/np.pi,1000)
draws_px=[]
fx=[]
px=[]
hist = []
#fx=np.multiply(draws_px,(1-draws_px))
#px=np.sin(np.pi* draws_px)
for i in range(len(randoms)): 
    draws_px.append(np.arccos(1-np.pi * randoms[i])/np.pi)
   # draws_px.append(np.arccos(1-np.pi * randoms[i])/np.pi)
for i in range(len(draws_px)):
    fx.append(draws_px[i]*(1-draws_px[i]))
for i in range(len(fx)):
    px.append(np.sin(np.pi* draws_px[i]))
   # samples.append((fx/px))
for i in range(len(fx)):
    hist.append(draws_px[i]*fx[i]/px[i])
fx = np.average(fx)
px = np.average(px)

results = np.average(hist)

plt.hist(hist, bins=20)  # arguments are passed to np.histogram
plt.title("Histogram with 'auto' bins")
plt.show()