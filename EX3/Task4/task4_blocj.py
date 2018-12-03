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
f_var = np.var(fx)
s = []
maxB=4000
blockStep = 100
for l in range(0,maxB,blockStep):
    print(str((l+1)/maxB)+" % completed")
    B = (l+1)
    Fj=[]
    for j in range(int(sample_number/B)):
        temp = []
        for i in range(B):
            temp.append(fx[i+(j-1)*B])
        Fj.append(np.mean(np.array(temp)))
    s.append(B*np.var(Fj)/np.var(fx))
    
plt.scatter(np.arange(maxB,blockStep),s)