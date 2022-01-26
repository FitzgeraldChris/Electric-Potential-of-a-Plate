#!/opt/local/bin/python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches

params = np.loadtxt("params.txt")
L = params[0]
Lbox = params[1]
Nplate = params[2]
Nbox = int(Lbox * Nplate)

potdata = np.loadtxt("potential.txt")
X = np.zeros((2*Nbox+1,2*Nbox+1))
Y = np.zeros((2*Nbox+1,2*Nbox+1))
Z = np.zeros((2*Nbox+1,2*Nbox+1))
for i in range(-Nbox,Nbox+1):
	for j in range(-Nbox,Nbox+1):
		X[i+Nbox,j+Nbox] = potdata[(j + Nbox) * (2 * Nbox + 1) + (i + Nbox),0]
		Y[i+Nbox,j+Nbox] = potdata[(j + Nbox) * (2 * Nbox + 1) + (i + Nbox),1]
		Z[i+Nbox,j+Nbox] = potdata[(j + Nbox) * (2 * Nbox + 1) + (i + Nbox),2]

fig = plt.figure(figsize=(8,5), dpi=80)
ax = plt.subplot(111)
CS = plt.contour(X, Y, Z, 10)
plt.clabel(CS,inline=1,fontsize=10)
plt.title(r'$V$')
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')

plt.plot([-L,L],[-1,-1],linewidth=5.0,color='Black')
plt.plot([-L,L],[1,1],linewidth=5.0,color='Black')

plt.savefig("VxyContour.pdf",dpi=72)

plt.show()








