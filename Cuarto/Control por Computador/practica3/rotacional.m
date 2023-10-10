clear;
close all;

j1 = 1;
j2 = 1;
t_step = 1;
k = 1;
b1 = 1;
b2 = 1;
time_sim = 10;

out_ej2 = sim('rotacional_sim.slx', time_sim);

figure(1);
hold on;
plot(out_ej2.tout, out_ej2.phi2, 'g');
plot(out_ej2.tout, out_ej2.phi1, 'r');
hold off;
title("Grado de rotación en el tiempo (Ejercicio 2)");
xlabel('Tiempo (s)'); ylabel('Ángulo de rotación (rad)');

k = 0.1;

out_ej3 = sim('rotacional_sim.slx', time_sim);

figure(2);
hold on;
plot(out_ej3.tout, out_ej3.phi2, 'g');
plot(out_ej3.tout, out_ej3.phi1, 'r');
hold off;
title("Grado de rotación en el tiempo (Ejercicio 3)");
xlabel('Tiempo (s)'); ylabel('Ángulo de rotación (rad/s)');

