data = load("data.txt");
t = data(:,1)*1e-3;
u = data(:,2);
v = data(:,3);

figure
subplot(2,1,1);
plot(t,u);
title("tension");
subplot(2,1,2);
plot(t,v);
title("vitesse");