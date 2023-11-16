%% -- Primer orden sencillo -- %%
root = 1;
polinomio = poly(root);
sis = tf(1,polinomio);
pzmap(sis);
step(sis);
%% -- Segundo orden sencillo -- %%
root = [-2;0];
polinomio = poly(root);
sis = tf(1,polinomio);
pzmap(sis);
step(sis);
%% -- Segundo orden con parte compleja -- %%
root = [-0.2+5i; -0.2-5i];
polinomio = poly(root);
sis = tf(1,polinomio);
pzmap(sis);
step(sis);
%% -- Primer orden con ceros -- %%
polos = -2;
ceros = -1;
polos_poli = poly(polos);
ceros_poli = poly(ceros);
sis = tf(ceros_poli,polos_poli);
pzmap(sis);
step(sis);
%% -- Segundo orden con ceros -- %%
polos = [-0.5+0.5i; -0.5-0.5i];
ceros = 1;
polos_poli = poly(polos);
ceros_poli = poly(ceros);
sis = tf(ceros_poli,polos_poli);
pzmap(sis);
step(sis);