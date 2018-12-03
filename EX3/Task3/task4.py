# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
sample_number = 1000000
#best_k=0
#minErr = 4
#target = 0.135
import numpy as np
import matplotlib.pyplot as plt
fx = np.loadtxt('MC.txt') [0:sample_number]
mean_fx = np.mean(fx)
f_var = np.var(fx)
fx_avg_2 = np.mean(fx)**2
Phi_k=[]
max_k=200
fx -=mean_fx
for k in range(max_k):
    f_iki = fx[:-k or None]*fx[k:]
#   f_iki = np.mean(np.array([(fx[i]-mean_fx)*(fx[i+k]-mean_fx) 
#    for i in range(len(fx)-k)]))
    Phi_k.append(np.mean(f_iki/f_var))

plt.plot(Phi_k)  
#    currErr=Phi_k-target
 #   if currErr<minErr:
  #      minErr = currErr
   #     best_k = k
