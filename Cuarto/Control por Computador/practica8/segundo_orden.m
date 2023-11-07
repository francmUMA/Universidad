M = 100000;
m = 100;
B = 100000;
K = 100000;
F = m*9.8;
num = 1/M;
den = [1 B/M K/M];
sis = tf(num, den);
step(F*sis);