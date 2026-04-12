load DataRobot2.mat
t = double(getElement(data,'u').Values.Time);
u = double(getElement(data,'u').Values.Data);
p = double(getElement(data,'Position').Values.Data);
v = double(getElement(data,'Vitesse').Values.Data);
phi = double(getElement(data,'Phi').Values.Data);
y = [p v phi];