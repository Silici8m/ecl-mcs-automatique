clc;
clear; 
close all;
load Donnees_secours/EXP3.mat

nx = 4;

data_ident = iddata(y, u, Ts);

% model1 = n4sid(data_ident,nx);
model2 = ssest(data_ident,nx);
model3 = tfest(data_ident,nx);
load Donnees_secours/EXP2.mat

data_val = iddata(y, u, Ts);
compare(data_val, model2)

save("model_ident.mat", "model2");