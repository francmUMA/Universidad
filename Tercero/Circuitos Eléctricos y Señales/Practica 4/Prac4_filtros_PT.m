% --------------------------------------------------
% Práctica 5.
% Representación de los Filtros Digitales utilizados.
% --------------------------------------------------
% Si esta variable vale 1, hacemos el filtro de Pan-Tompkins con Fs = 200 Hz.
% Si vale 0, hacemos el filtro modificado para Fs = 500 Hz.
Pan_Tompkins = 1;

% Frecuencias de representación del filtro (en radianes)
% Utilizamos una buena resolución para representarlo gráficamente
% (0.01 en este caso).
w = [0:0.01:pi];

% --------------------------------------------------
% 1.- Script de MATLAB para calcular el filtro H1(z) (pasa-bajos)
% --------------------------------------------------
% Definimos el filtro pasa bajos (H1)
if Pan_Tompkins == 1
    % Filtro pasa bajos para una Fs = 200 Hz (original de Pan-Tompkins):
    % Es un paso bajo con atenuación de -6 dB en 10 Hz (0.32 rad/muestra),
    % y -30dB en 21 Hz (0.67 rad/muestra)
    H1 = ((1.0 - exp(-1i*w*6)).^2) ./ ((1.0 - exp(-1i*w)).^2);
else
    % Filtro pasa bajos para una Fs = 500 Hz (modificado respecto al Pan-Tompkins).
    % La Fs es 2.5 veces la original, por lo que los ceros deberán situarse
    % a esa misma proporción respecto al filtro original.
    % Si el filtro era de orden 6^2, ahora debería ser (6*2.5)^2 = 15^2.
    % Es un paso bajo con atenuación de -6 dB en 10 Hz (0.13 rad/muestra),
    % y -30dB en 21 Hz (0.27 rad/muestra)
    H1 = ((1.0 - exp(-1i*w*15)).^2) ./ ((1.0 - exp(-1i*w)).^2);
end;    
% Normalizamos el filtro H1, buscando el valor máximo del módulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
[H1_max,p] = max(abs(H1));
H1_norm = H1 ./ H1_max;
% Dibujamos la Figura 1:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB
figure (1);
subplot(2,2,1); plot(w, abs(H1));
title ('A) Filtro H1 (Magnitud SIN Normalizar)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,2); plot(w, unwrap(angle(H1)));
title ('B) Filtro H1 (Fase)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Fase[rad]');
grid on;
subplot(2,2,3); plot(w, abs(H1_norm));
title ('C) Filtro H1 (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,4); plot(w, 20*log10(abs(H1_norm)));
title ('D) Filtro H1 (Magnitud en dB)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud dB');
grid on;

% --------------------------------------------------
% 2.- Script de MATLAB para calcular el filtro H4(z) (pasa-altos)
% --------------------------------------------------
% Definimos el filtro pasa bajos (H2)
if Pan_Tompkins == 1
    % Filtro pasa altos para una Fs = 200 Hz (original de Pan-Tompkins):
    % Primero definimos un filtro paso bajos con atenuación de -38 dB en 5 Hz (0.17 rad/muestra),
    % y -6dB en 2.5 Hz (0.08 rad/muestra)
    H2 = (1.0 - exp(-1i*w*32)) ./ (1.0 - exp(-1i*w));
else
    % Filtro pasa altos para una Fs = 500 Hz (modificado respecto al Pan-Tompkins).
    % Primero definimos un paso bajo con atenuación de -35 dB en 5 Hz (0.065 rad/muestra),
    % y -6dB en 2.5 Hz (0.03 rad/muestra)
    H2 = (1.0 - exp(-1i*w*80)) ./ (1.0 - exp(-1i*w));
end;
% Normalizamos el filtro H2, buscando el valor máximo del módulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
[H2_max,p] = max(abs(H2));
H2_norm = H2 ./ H2_max;
% Dibujamos la Figura 2:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB
figure (2);
subplot(2,2,1); plot(w, abs(H2));
title ('A) Filtro H2 (Magnitud SIN Normalizar)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,2); plot(w, unwrap(angle(H2)));
title ('B) Filtro H2 (Fase)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Fase[rad]');
grid on;
subplot(2,2,3); plot(w, abs(H2_norm));
title ('C) Filtro H2 (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,4); plot(w, 20*log10(abs(H2_norm)));
title ('D) Filtro H2 (Magnitud en dB)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud dB');
grid on;

% Definimos el filtro pasa altos (H3)
if Pan_Tompkins == 1
    % Filtro original Pan-Tompkins, Fs = 200 Hz
    % Restamos a un filtro pasa todo el filtro pasa bajos H2,
    % y obtenemos así el filtro pasa altos H3.
    % Le restamos el filtro H2 normalizado ya que el pasa todos es un "1" constante.
    % Quedará definimos un filtro H3 paso altos con atenuación de -6 dB en 5 Hz (0.17 rad/muestra),
    % y -30dB en 2.5 Hz (0.08 rad/muestra)
    H3 = exp(-1i*w*16) - H2_norm;
else
    % Filtro modificado, Fs = 500 Hz
    % Restamos a un filtro pasa todo el filtro pasa bajos H2,
    % y obtenemos así el filtro pasa altos H3.
    % Le restamos el filtro H2 normalizado ya que el pasa todos es un "1" constante.
    % Quedará definimos un filtro H3 paso altos con atenuación de -6 dB en 5 Hz (0.07 rad/muestra),
    % y -34dB en 2.5 Hz (0.03 rad/muestra)
    H3 = exp(-1i*w*40) - H2_norm;
end;
% Normalizamos el filtro H3, buscando el valor máximo del módulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
[H3_max,p] = max(abs(H3));
H3_norm = H3 ./ H3_max;
% Dibujamos la Figura 3:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB
figure (3);
subplot(2,2,1); plot(w, abs(H3));
title ('A) Filtro H2 (Magnitud SIN Normalizar)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,2); plot(w, unwrap(angle(H3)));
title ('B) Filtro H3 (Fase)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Fase[rad]');
grid on;
subplot(2,2,3); plot(w, abs(H3_norm));
title ('C) Filtro H3 (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,4); plot(w, 20*log10(abs(H3_norm)));
title ('D) Filtro H3 (Magnitud en dB)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud dB');
grid on;

% Definimos el filtro H4 definitivo, mezcla del pasa bajos con el pasa altos
H4 = H1_norm .* H3_norm;
% Normalizamos el filtro H4, buscando el valor máximo del módulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
[H4_max,p] = max(abs(H4));
H4_norm = H4 ./ H4_max;
% Dibujamos la Figura 4:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB
figure (4);
subplot(2,2,1); plot(w, abs(H4));
title ('A) Filtro H4 (Magnitud SIN Normalizar)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,2); plot(w, unwrap(angle(H4)));
title ('B) Filtro H4 (Fase)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Fase[rad]');
grid on;
subplot(2,2,3); plot(w, abs(H4_norm));
title ('C) Filtro H4 (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,4); plot(w, 20*log10(abs(H4_norm)));
title ('D) Filtro H4 (Magnitud en dB)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud dB');
grid on;


% --------------------------------------------------
% 3.- Script de MATLAB para calcular el filtro H5(z) (derivada)
% --------------------------------------------------
% Definimos el filtro de derivada (H5)
if Pan_Tompkins == 1
    % Filtro de derivada para una Fs = 200 Hz (original de Pan-Tompkins):
    % Presenta el máximo alrededor de 30 Hz, 28.6 Hz en realidad (0.9 rad/muestra).
    H5 = 0.1.*(2.0 + exp(-1i*w) - exp(-1i*w*3) - 2.0.*exp(-1i*w*4));
else
    % Filtro pasa bajos para una Fs = 500 Hz (modificado respecto al Pan-Tompkins).
    % La Fs es 2.5 veces la original, por lo que usamos una longitud de 2.5 veces la anterior
    % (antes era de orden 4, ahora será de orden 10).
    % Utilizamos la aproximación por mínimos cuadrados.
    % Presenta el máximo alrededor de 30 Hz, 30.2 Hz en realidad (0.38 rad/muestra),
    H5 = (5.0 + 4.0.*exp(-1i*w) + 3.0.*exp(-1i*w*2) + 2.0.*exp(-1i*w*3) + exp(-1i*w*4) ...
         - 1.0.*exp(-1i*w*6) - 2.0.*exp(-1i*w*7) - 3.0.*exp(-1i*w*8) - 4.0.*exp(-1i*w*9) - 5.0.*exp(-1i*w*10)) / 110.0;
end;    
% Normalizamos el filtro H5, buscando el valor máximo del módulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
[H5_max,p] = max(abs(H5));
H5_norm = H5 ./ H5_max;
% Dibujamos la Figura 5:
% A) Magnitud sin normalizar (lineal)
% B) Fase
% C) Magnitud normalizada entre 0 y 1
% D) Magnitud en dB
figure (5);
subplot(2,2,1); plot(w, abs(H5));
title ('A) Filtro H5 (Magnitud SIN Normalizar)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,2); plot(w, unwrap(angle(H5)));
title ('B) Filtro H5 (Fase)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Fase[rad]');
grid on;
subplot(2,2,3); plot(w, abs(H5_norm));
title ('C) Filtro H5 (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
subplot(2,2,4); plot(w, 20*log10(abs(H5_norm)));
title ('D) Filtro H5 (Magnitud en dB)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud dB');
grid on;
figure (6);
semilogx (w, 20*log10(abs(H5_norm)));
title ('Filtro H5 (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra] - LOG');
ylabel('Magnitud dB');
grid on;
