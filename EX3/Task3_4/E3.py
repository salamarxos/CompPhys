import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def task2():
    x = np.loadtxt("10000samples.txt")
    bins = np.arange(-1, 1, 5)
    n, bins, patches = plt.hist(x, 100, density=True, facecolor='b', alpha=0.75)

    plt.xlabel(r'$x$')
    plt.ylabel(r'$p(x)\propto sin(\pi x)$')
    plt.title('Histogram of 10000 samples')
    plt.grid(True)
    plt.show()

def task3():
    data = np.loadtxt("metrosamples1000.txt", delimiter=',')
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(data[:, 0], data[:, 1], data[:, 2], c='b')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    plt.show()

def task4():
    data1 = np.loadtxt("task4.txt", delimiter=',')
    data2 = np.loadtxt("block.txt", delimiter=',')
    f, (ax1, ax2) = plt.subplots(1, 2)
    ax1.plot(data1[:, 0], data1[:, 1], 'b')
    ax1.set_xlabel(r'$k$')
    ax1.set_ylabel(r'$\Phi_k$')
    ax1.set_title('Evaluation of correlation function')

    ax2.plot(data2[:, 0], data2[:, 1], 'r*')
    ax2.set_xlabel(r'block size')
    ax2.set_ylabel(r's')
    ax2.set_title('Block averaging')

    plt.show()

#task2()
#task3()
task4()
