%% Constantes physiques
g = 9.81;
a = 250e3;
b = 1e9;
c = 0.4e9;
d = 500e6;
e = 250e3;
f = 60;

%% Conditions initiales
x_0         = 0;
x_dot_0     = 0;
theta_0     = pi/3;
theta_dot_0 = 0;

X_0 = [x_0;
       x_dot_0;
       theta_0;
       theta_dot_0];

%% Modèle matriciel linéarisé du système complet

A = [0    1  0    0;
     0    0  -g   0;
     0    0  0    1;
     -e/b 0  -d/b -c/b];
B = [0;
     1/a;
     0;
     f/b];
C = [1 0 0 0;
     0 0 1 0];
D = [0;
     0];

%% Placement des pôles
poles_desirees = [-0.2 + 0.2i
                  -0.2 - 0.2i
                  -0.1 + 0.1i
                  -0.1 - 0.1i];

K = place(A, B, poles_desirees)



%% Controllabilité 

Ct = ctrb(A, B);
fprintf("rank(C) = %d\n", rank(Ct));
if rank(Ct)
    fprintf("Le système est contrôlable.\n");
else
    fprintf("Le système n'est pas contrôlable.\n");    
end







%%
function X_dot = porte_avion_dyn(X, u)
x = X(0);
x_dot = X(1);
theta = X(2);
theta_dot = X(3);

X_dot(0) = x_dot;
X_dot(1) = - g * sin(theta) + 1/a * u;
X_dot(2) = theta_dot;
X_dot(3) = - e/b * cos(theta) * x - d/b * sin(theta) - c/b * theta_dot + f/b * u;
end