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
theta_0     = pi/3;
theta_dot_0 = 0;

X_0 = [x_0;
       x_dot_0;
       theta_0;
       theta_dot_0];

%% Modèle matriciel linéarisé du système complet

Ac = [0 1 0 0;
     0 0 -a0/a2 0;
     0 0 0 1;
     -gamma/alpha2 0 -alpha0/alpha2 -alpha1/alpha2];

Bc = [0;
     1/a2;
     0;
     beta/alpha2];

Cc = [0 0 1 0];
Dc = 0;

Tss = [0.01, 0.2, 0.5, 2, 5, 10]; % s
Ts = Tss(3);

Ad = eye(4) + Ts*Ac; % Euler

Ad = expm(Ts*Ac);
Bd = integral(@(tau) expm(Ac*tau),0, Ts, 'ArrayValued', true)*Bc;
Cd = [0 0 1 0];

ssc = ss(Ac, Bc, Cc, Dc);
ssd = c2d(ssc, Ts);

Ad = ssd.A;
Bd = ssd.B;
Cd = ssd.C;

poles_c = [-0.1, -0.11, -0.12, -0.13];
poles_d = exp(poles_c * Ts);
Kc = place(Ac, Bc, poles_c);
Kd = place(Ad, Bd, poles_d);

Hc = -1 / (Cc * ((Ac - Bc*Kc) \ Bc));
Hd = 1 / (Cd * ((eye(4) - (Ad - Bd*Kd)) \ Bd));