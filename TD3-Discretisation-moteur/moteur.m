clear all; 
%% Espace d'état en temps continu
A = [-10   1;
     -0.02 -2];
B = [0;
     2];
C =  [1 0];
D = 0;
E = B;

ss = ss(A, B, C, D);

%% Paramètres d'échantillonnage (Question 1)
% Constante de temps du système
tau_min = -1/max(eig(A)); % Environ 0.5s
Ts = 0.05;

%% Espace d'état en temps discret (Question 1)

% Discrétisation
ssd = c2d(ss, Ts, 'ZOH');

Ad = ssd.A;
Bd = ssd.B;
Cd = ssd.C;
Ed = A\(expm(A*Ts)-eye(2))*E;


%% Valeurs propres (Question 2)
eigA = eig(A);
eigAd = eig(Ad);
for i = 1:size(A, 1)
    display(exp(eigA(i)*Ts)+ " ?= "+ eigAd(i))
end

%% Conception d'une loi de commande

% Controlabilité
Cmd = ctrb(A, B);
disp(['rank(Cmd) = ', rank(Cmd)])

% Calcul des gains du modèle continu
p_cmd = [-5 -6];
F = place(A, B, p_cmd);
G = - 1 / (C*inv(A - B*F)* B);

% Calcul des gains du modèle discret
p_cmd_d = exp(p_cmd*Ts);
Fd = place(Ad, Bd, p_cmd_d);
Gd = 1 / (C * ((eye(2) - (Ad - Bd*Fd)) \ Bd));

%% Observateurs
p_obs = [-20, -30];
L = place(A', C', p_obs)';


p_obs_d = exp(Ts*p_obs);
Ld = place(Ad', C', p_obs_d)';


%% Ajout d'un intégrateur
%A_aug = [A zeros(2, 1);        1 ]

Ad_aug = [Ad   zeros(2, 1);
         -Ts*C 1];
Bd_aug = [Bd;
          0];
C_aug = [1 0 0];
p_cmdi = [p_cmd -20];
p_cmdi_d = exp(Ts*p_cmdi);

Fd_aug = place(Ad_aug, Bd_aug, p_cmdi_d);

%% Simulation 
T = 5;
r = 5;
d = 10;
