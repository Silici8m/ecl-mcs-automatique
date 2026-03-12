%% Constantes

g = 9.81;  

% Masse du pendule (kg)
m = 0.5;  
% Longueur du pendule (m)
l = 0.3;

% Coefficient de frottement fluide (N.m.s/rad)
f = 1e-3;

%% Conditions initiales
theta_0 = pi/6; % rad
omega_0 = 0; % rad/s

%% Référence
theta_r = pi/3; % rad
fprintf("Référence : theta_r = %f\n", theta_r);

A =[0 1;
    -g/l 0];

B = [0;
     1];

C = [1 0];

% Gains PID

F = place(A, B, [-1 -2]);

G = -1/(C*(A-B*F)^(-1)*B);

Kp = 10;
Kd = 0.5;
Ki = 20;


%%
