L = 500;
Rg2 =  100;
Rg1 = 10;

num = Rg2;
den = [L Rg1+Rg2];
sis_planta = tf(num,den);
step(sis_g, 50);

%% Ejercicio 2 Simbolico %%
syms Cc Rco Re1 Re2 Lg Rg Rgp S;

sis_c = Cc / (Rco*S);
sis_h = Re1 / (Re1 + Re2);
sis_g = Rg / (Lg * S + Rg + Rgp);

sis_res = (sis_c*sis_g) / (1 + sis_c*sis_g*sis_h);
res_beauty = collect(sis_res);

%% Ejercicio 2 %%
Lg = 500;
Rgp = 10;
Rg = 100;
Cc = 0.2;
Re2 = 1000;
Re1 = 1000;
Rco = 1;

sis_num = Cc*Re1*Rg + Cc*Re2*Rg;
sis_den = [(Lg*Rco*Re1 + Lg*Rco*Re2) (Rco*Re1*Rg + Rco*Re2*Rg + Rco*Re1*Rgp + Rco*Re2*Rgp) (Cc*Re1*Rg)];
sis = tf(sis_num, sis_den);
step(sis);

