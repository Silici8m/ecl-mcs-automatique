data = load("data_robot_arm.mat");
u = data.u;
y = data.y;
Ts = 1;
n = length(u)
t = 0:Ts:(length(u)-1)*Ts;

prop = 0.2;
n_train = round(prop * n);
n_test = n - n_train;

u_train = u(1:n_train);
u_test = u(n_train+1:end);
y_train = y(1:n_train);
y_test = y(n_train+1:end);
t_train = t(1:n_train);
t_test = t(n_train+1:end);

disp(['Taille de u_train : ', num2str(length(u_train))]);
disp(['Taille de u_test : ', num2str(length(u_test))]);

%% Visualisation des signaux
figure; 
subplot(2,1,1)
plot(t_test,y_test);
ylabel('y','fontsize',14)
xlabel('t','fontsize',14)
subplot(2,1,2)
plot(t,u)
ylabel('u','fontsize',14)
xlabel('t','fontsize',14)
ylim([-a-.2 a+.2])


%% 1. Créer un objet iddata
data_train = iddata(y_train, u_train, Ts);
%% 2. Appliquer l'algo n4sid pour identifier un modèle d'état

nx_max = 10; % Ordre maximal du modèle
model = n4sid(data_train, nx_max);


data_val = iddata(y_test, u_test, Ts);

y_val = lsim(model, u_test);

[data_model, FIT] = compare(data_val, model);

