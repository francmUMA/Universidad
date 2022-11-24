% Scripts para comprobar soluciones de los ejercicios del tema 2.

%% Ejercicio 2.1.2 
%num = [1 2 4];
%den = [4 0 0];
%zplane(num, den);

%% Ejercicio 1.2 de la practica 3
%num = [1 -0.5];
%den = [1 0.5];
%zplane(num, den);

%% Ejercicio 1.3 de la practica 3
%X = [0,(pi/4),(pi/2),(3*pi/4),pi];
%Y = [1,0.5267,1,1.8987,3];
% plot(X, Y);

%% Ejercicio 5 de la práctica de arquitectura de computadores
%Y = [0.0327, 0.0204, 0.0122, 0.02, 0.0193];
%X = [2, 4, 8, 16, 32];
%plot(X, Y);
%xlabel('Blocksize'); ylabel('Tiempo (s)');

%% Ejercicio 6 de la práctica de arquitectura de computadores
X = [64, 128, 256, 512, 1024];
Y2 = [1.569190601,	1.33495935,	1.28440367,	1.612149533,	1.604827586];
Y4 = [1.889937107,	1.759285714,	2.058823529,	2.284768212,	2.458012042];
Y8 = [2.453061224,	2.518404908,	3.442622951,	4.016298021,    5.080786026];
Y16 = [1.157996146,	1.259202454,	2.1,	2.623574144,	2.426738972];
Y32 = [1.108856089,	1.216897233,	2.176165803,	2.457264957,	2.015242054];

plot(X, Y2);
hold on;
plot(X, Y4);
plot(X, Y8);
plot(X, Y16); 
plot(X, Y32);
hold off;
xlabel('Tamaño de Matriz'); ylabel('Speed Up respecto Naïve');

%% Calculo de la funcion de transferencia del ejercicio a entregar
