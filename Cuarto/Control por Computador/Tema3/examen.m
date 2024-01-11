a2 = 6;
a1= 40;
a0 = 1000;
b= pi/6;
d = 2;
J = 6.7;
B = 3;

num = d * sin(b);
den = [a2*J (a2*B+a1*J) (a1*B+a0*J) a0*B 0];
g = tf(num,den);

% a) 67115 -> Momento en el que se vuelve inestable ya que los polos conjugados 
% más dominantes pasan al semiplano derecho
% b) Con el siguiente control integrador se puede obtener con ki = 271 y un
% polo en -1 se obtiene error nulo con OS de 0 y Ts de 30s.
% c) kcr = 67115, pcr = 

num_c = 271;
den_c = [1 +1];
c = tf(num_c, den_c);

sis = tf(conv(num_c,num),[conv(den_c,den) conv(num_c,num)]);

