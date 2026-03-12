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
C = [0 0 1 0];
D = [0;
     0];

E = [0;
     0;
     1;
     0];

d = 1;
r = 0;


%% Controllabilité 

Ct = ctrb(A, B);
fprintf("rank(Ct) = %d\n", rank(Ct));
if rank(Ct)
    fprintf("Le système est contrôlable.\n");
else
    fprintf("Le système n'est pas contrôlable.\n");    
end

%% Placement des pôles commande
poles_cmd = [-0.2 + 0.2i
                  -0.2 - 0.2i
                  -0.1 + 0.1i
                  -0.1 - 0.1i];

K = place(A, B, poles_cmd);
H = -inv((C-D*K)*(A-B*K)^(-1)*B - D);

%% Observabilité
Obs = obsv(A, C);
fprintf("rank(Obs) = %d\n", rank(Obs));
if rank(Obs)
    fprintf("Le système est observable.\n");
else
    fprintf("Le système n'est pas observable.\n");    
end

%% Placement des pôles observateur
poles_cmd = [-5 + 2i
             -5 - 2i
             -5 + i
             -5 - i];

L = place(A', C', poles_cmd)';

%% Dynamique systeme

function [dX, y] = porte_avion_dyn(X, u)
x = X(0);
x_dot = X(1);
theta = X(2);
theta_dot = X(3);

dX = zeros(4);

dX(0) = x_dot;
dX(1) = - g * sin(theta) + 1/a * u;
dX(2) = theta_dot;
dX(3) = - e/b * cos(theta) * x - d/b * sin(theta) - c/b * theta_dot + f/b * u;
end

function [dX_hat] = porte_avion_obs(X_hat, y, u)

y_hat = C*X_hat;

dX_hat = A*X_hat + B*u + L*(y-y_hat);
end 
