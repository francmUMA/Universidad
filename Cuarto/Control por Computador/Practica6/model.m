syms B1 s K1 M1 B2 K2 M2 F;

A = [(B1*s + M1*s^2 + K1) (-K1 - B1*s);
        (-K1 - B1*s) (K1 + B2*s + B1*s + K2 + M2*s^2)                                      
];

E = [F;0];

I = A \ E;

m = 70;
B1 = 100;
K1 = 100000;
M1 = 1000;
M2 = 5;
K2 = 34300;
B2 = 1000;
g = 9.8;
F = m * g;

num = [B1 K1];
denom = [(M1 * M2) (B1*M1 + B1*M2 + B2*M1) (B1*B2 + K1*M1 + K1*M2 + K2*M1) (B1*K2 + B2*K1) (K1*K2)];
sis = tf(num, denom);
sisnum = zpk(sis);
pzmap(sis);


sis2num = zpk(roots(num), roots(denom), B1 /(M1*M2));
pzmap(sis2num);

k = B1 /(M1*M2);
ceros = -1000;
polos_dom = roots([1 0.5618 25.57]);
nuevos_polos = [-0.4+7i -0.4-7i];
nuevo_den = [polos_dom; nuevos_polos.'];
nuevo_sis = zpk(ceros, nuevo_den,k);
pzmap(nuevo_sis);

subplot(2,1,1);
step(m*g*sis);
title('Sistema Original');
subplot(2,1,2);
step(m*g*nuevo_sis);
title('Sistema modificado');
