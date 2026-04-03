
clc;clear all; close all;

%% Exemple de système SISO
A = [2,-1.105,0.92,-0.80;
     2,0,0,0;
     0,1,0,0;
     0,0,0.50,0];

B = [0.5;0;0;0];
C = [0,0,0.10,0.40];
D = 0; 


%% Expérience de génération de données 
Ts = .05;
a = 1;
N = 2^11-1;
sys_true= ss(A, B, C, D,Ts);

t = (0:N-1)*Ts;
u = idinput([N,1,1],'PRBS',[0 1],[-a a]); % entrée d'excitation PRBS
ytrue = lsim(sys_true,u);

%% Ajout de bruit sur la sortie
SNR = 20; %  rapport signal sur bruit
sigE= mean(ytrue.^2)*10^(-SNR/10);
e = sqrt(sigE)*randn(N,1); % réalization d'un bruit blanc de variance sigE
y = ytrue+e; 

%% Visualisation des signaux
figure; 
subplot(2,1,1)
plot(t,y);
ylabel('y','fontsize',14)
xlabel('t','fontsize',14)
subplot(2,1,2)
plot(t,u)
ylabel('u','fontsize',14)
xlabel('t','fontsize',14)
ylim([-a-.2 a+.2])


%% 1. Créer un objet iddata
data = iddata(y, u, Ts);
%% 2. Appliquer l'algo n4sid pour identifier un modèle d'état
nx_max = 10; % choix ordre
%model = n4sid(data, 1:nx_max);

model_o2 = n4sid(data, 2);
model_o3 = n4sid(data, 3);
model_o4 = n4sid(data, 4);
model_o5 = n4sid(data, 5);

eig_true = eig(sys_true)
eig_o2 = eig(model_o2)
eig_o3 = eig(model_o3)
eig_o4 = eig(model_o4)
eig_o5 = eig(model_o5)

tf_true = ss2tf(sys_true.A, sys_true.B, sys_true.C, sys_true.D)
tf_o2 = ss2tf(model_o2.A, model_o2.B, model_o2.C, model_o2.D)
tf_o3 = ss2tf(model_o3.A, model_o3.B, model_o3.C, model_o3.D)
tf_o4 = ss2tf(model_o4.A, model_o4.B, model_o4.C, model_o4.D)
tf_o5 = ss2tf(model_o5.A, model_o5.B, model_o5.C, model_o5.D)

step(model_o4, sys_true)

model = model_o4;

%% 3. Validation sur de nouvelles données
SNR = 20; %  rapport signal sur bruit
sigE= mean(ytrue.^2)*10^(-SNR/10);

u_val = randn(N,1); % entrée comme une réalisation de bruit blanc
y_val = lsim(sys_true, u_val); % génération de la sortie correspondante
y_val = y_val + sigE*randn(size(y_val)); % Ajout de bruit de mesure
data_val = iddata(y_val, u_val, Ts); % création d'un objet iddata

[data_model_true, FIT_true] = compare(data_val, sys_true); % système réel
[data_model_o2, FIT_o2] = compare(data_val, model_o2); % ordre 2
[data_model_o3, FIT_o3] = compare(data_val, model_o3); % ordre 2
[data_model_o4, FIT_o4] = compare(data_val, model_o4); % ordre 2
[data_model_o5, FIT_o5] = compare(data_val, model_o5); % ordre 2

data_model = data_model_o2;
FIT = FIT_o2;

%% Tracer des figures
figure;
t = data_val.SamplingInstants;
plot(t, data_val.OutputData, 'b', 'LineWidth', 2); hold on;
plot(t, data_model.OutputData, 'r--', 'LineWidth', 2);
legend('Measured', 'Model');
set(gca,'fontsize',15)
xlabel('time','FontSize',17)
ylabel('outputs','FontSize',17)
title(['Comparison $y$ vs $\hat{y}$: FIT = ' num2str(FIT)],...
'interpreter', 'latex', 'fontweight','bold','fontsize',14)
grid on;
