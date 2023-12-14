%% EJERCICIO 1 %%
num = 1;
den_g1 = [1 1.65];
den_g2 = [1 0.35 2.4];

g1 = tf(num,den_g1);
g2 = tf(num,den_g2);
g = g1*g2;

%% EJERCICIO 2 %%
num = 2;
den_g = [1 1 4 3];
g = tf(num, den_g);