%% Ejercicio 1 %%
num = [1 1 0.26];
den = [1 0.925 0.2747 0.0261];
g = tf(num,den);

% Se hace estable siempre --> Todos los valores de K
% Los tiempos de establecimiento se mueven entre 0 y 22.6 segundos
% La sobreoscilación se mueve entre 0 y 3.92
% 255 se limita en el caso de tener pocos bits y elimina el error
% estacionario además de reducir a casi 0 el overshoot y el tiempo de
% establecimiento
% Un segundo orden se aproxima llevando el polo no conjugado muy a la
% izquierda, es decir, reduciendo su dominancia.

%% Ejercicio 2 %%
num = [1 1 4.25];
den = [1 3.81 5.638 3.656 0.036];
g = tf(num, den);

% K =  0 a 2.41,9.55 a inf
% Ts = 2.98 a 902
% Desde 0 a 99.99 ---> OS %
% 0.25564 --> Sigue teniendo error estacionario pero es el que mejor ratio
% OS / Ts tiene

%% Ejercicio 3 %%
num = 1;
den = conv(conv([1 0.6],[1 0.4]),[1 4]);
g = tf (num, den);