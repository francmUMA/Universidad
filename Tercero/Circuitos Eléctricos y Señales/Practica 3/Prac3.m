% --------------------------------------------------
% Pr�ctica 3. Transformada Z y de Fourier.
% Filtros Digitales FIR e IIR.
% --------------------------------------------------



% --------------------------------------------------
% 1.- Resoluci�n anal�tica de una funci�n de
% transferencia de un sistema (Filtro FIR).
% --------------------------------------------------
% H(z) = (1-0.5*z^-1)*(1+0.5*z^-1)
% (S�lo resoluci�n anal�tica, no hay que hacer nada en MATLAB
% en este primer apartado)



% --------------------------------------------------
% 2.- Script de MATLAB para calcular y aplicar
% el filtro H(z) anterior.
% --------------------------------------------------
% Frecuencias de representaci�n del filtro (en radianes)
% Utilizamos una buena resoluci�n para representarlo gr�ficamente
% (0.01 en este caso).
w = 0:0.01:pi;

% Definimos el filtro, Funci�n de transferencia H(z) con z = e^jw:
% Calculamos la fase del filtro

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

H = (1 - 0.5 * exp(-1 * 1i * w)) .* (1 + 0.5 * exp(-1 * 1i * w));
fase = angle(H);

% Normalizamos el filtro, buscando el valor m�ximo del m�dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Dibujamos la Figura 1:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% d) Magnitud en dB

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
figure(1); 

subplot(2,2,1); plot(w, abs(H)); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('|H(z)|');

subplot(2,2,2); plot(w, fase); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('Fase[rad]');


% Dibujamos la Figura 2:
% A) Se�al Senoidal de Entrada en funci�n del tiempo
% B) Se�al Senoidal de Entrada en funci�n de la frecuencia (Magnitud)
% C) Se�al Senoidal en funci�n del tiempo tras aplicar el filtro e IFFT
% D) Se�al Senoidal en funci�n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se�al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n� de muestras
% que el seno de entrada, que vendr� dado en la variable "longitud".
% Este n� de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser� de 0 a 2*pi espaciados "2*pi/longitud"
w2 = [0:2*pi/longitud:2*pi-(2*pi/longitud)];

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Dibujamos la Figura 3:
% A) Se�al Senoidal de Entrada en funci�n del tiempo
% B) Se�al Senoidal de Entrada en funci�n de la frecuencia (Magnitud)
% C) Se�al Senoidal en funci�n del tiempo tras aplicar el filtro e IFFT
% D) Se�al Senoidal en funci�n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se�al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n� de muestras
% que el seno de entrada, que vendr� dado en la variable "longitud".
% Este n� de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser� de 0 a 2*pi espaciados "2*pi/longitud"
w2 = [0:2*pi/longitud:2*pi-(2*pi/longitud)];

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------



% --------------------------------------------------
% 3.- Resoluci�n anal�tica de una funci�n de
% transferencia de un sistema (Filtro FIR).
% --------------------------------------------------
% H(z) = (1-0.5*z^-1)/(1+0.5*z^-1)
% (S�lo resoluci�n anal�tica, no hay que hacer nada en MATLAB
% en este tercer apartado)



% --------------------------------------------------
% 4.- Script de MATLAB para calcular y aplicar
% el filtro H(z) anterior.
% --------------------------------------------------
% Frecuencias de representaci�n del filtro (en radianes)
% Utilizamos una buena resoluci�n para representarlo gr�ficamente
% (0.01 en este caso).
w = [0:0.01:pi];
% Definimos el filtro, Funci�n de transferencia H(z) con z = e^jw:

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Dibujamos la Figura 4:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Dibujamos la Figura 5:
% A) Se�al Senoidal de Entrada en funci�n del tiempo
% B) Se�al Senoidal de Entrada en funci�n de la frecuencia (Magnitud)
% C) Se�al Senoidal en funci�n del tiempo tras aplicar el filtro e IFFT
% D) Se�al Senoidal en funci�n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se�al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n� de muestras
% que el seno de entrada, que vendr� dado en la variable "longitud".
% Este n� de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser� de 0 a 2*pi espaciados "2*pi/longitud"
w2 = [0:2*pi/longitud:2*pi-(2*pi/longitud)];

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Dibujamos la Figura 6:
% A) Se�al Senoidal de Entrada en funci�n del tiempo
% B) Se�al Senoidal de Entrada en funci�n de la frecuencia (Magnitud)
% C) Se�al Senoidal en funci�n del tiempo tras aplicar el filtro e IFFT
% D) Se�al Senoidal en funci�n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se�al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n� de muestras
% que el seno de entrada, que vendr� dado en la variable "longitud".
% Este n� de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser� de 0 a 2*pi espaciados "2*pi/longitud"
w2 = [0:2*pi/longitud:2*pi-(2*pi/longitud)];

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

