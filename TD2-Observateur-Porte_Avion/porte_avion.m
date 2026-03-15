clear all; close all;
%% Constantes physiques

a2 = 250e3;
alpha2 = 1e9;
a0 =9.81*250e3;
alpha1 = 0.4e9;
alpha0 = 500e6;
gamma = 250e3;
beta = 60;

%% Conditions initiales
x_0         = 0;
x_dot_0     = 0;
theta_0     = 0;%pi/10;
theta_dot_0 = 0;

X_0 = [x_0;
       x_dot_0;
       theta_0;
       theta_dot_0];

%% Modèle matriciel linéarisé du système complet

A = [0 1 0 0;
     0 0 -a0/a2 0;
     0 0 0 1;
     -gamma/alpha2 0 -alpha0/alpha2 -alpha1/alpha2];

B = [0;
     1/a2;
     0;
     beta/alpha2];

C = [0 0 1 0];
D = 0;

C2 = [1 0 0 0;
     0 0 1 0];
D2 = [0;
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
poles_cmd = [-0.1
             -0.11
             -0.12
             -0.13];

K = place(A, B, poles_cmd);
H = -pinv((C) * ((A - B*K) \ B));

H2 = -pinv((C - D*K) * ((A - B*K) \ B) - D);


Ki = -2000;

%% Observabilité
Obs = obsv(A, C);
fprintf("rank(Obs) = %d\n", rank(Obs));
if rank(Obs)
    fprintf("Le système est observable.\n");
else
    fprintf("Le système n'est pas observable.\n");    
end

%% Placement des pôles observateur (inutilisé)
poles_obs = [-5 + 2i
             -5 - 2i
             -5 + 1i
             -5 - 1i];

L = place(A', C', poles_obs)';

%% Observateur avec perturbation constante

E = [0;
     0;
     1;
     0];

A_obs = [A           E; 
         zeros(1, 4) 0];
B_obs = [B; 0];
C_obs = [C2 zeros(2, 1)];
Obs_aug = obsv(A_obs, C_obs);
fprintf("rank(Obs_aug) = %d\n", rank(Obs_aug));

% inutilisé
L_obs = place(A_obs', C_obs', [-2, -2.5, -3, -3.5, -4])';

%% Observateur avec perturbation sinusoidale
omega_pert = 0.1;

A_pert = [0              1;
          -omega_pert^2  0];


E2 = [0 0;
      0 0;
      1 0;
      0 0];

A_obs2 = [A           E2;
         zeros(2, 4) A_pert];
B_obs2 = [B; 0; 0];
C_obs2 = [C2 zeros(2, 2)];

Obs_aug2 = obsv(A_obs2, C_obs2);
fprintf("rank(Obs_aug2) = %d\n", rank(Obs_aug2));

L_obs2 = place(A_obs2', C_obs2', [-2, -2.5, -3, -3.5, -4, -4.5])';

%% Retour d'état pour rejeté la perturbation sinusoidale
Bc = [0; 
      1];
A_aug = [A zeros(4, 2);
         -Bc*C A_pert];
B_aug = [B; 
         zeros(2, 1)];

Cmd_aug2 = ctrb(A_aug, B_aug);
fprintf("rank(Cmd_aug2) = %d\n", rank(Cmd_aug2));
poles_cmd2 = [poles_cmd;-3; -4];
K2 = place(A_aug, B_aug, poles_cmd2);

Kx = K2(1:4); % Gains pour les états du bateau
Kc = K2(5:6); % Gains pour la perturbation