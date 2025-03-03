% Se?al de ECG, algoritmo de Pam-Tompkins, Mejora 1
% -----------------------------------------------------

% 1.- Cargar la se?al del ECG de un fichero externo
% -------------------------------------------------
load ('E1000000.MAT');
load ('E1040552.MAT');
load ('E1001103.MAT');
load ('E1010954.MAT');
load ('E1071230.MAT');
load ('E1140536.MAT');
load ('E1162547.MAT');
load ('E2002449.MAT');
load ('E2140221.MAT');
load ('E2202029.MAT');
load ('E2322334.MAT');
load ('e113.mat');
load ('e222.mat');
% Definimos ECG_1 como la variable de entrada con el ECG.
ECG_1 = e1000000;
% ECG_1 = e1040552;
% ECG_1 = e1001103;
% ECG_1 = e1010954;
% ECG_1 = e1071230;
% ECG_1 = e1140536;
% ECG_1 = e1162547;
% ECG_1 = e2002449;
% ECG_1 = e2140221;
% ECG_1 = e2202029;
% ECG_1 = e2322334;
% ECG_1 = e113;
% ECG_1 = e222;
% Calculamos la longitud de la secuencia
longitud = length (ECG_1);
% Creamos el intervalo de representaci?n de la se?al, en muestras
m = 0:(longitud-1);
% Frecuencia de muestreo, 500 Hz por defecto
Fs = 500;
% Resoluci?n de la se?al (periodo de muestreo), inversa de la frecuencia
Ts = 1 / Fs;
% Definimos el intervalo de tiempo de representaci?n de la se?al del ECG
t = 0:Ts:(longitud-1)/Fs;



% 2.- Eliminar el OFFSET de esta se?al del ECG.
% ---------------------------------------------
% Calculamos la ECG sin OFFSET, es decir, la centramos verticalmente en el eje Y
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

ECG_1_sinOFFSET = ECG_1 - mean(ECG_1);

% Figura 1, subplot 1
% Representamos gr?ficamente el ECG sin DC, en valores de mV y de tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
figure(1);
subplot(2,1,1); plot(t, ECG_1_sinOFFSET); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');


% 3.- Realizar un primer an?lisis en frecuencia (FFT) de toda la se?al del ECG 
% ----------------------------------------------------------------------------
% Calculamos la FFT de la se?al del ECG sin DC y
% Generamos un vector con las muestras en frecuencia para el eje X de la representaci?n
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

fft_ECG_1_sinOFFSET = fft(ECG_1_sinOFFSET, longitud);
magnitud_fft_ECG_1_sinOFFSET = abs(fft_ECG_1_sinOFFSET);

% Figura 1, subplot 2
% Dibujamos la magnitud en frecuencia del ECG sin DC
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

EjeX = linspace (0,Fs-(Fs/longitud),longitud);
subplot(2,1,2); plot(EjeX(1:(longitud/2)+1), magnitud_fft_ECG_1_sinOFFSET(1:(longitud/2)+1)); grid;
xlabel('Frecuencia(Hz)');  ylabel('|ECG|');

% 4.- Representar de nuevo la se?al del ECG sin OFFTSET y la FFT entre 0 y 35 Hz
% ------------------------------------------------------------------------------
% Figura 2, subplot 1
% Representamos gr?ficamente el ECG sin DC de nuevo, en valores de mV y de tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

figure(2);
subplot(2,1,1); plot(t, ECG_1_sinOFFSET); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');

% Figura 2, subplot 2
% Dibujamos la magnitud en frecuencia del ECG sin DC, pero s?lo entre 0 y 35 Hz
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
subplot(2,1,2); plot(EjeX(1:(longitud/16)+1), magnitud_fft_ECG_1_sinOFFSET(1:(longitud/16)+1)); grid;
xlabel('Frecuencia(Hz)');  ylabel('|ECG|');


% 5.- Aplicar un filtro pasa-bajos a la se?al del ECG (H1)
% --------------------------------------------------------
% Generamos un filtro H basado en el n? de muestras de la se?al,
% que vendr? dado en la variable "longitud".
% Este n? de muestras debe coincidir con las de la FFT de la propia se?al del ECG,
% que ser? de 0 a 2*pi espaciados "2*pi/longitud"
w = 0:2*pi/longitud:2*pi-(2*pi/longitud);
% Definimos el filtro pasa-bajos para una Fs = 500 Hz (modificado respecto al Pan-Tompkins).
H1 = (1 - exp(-15 * 1i * w)).^2 ./ (1 - exp(-1 * 1i * w)).^2;

% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Normalizamos el filtro, buscando el valor m?ximo del m?dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
[H1_max, p] = max(abs(H1));
H1_normalizado = H1 ./ H1_max;

% El valor del filtro en la frecuencia 0 es infinito,
% pero deber?a tener ganancia 1
% (al ser un filtro pasa-bajos)
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
H1_normalizado(1) = 1.0;

figure(9); subplot(2,1,1);
plot(w, abs(H1_normalizado)); xlabel('Frecuencia(rad/muestra)'); ylabel('Magnitud');
title('Filtro Pasa Bajos');

% Multiplicamos en frecuencia dato a dato
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
res1_z = fft_ECG_1_sinOFFSET .* H1_normalizado;


% Calculamos FFT inversa.
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
res1_compleja = ifft(res1_z);
res1_real = real(res1_compleja);


% Figura 3, subplot 2
% Representamos gr?ficamente la se?al de la FFT filtrada pasa-bajos
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
magnitud_res1_z = abs(res1_z);
figure(3);
subplot(2,1,2); plot(EjeX(1:(longitud/16)+1), magnitud_res1_z(1:(longitud/16)+1)); grid;
xlabel('Frecuencia(Hz)'); ylabel('|ECG|');

% Figura 3, subplot 1
% Representamos gr?ficamente la se?al en el tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

subplot(2,1,1); plot(t, res1_real); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');

% 6.- Aplicar un filtro pasa-altos a la se?al del ECG (H3)
% --------------------------------------------------------
% Definimos el filtro pasa altos para una Fs = 500 Hz (modificado respecto al Pan-Tompkins).
% Lo hacemos definiendo primero un pasa bajos Hz
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
H2 = (1 - exp(-80 * 1i * w)) ./ (1 - exp(-1 * 1i * w));

% Normalizamos el filtro H2, buscando el valor m?ximo del m?dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
[H2_max, p] = max(abs(H2));
H2_normalizado = H2 ./ H2_max;


% El valor del filtro en la frecuencia 0 es infinito,
% pero deber?a tener ganancia 1
% (al ser un filtro pasa-bajos)
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
H2_normalizado(1) = 1.0;

% Restamos a un filtro pasa todo el filtro pasa bajos H2,
% y obtenemos as? el filtro definitivo pasa altos H3.
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
H3 = exp(-40 * 1i * w) - H2_normalizado;

% Normalizamos el filtro H3, buscando el valor m?ximo del m?dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
[H3_max, p] = max(abs(H3));
H3_normalizado = H3 ./ H3_max;



figure(9); subplot(2,1,2);
plot(w, abs(H3_normalizado)); xlabel('Frecuencia(Hz)'); ylabel('Magnitud');
title('Filtro Pasa Altos');
% Multiplicamos en frecuencia dato a dato la se?al ya filtrada en el paso anterior
% por el filtro H3 pasa altos normalizado.
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
res2_z = res1_z .* H3_normalizado;

% Calculamos FFT inversa.
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
res2_compleja = ifft(res2_z);
res2_real = real(res2_compleja);

% Figura 4, subplot 2
% Representamos gr?ficamente la se?al de la FFT filtrada pasa-bajos y pasa altos
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
magnitud_res2_z = abs(res2_z);
figure(4);
%subplot(2,1,2); plot(EjeX(1:(longitud/16)+1), magnitud_fft_ECG_1_sinOFFSET(1:(longitud/16)+1)); grid; hold on;
subplot(2,1,2); plot(EjeX(1:(longitud/16)+1), magnitud_res2_z(1:(longitud/16)+1)); grid;
%hold off
xlabel('Frecuencia(Hz)'); ylabel('|ECG|');


% Figura 4, subplot 1
% Representamos gr?ficamente la se?al en el tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
subplot(2,1,1); plot(t, res2_real); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');


% 8.- Calcular la derivada a la se?al ya filtrada
% -----------------------------------------------
% Definimos el filtro que calcula la derivada del ECG filtrado
H5 = (5 + 4.*exp(-1 * 1i * w) + 3 .* exp(-2 * 1i * w) + 2 .* exp(-3 * 1i * w) + exp(-4 * 1i * w) - exp(-6 * 1i * w) - 2 .* exp(-7 * 1i * w) - 3 .* exp(-8 * 1i * w) - 4 .* exp(-9 * 1i * w) - 5 .* exp(-10 * 1i * w)) ./ 110.0;
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Normalizamos el filtro, buscando el valor m?ximo del m?dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
[H5_max, p] = max(abs(H5));
H5_normalizado = H5 ./ H5_max;

% Multiplicamos en frecuencia dato a dato la se?al ya filtrada en el paso anterior
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
res3_z = res2_z .* H5_normalizado;

% Calculamos FFT inversa.
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
res3_compleja = ifft(res3_z);
res3_real = real(res3_compleja);

% Figura 5, subplot 2
% Representamos gr?ficamente la se?al de la FFT derivada
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
magnitud_res3_real = abs(res3_z);
figure(5);
subplot(2,1,2); plot(EjeX(1:(longitud/16)+1), magnitud_res3_real(1:(longitud/16)+1)); grid;
xlabel('Frecuencia(Hz)'); ylabel('|ECG|');

% Figura 5, subplot 1
% Representamos gr?ficamente la se?al en el tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
subplot(2,1,1); plot(t, res3_real); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');


% 9.- Elevar la se?al al cuadrado muestra a muestra, en el tiempo
% ---------------------------------------------------------------
% Multiplicamos en el tiempo dato a dato la se?al ya filtrada y derivada
% ------------------------


% A RELLENAR POR EL ALUMNO
% ------------------------
res4_real = res3_real .* res3_real;

% Figura 6, subplot 1
% Representamos gr?ficamente la se?al en el tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
figure(6);
subplot(2,1,1); plot(t, res4_real); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');


% 10.- Aplicar una ventana de integraci?n a la se?al
% ---------------------------------------------
% Tiempo de la ventana de integraci?n, en segundos.
% Por defecto, 150 ms
tiempo_ventana = 0.15;
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% N? de muestras de la ventana de integraci?n
muestras_vent = round(tiempo_ventana / Ts);
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------

% Aplicar la ventana de integraci?n. CONSEJO: se puede definir como si fuera un filtro,
% y aplicar con el comando "filter" a la se?al elevada al cuadrado.
% Coeficientes del filtro:
% a = 1 (filtro FIR)
% b = (1/muestras_vent) para todos los datos de entrada de la ventana
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
a = 1;
b = (1 / muestras_vent) * ones(1,muestras_vent);
ECG_integ = filter(b,a,res4_real);


% Figura 6, subplot 2
% Representamos gr?ficamente la se?al en el tiempo
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
subplot(2,1,2); plot(t, ECG_integ); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');


% 11.- Algoritmo de detecci?n del QRS mediante umbrales
% -----------------------------------------------------
% Inicializamos los valores de "spki" y "npki"
% a partir de los "entren" primeros segundos de se?al
entren = 1;
% spki ser? 1/3 del m?ximo de la se?al integrada en ese periodo
spki = max (ECG_integ(1:entren*Fs)) / 3;
% npki ser? la mitad de la media de la se?al integrada en ese periodo
npki = mean (ECG_integ(1:entren*Fs)) / 2;
% Inicializamos el umbral "thri1" que nos indicar? si el pico
% es de ruido (<= thri1) o se?al (> thri1)
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
threshold_i1 = npki + 0.25 * (spki - npki); 

% Buscamos los picos en la se?al integrada
% (utilizar "findpeaks")
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
intervalo = 0.2*Fs;
% [picos, locs]  = findpeaks(ECG_integ); % --No mejorado--
[picos, locs]  = findpeaks(ECG_integ,'MinPeakDistance',intervalo); % --Mejora 1--
total_picos = length(picos);
% Creamos un vector relleno de ceros que indicar? si hay QRS en un punto o no
% Si hay 0 es que no hay QRS, si hay otro valor es que s? lo hay
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
qrs = zeros([1, longitud]);

% Creo un vector para llevar el control de los "thri1", "npkis" y "spkis" que tengo
% en la evaluaci?n de cada pico encontrado, y lo dibujar? junto con la se?al integrada
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
threshs = zeros([1, longitud]);
npkis = zeros([1, longitud]);
spkis = zeros([1, longitud]);

% Realizamos un blucle identificando si cada pico es de se?al o ruido,
% y tomando las acciones oportunas
for i = 1:total_picos
    % ------------------------
    % A RELLENAR POR EL ALUMNO
    % ------------------------
    pos_pico = locs(i);
    valor_pico = picos(i);
    threshs(pos_pico) = threshold_i1;
    spkis(pos_pico) = spki;
    npkis(pos_pico) = npki;
    
    if valor_pico > threshold_i1
        spki = 0.125 * valor_pico + 0.875 * spki;
        qrs(pos_pico) = valor_pico;
    else
        npki = 0.125 * valor_pico + 0.875 * npki;
    end
    threshold_i1 = npki + 0.25 * (spki - npki);   
end

% Figura 7, subplot 1
% Dibujamos la ECG integrada y el vector QRS en dos subplots
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
figure (7); subplot (2,1,1);
plot (t,ECG_integ); grid on; hold on;
thrs_positivos = threshs > 0;
spkis_positivos = spkis > 0;
npkis_positivos = npkis > 0;
qrs_positivos = qrs > 0;
plot(t(thrs_positivos), threshs(thrs_positivos), '*r'); 
plot(t(spkis_positivos), spkis(spkis_positivos), '+g'); 
plot(t(npkis_positivos), npkis(npkis_positivos), '.k');  
plot(t(qrs_positivos), qrs(qrs_positivos), '^m');
hold off;
% Figura 7, subplot 2
% Dibujamos la ECG sin DC para comprobar los sitios donde hemos encontrado complejos QRS
% ------------------------
% A RELLENAR POR EL ALUMNO
% ------------------------
subplot(2,1,2); plot(t, ECG_1_sinOFFSET); grid;
xlabel('Tiempo(s)');  ylabel('ECG(mV)');