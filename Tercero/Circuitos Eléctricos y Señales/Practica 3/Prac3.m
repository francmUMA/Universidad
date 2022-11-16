% --------------------------------------------------
% Pr?ctica 3. Transformada Z y de Fourier.
% Filtros Digitales FIR e IIR.
% --------------------------------------------------



% --------------------------------------------------
% 1.- Resoluci?n anal?tica de una funci?n de
% transferencia de un sistema (Filtro FIR).
% --------------------------------------------------
% H(z) = (1-0.5*z^-1)*(1+0.5*z^-1)
% (S?lo resoluci?n anal?tica, no hay que hacer nada en MATLAB
% en este primer apartado)



% --------------------------------------------------
% 2.- Script de MATLAB para calcular y aplicar
% el filtro H(z) anterior.
% --------------------------------------------------
% Frecuencias de representaci?n del filtro (en radianes)
% Utilizamos una buena resoluci?n para representarlo gr?ficamente
% (0.01 en este caso).
w = 0:0.01:pi;

% Definimos el filtro, Funci?n de transferencia H(z) con z = e^jw:
% Calculamos la fase del filtro

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

H = (1 - 0.5 * exp(-1 * 1i * w)) .* (1 + 0.5 * exp(-1 * 1i * w));
fase = angle(H);

% Normalizamos el filtro, buscando el valor m?ximo del m?dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

[H_max, p] = max(abs(H));
H_normalizada = H ./ H_max;
H_normalizada_dB = 20 * log10(abs(H_normalizada));

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

subplot(2,2,3); plot(w, H_normalizada); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('Magnitud (Hz)');

subplot(2,2,4); plot(w, H_normalizada_dB); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('Magnitud (dB)');


% Dibujamos la Figura 2:
% A) Se?al Senoidal de Entrada en funci?n del tiempo
% B) Se?al Senoidal de Entrada en funci?n de la frecuencia (Magnitud)
% C) Se?al Senoidal en funci?n del tiempo tras aplicar el filtro e IFFT
% D) Se?al Senoidal en funci?n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se?al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n? de muestras
% que el seno de entrada, que vendr? dado en la variable "longitud".
% Este n? de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser? de 0 a 2*pi espaciados "2*pi/longitud"


% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

Amplitud = 4;
%Frecuencia = 100;
Frecuencia = 50;
Fs = 800;
Ts = 1 / Fs;
Tmax = 16 / Frecuencia;
t = 0:Ts:(Tmax - Ts);
senal_1 = Amplitud * sin(2 * pi * Frecuencia * t);
longitud_1 = length(senal_1);

% Calcular la fft de la se�al para representarla en frecuencia
senal_1_fft = fft(senal_1, longitud_1);
magnitud_senal_1_fft = abs(senal_1_fft);
EjeX = linspace (0,Fs-(Fs/longitud_1),longitud_1);

% Redefinimos el filtro
w2 = 0:2*pi/longitud_1:2*pi-(2*pi/longitud_1);
H_redefinido = (1 - 0.5 * exp(-1 * 1i * w2)) .* (1 + 0.5 * exp(-1 * 1i * w2));

% Aplicamos el filtro
y_en_z = senal_1_fft .* H_redefinido;
y = ifft(y_en_z);
y_real = real(y);

% Calculamos la fft de la se�al para representarla en frecuencia
y_real_fft = fft(y, longitud_1);
magnitud_y_real_fft = abs(y_real_fft);

%Dibujar las gr�ficas
figure(2);
subplot(2,2,1); plot(t, senal_1); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,2); plot(EjeX(1:(longitud_1/2)+1), magnitud_senal_1_fft(1:(longitud_1/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

subplot(2,2,3); plot(t, y_real); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,4); plot(EjeX(1:(longitud_1/2)+1), magnitud_y_real_fft(1:(longitud_1/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

% Dibujamos la Figura 3:
% A) Se?al Senoidal de Entrada en funci?n del tiempo
% B) Se?al Senoidal de Entrada en funci?n de la frecuencia (Magnitud)
% C) Se?al Senoidal en funci?n del tiempo tras aplicar el filtro e IFFT
% D) Se?al Senoidal en funci?n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se?al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n? de muestras
% que el seno de entrada, que vendr? dado en la variable "longitud".
% Este n? de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser? de 0 a 2*pi espaciados "2*pi/longitud"
%w2 = [0:2*pi/longitud:2*pi-(2*pi/longitud)];

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Definimos los senos
frec_1 = 30;
frec_2 = 220;
Tmax = 16/frec_2;
t = 0:Ts:(Tmax - Ts);
seno1 = Amplitud * sin(2 * pi * frec_1 * t);
seno2 = Amplitud * sin(2 * pi * frec_2 * t);
seno_t = seno1 + seno2;
longitud_2 = length(seno_t);

% Calculamos la fft de seno_t para representarla en frecuencia
seno_t_fft = fft(seno_t, longitud_2);
magnitud_seno_t_fft = abs(seno_t_fft);
EjeX = linspace (0,Fs-(Fs/longitud_2),longitud_2);

% Redefinimos el filtro
w3 = 0:2*pi/longitud_2:2*pi-(2*pi/longitud_2);
H_2_redefinido = (1 - 0.5 * exp(-1 * 1i * w3)) .* (1 + 0.5 * exp(-1 * 1i * w3));

% Aplicamos el filtro
y_2_en_z = seno_t_fft .* H_2_redefinido;
y_2 = ifft(y_2_en_z);
y_2_real = real(y_2);

% Calculamos la fft de la se�al para representarla en frecuencia
y_real_2_fft = fft(y_2, longitud_2);
magnitud_y_real_2_fft = abs(y_real_2_fft);

figure(3);

subplot(2,2,1); plot(t, seno_t); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,2); plot(EjeX(1:(longitud_2/2)+1), magnitud_seno_t_fft(1:(longitud_2/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

subplot(2,2,3); plot(t, y_2_real); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,4); plot(EjeX(1:(longitud_2/2)+1), magnitud_y_real_2_fft(1:(longitud_2/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

% --------------------------------------------------
% 3.- Resoluci?n anal?tica de una funci?n de
% transferencia de un sistema (Filtro FIR).
% --------------------------------------------------
% H(z) = (1-0.5*z^-1)/(1+0.5*z^-1)
% (S?lo resoluci?n anal?tica, no hay que hacer nada en MATLAB
% en este tercer apartado)



% --------------------------------------------------
% 4.- Script de MATLAB para calcular y aplicar
% el filtro H(z) anterior.
% --------------------------------------------------
% Frecuencias de representaci?n del filtro (en radianes)
% Utilizamos una buena resoluci?n para representarlo gr?ficamente
% (0.01 en este caso).
w = 0:0.01:pi;
% Definimos el filtro, Funci?n de transferencia H(z) con z = e^jw:

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

H2 = (1 - 0.5 * exp(-1 * 1i * w)) ./ (1 + 0.5 * exp(-1 * 1i * w));
fase2 = angle(H2);
[H2_max, p2] = max(abs(H2));
H2_normalizada = H2 ./ H2_max;
H2_normalizada_dB = 20 * log10(abs(H2_normalizada));

% Dibujamos la Figura 4:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

figure(4);
subplot(2,2,1); plot(w, abs(H2)); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('|H(z)|');

subplot(2,2,2); plot(w, fase2); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('Fase[rad]');

subplot(2,2,3); plot(w, H2_normalizada); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('Magnitud (Hz)');

subplot(2,2,4); plot(w, H2_normalizada_dB); grid;
xlabel('Frecuencia[rad/muestra]'); ylabel('Magnitud (dB)');


% Dibujamos la Figura 5:
% A) Se?al Senoidal de Entrada en funci?n del tiempo
% B) Se?al Senoidal de Entrada en funci?n de la frecuencia (Magnitud)
% C) Se?al Senoidal en funci?n del tiempo tras aplicar el filtro e IFFT
% D) Se?al Senoidal en funci?n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se?al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n? de muestras
% que el seno de entrada, que vendr? dado en la variable "longitud".
% Este n? de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser? de 0 a 2*pi espaciados "2*pi/longitud"

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

Fs = 800;
Ts = 1 / Fs;
Tmax = 16 / Frecuencia;
t2 = 0:Ts:(Tmax - Ts);
EjeX = linspace (0,Fs-(Fs/longitud_1),longitud_1);

% Redefinimos el filtro para que tenga las dimensiones de la señal
H2_redefinido = (1 - 0.5 * exp(-1 * 1i * w2)) ./ (1 + 0.5 * exp(-1 * 1i * w2));

% Aplicamos el filtro
y2_z = senal_1_fft .* H2_redefinido;
y2 = ifft(y2_z);
y2_real = real(y2);

% Calculamos la fft de la se�al para representarla en frecuencia
y2_real_fft = fft(y2, longitud_1);
magnitud_y2_real_fft = abs(y2_real_fft);

figure(5);

subplot(2,2,1); plot(t2, senal_1); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,2); plot(EjeX(1:(longitud_1/2)+1), magnitud_senal_1_fft(1:(longitud_1/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

subplot(2,2,3); plot(t2, y2_real); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,4); plot(EjeX(1:(longitud_1/2)+1), magnitud_y2_real_fft(1:(longitud_1/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

% Dibujamos la Figura 6:
% A) Se?al Senoidal de Entrada en funci?n del tiempo
% B) Se?al Senoidal de Entrada en funci?n de la frecuencia (Magnitud)
% C) Se?al Senoidal en funci?n del tiempo tras aplicar el filtro e IFFT
% D) Se?al Senoidal en funci?n de la frecuencia tras aplicar el filtro
% Aplicamos el filtro sobre la se?al senoidal.
% Debemos generar un filtro igual al anterior pero con el mismo n? de muestras
% que el seno de entrada, que vendr? dado en la variable "longitud".
% Este n? de muestras debe coincidir con las de la FFT del seno de entrada,
% que ser? de 0 a 2*pi espaciados "2*pi/longitud"

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

Tmax = 16/frec_2;
t3 = 0:Ts:(Tmax - Ts);
EjeX = linspace (0,Fs-(Fs/longitud_2),longitud_2);

% Redefinimos el filtro
H2_2_redefinido = (1 - 0.5 * exp(-1 * 1i * w3)) ./ (1 + 0.5 * exp(-1 * 1i * w3));

% Aplicamos el filtro
y2_2_z = seno_t_fft .* H2_2_redefinido;
y2_2 = ifft(y2_2_z);
y2_2_real = real(y2_2);

% Calculamos la fft de la se�al para representarla en frecuencia
y2_real_2_fft = fft(y2_2, longitud_2);
magnitud_y2_real_2_fft = abs(y2_real_2_fft);

figure(6);

subplot(2,2,1); plot(t3, seno_t); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,2); plot(EjeX(1:(longitud_2/2)+1), magnitud_seno_t_fft(1:(longitud_2/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');

subplot(2,2,3); plot(t3, y2_2_real); grid;
xlabel('Tiempo[seg]'); ylabel('Amplitud');

subplot(2,2,4); plot(EjeX(1:(longitud_2/2)+1), magnitud_y2_real_2_fft(1:(longitud_2/2)+1)); grid;
xlabel('Frecuencia[Hz]'); ylabel('Magnitud');