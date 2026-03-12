

data = load("data.txt");
t = data(:,1)*1e-3;
u = data(:,2);
v = data(:,3);


t0 = 1.01;
t1 = 1.15;
idx = (t >= t0 & t <= t1);

new_data = iddata(v(idx), u(idx), t(2)-t(1));
modele = tfest(new_data, 1);
figure
compare(new_data, modele)

p = pole(modele);

K = dcgain(modele);
tau = -1/p;


figure
subplot(3,1,1);
plot(t,u);
title("tension");
subplot(3,1,2);
plot(t,v);
title("vitesse");

new_t = linspace(0, 5, 500);
new_u = (new_t > 1 & new_t <= 2) * 5;

subplot(3,1,3);
lsim(modele, new_u, new_t)
title("modèle vitesse");

%% Asservissement en vitesse
v_ref = 600;

tau_des = 0.01;
zeta_des = 0.7;
omega_n = 1/(zeta_des*tau_des)


Kp = (2*tau/tau_des - 1)/K
Ki = omega_n^2/K
fprintf("Kp=%f\nKi=%f\n", Kp, Ki);
