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
potencias = [2, 4, 8, 16, 32];
%plot(X, Y);
%xlabel('Blocksize'); ylabel('Tiempo (s)');

%% Ejercicio 6 de la práctica de arquitectura de computadores
size_matriz = [64, 128, 256, 512, 1024];
% Y2 = [1.569190601,	1.33495935,	1.28440367,	1.612149533,	1.604827586];
% Y4 = [1.889937107,	1.759285714,	2.058823529,	2.284768212,	2.458012042];
% Y8 = [2.453061224,	2.518404908,	3.442622951,	4.016298021,    5.080786026];
% Y16 = [1.157996146,	1.259202454,	2.1,	2.623574144,	2.426738972];
% Y32 = [1.108856089,	1.216897233,	2.176165803,	2.457264957,	2.015242054];

%plot(X, Y2);
%hold on;
%plot(X, Y4);
%plot(X, Y8);
%plot(X, Y16); 
%plot(X, Y32);
%hold off;
%xlabel('Tamaño de Matriz'); ylabel('Speed Up respecto Naïve');

%% Ejercicio 6 y 7 de la practica 4 de arquitectura de computadores
factor_2 = [1.742028986,	1.642,	1.505916099,	1.671511628,	1.850217462];
factor_4 = [2.262801205,	2.099410452,	2.025416078,	2.047477745,	2.102077687];
factor_8 = [2.639588558,	2.418275209,	2.295081967,	2.247557003,	2.515974873];
factor_16 = [2.634035597,	2.495946494,	2.610316967,	2.164366374,	2.631204319];
factor_32 = [6.559703122,	5.349114996,	5.009302991,	4.901682897,	6.249964748];
factor_256 = [1.505916099, 2.025416078, 2.295081967, 2.610316967, 5.009302991];
figure(1);
plot(potencias, factor_256);
xlabel('Factor de Desenrolle'); ylabel('Factor de Mejora');

figure(2);
plot(size_matriz, factor_2);
hold on;
plot(size_matriz, factor_4);
plot(size_matriz, factor_8);
plot(size_matriz, factor_16);
plot(size_matriz, factor_32);
hold off;
xlabel('Tamaño de la matriz'); ylabel('Factor de Mejora');
