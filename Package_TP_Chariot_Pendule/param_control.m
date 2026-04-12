clc
clear all;
close all;

nx = 4;

%% 1) Modèle du système
load robot_model.mat % Charger modèle à temps continu

%load model_ident.mat
%model = model2;
A = model.a;
B = model.b;
C = model.c;
D = model.d;
Ts = model.Ts;


% x =[velocity position  dphi  phi]
[ny,nx] = size(C);
nz = 1;

%s_p = [-0.5 + 0.1i, -0.5 - 0.1i, -0.8, -0.9];
%z_p = exp(Ts*s_p);

sysc = d2c(model);
[wn, zeta, vp] = damp(sysc.a);
vp(4) = -0.5;
xi = .7;
vp(2) = -wn(2)*xi+1i*wn(2)*sqrt(1-xi^2);
vp(3) = -wn(2)*xi-1i*wn(2)*sqrt(1-xi^2);

z_p = exp(Ts*vp);

%% 2) Paramètres retour d'état

K =  place(A, B, z_p); % gain de retour stabilisant
%K =  lqr(model2, Q, R);
C_cmd = [0 1 0 0];
H =  1/ (C_cmd*((eye(4) - A + B*K)\B)); % gain de précommande


%% 3) Observateur
z_po = 0.5*z_p;
L =  place(A',C', z_po)'; % gain de l'observateur




%% 4) Paramètres retour d'état intégral
% Ka = XXX; % gain stabilisant pour le système augmenté
% Kb = 0; % gain de l'anti-windup

