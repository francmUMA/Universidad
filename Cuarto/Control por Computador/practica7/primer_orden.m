M = 200;
B = 10;
F = 1.5;
num = 1/M;
den = [1 B/M];
tf_pol = tf(num,den);
tf_num = zpk(tf_pol);
ltiview('step',F*tf_pol);