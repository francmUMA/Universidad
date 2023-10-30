syms B1 s K1 M1 B2 K2 M2 m g U;

A = [(B1*s + M1*s^2 + K1) -K1;
        (-K1 -B1*s) (K1 + B2*s + K2 + M2*s^2)                                      
];

E = [m*g*U;0];

I = A \ E;

m = 70;
B1 = 100;
K1 = 100000;
M1 = 1000;
M2 = 5;
K2 = 34300;
B2 = 1000;