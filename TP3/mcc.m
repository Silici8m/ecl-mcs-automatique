clear;
tau = 30e-3;
k = 126;

A = [-1/tau 0; 
     1      0];

B = [k/tau;
     0];

C = [0 1];

D = 0;

ssc = ss(A, B, C, D);

p_des = [-10 -33];

K = place(A, B, p_des);

G = -(C*(A-B*K)^(-1)*B)^(-1);

% Modèle discret
Te = 0.8;

ssd = c2d(ssc, Te);

Ad = ssd.A;
Bd = ssd.B;
Cd = ssd.C;
p_des_d = exp(Te*p_des);

Kd = place(Ad, Bd, p_des_d);


A_aug = [-1/tau 0  0; 
         1      0  0;
         0      -1 0];

B_aug = [k/tau 0;
     0     0;
     0     1];


K_aug = place(A_aug, B_aug, [-1, -2, -3]);
Gd = 1 / (Cd * ((eye(2) - (Ad - Bd*Kd)) \ Bd));

%% Observation

pole_obs = [-50 -300];

Obs = obsv(A, C);

L = place(A', C', pole_obs)';

%% Perturabtion

Abar = [A B;
        zeros(1, 3)];

Bbar = [B;
        0];

Cbar = [C 0];

p_des = [-60 -70 -80];

Lbar = place(Abar', Cbar', p_des)';

p_des = [-10 -33 -50];
Kbar = place(Abar, Bbar, p_des);