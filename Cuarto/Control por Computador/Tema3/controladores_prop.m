num = 1;
den = [4 4.8 1.76 0.192];
sis = tf(num, den);
sis_norm = zpk(sis);
step(sis);
kp = 0.22;