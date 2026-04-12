# 
# Robot
#
# Yannick Desplanques - 20220316
import numpy as np
import matplotlib.pyplot as plt

from math import pi, sqrt, cos, sin

# –––– Initialisation ––––––––––––––––––––––––––––––––––––––––––––-
# Conditions initiales
lambda0 = 0.      # position initiale lambda
phi0 = pi/2       # position initiale phy
dlambda0 = 0.     # vitesse initiale
dphi0 = 0.
#
# Discretisation temporelle et definition de l’intervalle d’etude
t0 = 0.          # instant initial
it = 4.          # intervalle d’etude
h = 0.0005       # pas de temps
#
# Initialisation des variables ––––––––––––––––––––––––––––––––––––-
#
t=[t0]
y = np.empty((1,4))
y[0,:] = [lambda0,phi0,dlambda0,dphi0]
#
#
# Définition du système différentiel f(t) ––––––––––––––––––––––––––                
# 
def f(t,y): 
  # Donnees
  g = 9.81    # pesanteur
  # Caracteristiques du robot (Unites SI)
  mb = .5     # masse base kg
  mp = 0.070  # masse portique+parralèlogramme kg (70g = 30g base + 40g portique ?)
  mc = .100   # masse charge kg
  d  = .130   # m longueur bras charge DGc

  # caracteristiques moteur chenille
  # I = .000366  # kg.m2 Inertie rapporté à la roue : me = I/r2
  # me = .432    # kg masse équivalente pour chaque moteur de chenille
  # 
  a1 = .05     # N.m/V
  b1 = .0233   # N.m.s/rd
  u1 = 0#9.      # V Tension nominale
  r = 0.0291   # m rayon primitif roue chenille

 # masse totale du robot
  ms = mb+mp+mc  # kg masse totale du robot 

  #
  # Position
  lamda=y[0]
  phi=y[1]
  #
  # Equations differentielles en position
  dlambda=y[2]
  dphi=y[3]
 
  # Force motrice chenilles
  Fc=0#2/r*(a1*u1-b1*dlambda/r)
  #F=0.
  #
  # Equations differentielles en vitesse
  ddlambda = ( Fc/mc          + d*dphi**2*sin(phi)          + g*sin(phi)*cos(phi) ) / (ms/mc-cos(phi)**2)
  ddphi   = -( Fc*cos(phi)/mc + d*dphi**2*cos(phi)*sin(phi) + ms/mc*g*sin(phi)    ) / (ms/mc-cos(phi)**2) / d
 
  return np.array([dlambda,dphi,ddlambda,ddphi])
#
# Méthode Runge Kutta 4 –––––––––––––––––––––––––––––––––––––––––––-
# 
def rk4(y,h,t):
  m1 = f(t,y)
  m2 = f(t+h/2,y+h/2*m1) 
  m3 = f(t+h/2,y+h/2*m2)
  m4 = f(t+h,y+h*m3)
  return y + (h/6)*(m1 + 2*m2 + 2*m3 + m4)
#
# Résolution –—————————–———————–———————––––––––––––––––––––––––––––-
#
i = t0+h
while i < t0 + it:
  y = np.vstack((y,rk4(y[-1,:],h,t[-1]) ))
  t = np.hstack((t,t[-1]+h))
  
  i += h

# 
test = ["Demarrage au repos va u1=9V"] 
np.savetxt(test[0]+'.csv',y,delimiter=';') 

 
# Graph des résultats –––––––––––––––––––––––––––––––––––––––––––––-
fig1 = plt.figure(1)
title = [test[0]]
scale = [1,.1,1,.1]
color = ['r','c','b','g']
label = ["lambda [m]","phi [10*rad]","dlambda [m/s]","dphi [10*rad/s]"]
for i in range(0,2):
 plt.plot(t,y[:,i]*scale[i],color[i],label=label[i])
plt.legend()
plt.title(title[0])
plt.xlabel('Time [s]')
plt.savefig(title[0]+'.png',
            dpi=300, bbox_inches='tight',pad_inches=0.1)

plt.show()