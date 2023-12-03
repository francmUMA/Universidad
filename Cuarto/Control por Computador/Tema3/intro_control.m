%% Ejercicio 1 %%
L = 500;
Rg2 =  100;
Rg1 = 10;

num = Rg2;
den = [L Rg1];
sis_g = tf(num,den);

step(sis, 50);


