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

X0 = [theta_0; omega_0];

%% Référence
theta_r = pi/3; % rad
fprintf("Référence : theta_r = %f\n", theta_r);

A =[0 1;
    -g/l -f/(m*l^2)];

B = [0;
     1/(m*l^2)];

C = [1 0];

D = 0;

%% COMMANDE

% Commandabilité
Cmd = ctrb(A, B);

fprintf("rank(Cmd) = %d\n", rank(Cmd));
if rank(Cmd) == 2
    fprintf("Le système est commandable.\n");
else
    fprintf("Le système n'est pas commandable.\n");
    return;
end

K = place(A, B, [-1 -1.5]);

fprintf("Gain commande :")
display(K)



%% OBSERVATION

% Observabilité
Obs = obsv(A, C);

fprintf("rank(Obs) = %d\n", rank(Obs));
if rank(Obs) == 2
    fprintf("Le système est observable.\n");
else
    fprintf("Le système n'est pas observable.\n");
    return;
end

L = place(A', C', [-2 -3])';


fprintf("Gain observateur :")
display(L)


A_obs = A-L*C;
B_obs = [B 0
         0 L]
C_obs = eye(2);
D_obs = 
