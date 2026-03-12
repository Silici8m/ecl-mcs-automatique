tau = 30e-3;
k = 126;

A = [-1/tau 0; 
     1      0];

B = [k/tau;
     0];

C = [0 1];

p_des = [-2+10i -2-10i];

K = place(A, B, p_des)

G = -(C*(A-B*K)^(-1)*B)^(-1)



A_aug = [-1/tau 0  0; 
         1      0  0;
         0      -1 0];

B_aug = [k/tau 0;
     0     0;
     0     1];


K_aug = place(A_aug, B_aug, [-1, -2, -3]);