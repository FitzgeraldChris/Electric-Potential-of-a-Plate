import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

potentialX = np.loadtxt('potential.txt', usecols=[0])
potentialY = np.loadtxt('potential.txt', usecols=[1])
potentialV = np.loadtxt('potential.txt', usecols=[2])

numlines = len(open('potential.txt').readlines())
n = int(np.sqrt(numlines))

X = np.reshape(potentialX,(n,n))
Y = np.reshape(potentialY,(n,n))
Z = np.reshape(potentialV,(n,n))

plt.contour(X, Y, Z, colors=['blue'])
plt.show()
plt.savefig("potential.pdf")
plt.close()

#
potential = np.loadtxt('potential.txt')
x,y,v = zip(*potential)
fig = plt.figure()
ax = fig.gca(projection = '3d')
ax.plot(x,y,v,'.')
ax.set_title("Potenial around Capacitor")
#ax.legend()
plt.show()
plt.savefig("3DPotential.pdf")
plt.close()

#Plot of Electric Field X
electricfieldX = np.loadtxt('electricfield.txt', usecols= [2])
electricfieldY = np.loadtxt('electricfield.txt', usecols = [3])
Ex = np.reshape(electricfieldX,(n,n))

fig = plt.figure()
ax = fig.gca(projection = '3d')
ax.plot_surface( X, Y, Ex)
ax.set_title("Electric Field of X")
plt.show()
plt.savefig('Ex.pdf')
plt.close()

Ey = np.reshape(electricfieldY,(n,n))
#Plot of Electric Field Y
fig = plt.figure()
ax = fig.gca(projection = '3d')
ax.plot_surface( X, Y, Ey)
ax.set_title("Electric Field of Y")
plt.show()
plt.savefig('Ey.pdf')
plt.close()