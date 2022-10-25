% ----------
% PR�CTICA 2
% ----------

% 1.- Se�al de ECGç
% ----------------
% Cargar el ECG "e1071230.MAT", eliminar la componente de continua,
% y representarlo gr�ficamente en funci�n del tiempo y de la frecuencia.

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

%Cargar la se�al en la variable ECG_1
load('e1071230');
ECG_1 = e1071230;

%Calcular la longitud de la se�al
longitud = length(e1071230);

%Creamos el intervalo de tiempo
Fs = 500;
Ts = 1/Fs;
t = 0:Ts:(longitud - 1)/Fs;

%Se�al sin DC
ECG_sin_DC = e1071230 - mean(e1071230);
figure (1); subplot(2,1,1); plot(t, ECG_sin_DC);
title('Se�al ECG sin DC en el tiempo');
xlabel('Tiempo (s)');
ylabel('ECG sin DC (mV)');

%Calculamos la FFT de la se�al para representarla en frecuencia
fft_ECG_sin_DC = fft (ECG_sin_DC, longitud);
magnitud_ECG_sin_DC = abs (fft_ECG_sin_DC);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (1); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_sin_DC(1:(longitud/8)+1));
title('Se�al ECG sin DC en frecuencia');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');




% 2.- Simulaci�n de interferencia de l�nea de alimentaci�n (50 Hz)
% ----------------------------------------------------------------
% Generar una se�al senoidal de 50 Hz y 150 mV de amplitud para mezclala
% con el ECG del apartado anterior, simulando la introducci�n de ruido.
% Dibujar el resultado en funci�n del tiempo y de la frecuencia.

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

%Creaci�n de la se�al de ruido
senal_de_ruido = 150*sin(2*pi*50*t);

%Se suma con la se�al de ECG_sin_DC
ECG_mezclado = ECG_sin_DC + senal_de_ruido;

%Representacion en el tiempo
figure (2); subplot(2,1,1); plot(t, ECG_mezclado);
title('Se�al ECG sin DC con ruido en el tiempo');
xlabel('Tiempo (s)');
ylabel('ECG sin DC con ruido (mV)');

%Representacion en frecuencia
fft_ECG_mezclado = fft (ECG_mezclado, longitud);
magnitud_ECG_mezclado = abs (fft_ECG_mezclado);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (2); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_mezclado(1:(longitud/8)+1));
title('Se�al ECG sin DC con ruido en frecuencia');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');

% 3.- Ejemplo de filtro IIRNOTCH.
% -------------------------------
% Filtramos la se�al del ECG para eliminar el ruido introducido en la banda de 50 Hz
% Definimos la frecuencia que deseamos eliminar, centrada en W0
% La dividimos entre "Fs/2" porque hay que dar la frecuencia normalizada al filtro,
% es decir, un valor entre 0 y 1.
% Las frecuencias ir�n desde la 0 (0 radianes) hasta la 1 (Pi radianes, que es Fs/2).
W0 = 50/(Fs/2);
% Definimos el ancho de banda del filtro (BW), es decir, cu�nto m�s va a eliminar
% alrededor de la frecuencia base W0.
% Factor_calidad ser� un n�mero entre 0 y 100, habitualmente
% BW ser� W0 dividido entre el factor de calidad.
% Si el factor de calidad crece, la banda a filtrar se estrecha
Factor_calidad = 10;
BW = W0/Factor_calidad;
% Obtenemos los coeficientes del filtro
[b,a] = iirnotch (W0, BW);
% Mostramos el filtro, figura 3
fvtool (b,a);
% Aplicamos el filtro sobre la se�al "ECG_mezclado"
ECG_filtrado1 = filter (b,a,ECG_mezclado);
% Dibujo la se�al ECG_filtrado1 en funci�n del tiempo y de la frecuencia

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

%Representaci�n en el tiempo
figure (4); subplot(2,1,1); plot(t, ECG_filtrado1);
title('Se�al ECG sin DC con ruido de 50Hz filtrada');
xlabel('Tiempo (s)');
ylabel('ECG (mV)');

%Representacion en frecuencia
fft_ECG_filtrado1 = fft (ECG_filtrado1, longitud);
magnitud_ECG_filtrado1 = abs (fft_ECG_filtrado1);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (4); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_filtrado1(1:(longitud/8)+1));
title('Se�al ECG sin DC con ruido de 50Hz filtrada');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');

% 4.- Filtrado del ECG para eliminar la interferencia de la respiraci�n (< 1 Hz)
% ------------------------------------------------------------------------------
% Filtro iirnotch

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

%Definimos la frecuencia y el factor de calidad
frecuencia = 0.1;
factor_calidad = 0.25;

%Dividimos entre Fs/2 para normalizar
W0 = frecuencia/(Fs/2);

%Obtenemos el ancho de banda
BW = W0/factor_calidad;

%Obtenemos los coeficientes del filtro
[b,a] = iirnotch(W0,BW);

%Mostrar el filtro con fvtool
fvtool(b,a);

%Aplicamos el filtro a la se�al
ECG_filtrado2 = filter(b,a,ECG_filtrado1); 

%Representaci�n gr�fica en tiempo y frecuencia de la se�al ECG_filtrado2

%Representaci�n en el tiempo
figure (6); subplot(2,1,1); plot(t, ECG_filtrado2);
title('Se�al ECG sin DC filtrando interferencia de respiraci�n y ruido de 50Hz');
xlabel('Tiempo (s)');
ylabel('ECG (mV)');

%Representacion en frecuencia
fft_ECG_filtrado2 = fft (ECG_filtrado2, longitud);
magnitud_ECG_filtrado2 = abs (fft_ECG_filtrado2);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (6); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_filtrado2(1:(longitud/8)+1));
title('Se�al ECG sin DC filtrando interferencia de respiraci�n y ruido de 50Hz');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');


% 5.- Filtramos la se�al del ECG para eliminar la interferencia de la respiraci�n (< 1 Hz)
% (M�todo Alternativo)
% ----------------------------------------------------------------------------------------
Fstop = 0.1;         % Stopband Frequency
Fpass = 1;           % Passband Frequency
Astop = 30;          % Stopband Attenuation (dB)
Apass = 0.5;         % Passband Ripple (dB)
match = 'passband';  % Band to match exactly
% Construct an FDESIGN object and call its BUTTER method.
h  = fdesign.highpass(Fstop, Fpass, Astop, Apass, Fs);
Hd = design(h, 'butter', 'MatchExactly', match);
fvtool (Hd);
ECG_filtrado3 = filter (Hd,ECG_filtrado1);
% Dibujo la se�al ECG_filtrado3 en funci�n del tiempo y de la frecuencia

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

%Representaci�n en el tiempo
figure (8); subplot(2,1,1); plot(t, ECG_filtrado3);
title('Se�al ECG sin DC filtrando interferencia de respiraci�n y ruido de 50Hz (alternativo)');
xlabel('Tiempo (s)');
ylabel('ECG (mV)');

%Representacion en frecuencia
fft_ECG_filtrado3 = fft (ECG_filtrado3, longitud);
magnitud_ECG_filtrado3 = abs (fft_ECG_filtrado3);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (8); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_filtrado3(1:(longitud/8)+1));
title('Se�al ECG sin DC filtrando interferencia de respiraci�n y ruido de 50Hz (alternativo)');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');

% Calcular la diferencia entre ECG_filtrado1 y ECG_filtrado2
ECG_filtrado1_2 = ECG_filtrado1 - ECG_filtrado2;

%Representaci�n de dicha se�al

%Representaci�n en el tiempo
figure (9); subplot(2,1,1); plot(t, ECG_filtrado1_2);
title('Se�al diferencia ECG_filtrado1 y ECG_filtrado2 en el tiempo');
xlabel('Tiempo (s)');
ylabel('ECG (mV)');

%Representacion en frecuencia
fft_ECG_filtrado1_2 = fft (ECG_filtrado1_2, longitud);
magnitud_ECG_filtrado1_2 = abs (fft_ECG_filtrado1_2);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (9); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_filtrado1_2(1:(longitud/8)+1));
title('Se�al diferencia ECG_filtrado1 y ECG_filtrado2 en frecuencia');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');

% Calcular la diferencia entre ECG_filtrado2 y ECG_filtrado3
ECG_filtrado2_3 = ECG_filtrado2 - ECG_filtrado3;

%Representaci�n en el tiempo
figure (10); subplot(2,1,1); plot(t, ECG_filtrado2_3);
title('Se�al diferencia ECG_filtrado2 y ECG_filtrado3 en el tiempo');
xlabel('Tiempo (s)');
ylabel('ECG (mV)');

%Representacion en frecuencia
fft_ECG_filtrado2_3 = fft (ECG_filtrado2_3, longitud);
magnitud_ECG_filtrado2_3 = abs (fft_ECG_filtrado2_3);
EjeX = linspace (0,Fs-(Fs/longitud),longitud);
figure (10); subplot(2,1,2); plot(EjeX(1:(longitud/8)+1), magnitud_ECG_filtrado2_3(1:(longitud/8)+1));
title('Se�al diferencia ECG_filtrado2 y ECG_filtrado3 en frecuencia');
xlabel('Frecuencia (Hz)');
ylabel('Magnitud');

%Ejercicio 5.3
H = [1 -2 1] / [1 -1.9895 0.9895];
ceros = [1 -2 1];
polos = [1 -1.9895 0.9895];
%zplane(ceros, polos);




