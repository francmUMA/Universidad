M = 100*1000;
m = 1;
K = 4*(pi^2)*M;
B = 4*pi*M;
F = m*9.8;
num = 1/M;
den = [1 B/M K/M];
sis = tf(num, den);
step(F*sis);
%% Apartado D
M = 100*1000;
m = 1;
K = 4*(pi^2)*M;
B = 2*pi*M;
F = m*9.8;
num = 1/M;
den = [1 B/M K/M];
sis = tf(num, den);
step(F*sis);
%% Apartado E
M = 100*1000;
m = 1;
K = 4*(pi^2)*M;
B = 0;
F = m*9.8;
num = 1/M;
den = [1 B/M K/M];
sis = tf(num, den);
step(F*sis);
%% Apartado F
M = 100*1000;
m = 200*1000;
K = 4*(pi^2)*M;
B = 0;
F = m*9.8;
num = 1/M;
den = [1 B/M K/M];
sis = tf(num, den);
step(F*sis);