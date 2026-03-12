%% Constantes physiques
g = 9.81;
a = 250e3;
b = 1e9;
c = 0.4e9;
d = 500e6;
e = 250e3;
f = 60;

A_pa = [0 1;
        -d/b -c/b];
B_pa = [0;
        f/b];
C_pa = [1 0];
D_pa = 0;