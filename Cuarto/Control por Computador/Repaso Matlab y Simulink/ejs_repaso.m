%%Ejercicio1%%
t = 0:0.001:4;
figure(1);

subplot(3,1,1);
unitstep = t >= 0 & t<=1;
r = t.*unitstep;
f1 = 5*(1-exp(-2*t)) + r;
plot(t, f1);

subplot(3,1,2);
f2 = 5*(1-exp(-2*t));
plot(t, f2);
hold on;
plot(t, r, 'g*');
hold off;

subplot(3,1,3);
r0 = 0 .* r;
r2 = 2 .* r;
r3 = 3 .* r;
r4 = 4 .* r;
r5 = 5 .* r;
r6 = 6 .* r;
plot(t, f2);
hold on;
plot(t, r0, 'g.');
plot(t, r, 'r*');
plot(t, r2, 'mo');
plot(t, r3, 'k+');
plot(t, r4, 'ys');
plot(t, r5, 'cd');
plot(t, r6, 'gv');
hold off;

%% Ejercicio 2 %%
x = -5:0.01:5;
p1 = x.^2 + 5*x + 1;
p2 = 2*x.^3 + 4*x.^2 - 3;
figure(2);
plot(x, p1, 'g');
hold on;
plot(x, p2, 'b--');

raices_p1 = roots(p1);
raices_p2 = roots(p2);
plot(raices_p1, 'rx');
plot(raices_p2, 'gx');

min_p1 = min(p1);
min_p2 = min(p2);
max_p1 = max(p1);
max_p2 = max(p2);
plot(min_p1, 'ko');
plot(min_p2, 'ko');
plot(max_p1, 'ko');
plot(max_p2, 'ko');

