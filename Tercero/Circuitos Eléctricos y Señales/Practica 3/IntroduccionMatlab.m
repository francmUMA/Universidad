%%Introducci�n a Matlab CEyS
%Comandos b�sicos
clc
clear all
close all
%Asignaci�n de valores a una variable
var=5;
%Asignaci�n de n�meros "aleatorios"
var=randi([1,19],[1 6]) %genera 6 n�meros aleatorios del 1 al 19
%Redondear hacia arriba
var1=ceil(8.5);
%Redondear hacia abajo
var2=floor(8.5);
%Redondear al entero m�s cercano
var3=round(8.25)
%Funci�n exponencial
var4=exp(2)
%Funciones trigonom�tricas
var5=sin(pi/2);
var6=sind(90);
%Trabajando con vectores
x = [2 4 9 10]
x = [2,4,9,10];
x=x'
x=0:1:10;
x = linspace (1,21,41)
%Crea un vector x de 1 fila y 100 columnas con todos sus valores a 0
x = zeros (1,100)
%Crea un vector x de 1 fila y 100 columnas con todos sus valores a 1
x = ones (1,100)
%Calculando la longitud o dimensi�n de un vector x
length (x)
%Trabajando con plots
x = 1:360; y1 = sind (x); y2 = cosd (x); y3 = exp (x); y4 = x.^2; 
figure(1);
subplot (2,2,1), plot (x,y1), title ('seno') 
subplot (2,2,2), plot (x,y2), title ('coseno') 
subplot (2,2,3), plot (x,y3), title ('exponencial') 
subplot (2,2,4), plot (x,y4), title ('x^2')
%%
%Instrucci�n if
a=input('introduzca el primer dato ')
b=input('introduzca el segundo dato ')
if a>b
    salida=a;
else 
    salida=b;
end
disp(salida);
%Instrucci�n para repetici�n condicionada while
dato=input('introduzca la cantidad de terminos')
x=0
while dato>0
    x=x+1/dato;
    dato=dato-1;
end
disp(x);
%Instruccion condicionada a una secuencia for
for i=1:fin
    x=x+1/i;
end
disp(x);
%%
%%Trabajando con n�meros complejos
z=1+i*4
z=complex(1,2)
%Magnitud o m�dulo
abs(z)
%Fase o �ngulo
angle(z)
%Complejo conjugado
conj(z)
%Parte real de un n� complejo
real(z)
%Parte imaginar�a de un n� complejo
imag(z)
%%
%Manejo simb�lico
%Definici�n de variable x de tipo simb�lico
syms x; 
%Suma algebraica
3*x+2*x
%Definici�n de una funci�n simb�lica
f=3*x^2+2*x
%Evaluaci�n de una funci�n
x=2;
y=eval(f)
%%
%%Trabajando con raices de un polinomio
p=[1 3 5];
%C�lculo de las raices del polinomio
raices=roots(p)
%C�lculo de los coeficientes de un polinomio a partir de sus raices
p1=poly(raices)
%Evaluando el valor en un punto H(z)
a=[-2*sqrt(3) 2 0 0];
b=[-1 0 1];
ar=polyval(a,cos(pi/4)+i*sin(pi/4));
br=polyval(b,cos(pi/4)+i*sin(pi/4));
resp=ar/br
abs(resp)
angle(resp)
%%
%p=conv(p1,p2) %Realiza la multiplicaci�n de polinomios
%Multiplicaci�n de bloques G1(z)=z/z+2 y G2(z)=4(z+1)/z^2+4z+5
g1num=[1 0];g1den=[1 2];
g2num=[4 4];g2den=[1 4 5];
gnum=conv(g1num,g2num);
gden=conv(g1den,g2den);
zeros=roots(gnum)
polos=roots(gden)
%%
%Ejemplo c�lculo de los residuos para expandir en fracciones simples
num=[16 80];
den1=[1 4 8];
den2=[1 10];
den=conv(den1,den2);
[r,p,ki]=residue(num,den)
%Magnitud y �ngulo que forman los residuos abs() y angle()
mag=abs(r)
fase=angle(r)*180/pi
%%
%Funci�n de transferencia de un sistema
%EJEMPLOS
%Definici�n por costrucci�n directa. Definimos previamente la variable z
%como un objeto de tf
z=tf('z',-1)
H=20/((z+1)*(z+6)*(z+10))
%Definicion con tf numerador y denominador. Adem�s se indica el tiempo de
%muestreo
T=0.1
sys=tf([1 -1],[1 4 9 10],T)
pole(sys)
zero(sys)
pzmap(sys)
%Definici�n con zpk indicando zeros, polos, ganancia y el tiempo de muestreo
sys2=zpk([-1 -1],[0 -3],10,0.5)
%Ejemplo
num=[1 2];
den=[1 3 5 8];
[z,p,k]=tf2zpk(num,den)
%%
%An�lisis de la respuesta temporal utilizando Matlab
%Calcula la respuesta de un sistema ante una entrada escal�n unitario. Si la funci�n no se asigna a una variable se muestra la salida en una ventana gr�fica
%[sal,est,t]=step(num,den,rango_tiempo)
%Ejemplo G(s)=2/s+2
num=[2];
den=[1 2];
step(num,den)
%Calcula la respuesta de un sistema ante una entrada impulso unitario. Si la funci�n no se asigna a una variable se muestra la salida en una ventana gr�fica
%[sal,est,t]=impulse(num,den,rango_tiempo)
%Ejemplo G(s)=3/s-5
num=[3];
den=[1 -5];
impulse(num,den)
%%
%Diagrama de polos y ceros
%Find the zeros, poles, and gain of the system. Use eqtflength to ensure 
%the numerator and denominator have the same length. Plot the poles and zeros to verify that they are in the expected locations.
b = [2 3];
a = [1 1/sqrt(2) 1/4];
fvtool(b,a,'polezero')
[b,a] = eqtflength(b,a);
[z,p,k] = tf2zp(b,a)
text(real(z)+.1,imag(z),'Zero')
text(real(p)+.1,imag(p),'Pole')
%%
%Ejemplo de generaci�n de la Se�al escal�n e impulso
%Definimos la se�al escal�n con la funci�n zeros y ones
u=[zeros(1,10),ones(1,11)];
n=-10:10;
stem(n,u)
ylabel('Amplitud')
xlabel('Tiempo(s)')
%%
%Definimos la se�al impulso con la funci�n zeros y ones
delta=[zeros(1,10),1,zeros(1,10)];
n=-10:10;
stem(n,delta)
ylabel('Amplitud')
xlabel('Tiempo(s)')
%%
%Generar y dibujar la gr�fica de una se�al muestreada a 8 KHz
%x(t)=2sen(2*pi*400*t+pi/4)
%Frecuencia de la se�al senoidal
F0=400;
%Amplitud de la se�al senoidal
Amplitud=2;
%Fase de la se�al senoidal
phi=pi/4;
%Frecuencia de muestreo Hz
Fs=8000;
%Periodo de muestreo
Ts=1/Fs;
%Intervalo de tiempo
t=-0.002:Ts:0.002;
%Se�al senoidal a generar
x=Amplitud*sin(2*pi*F0*t+phi);
%Se�al muestreada y gr�fica
stem(t,x)

%Ejemplo 2: Muestreo de la se�al Sinc sinc(x)=sin(x)/x
%Intervalo de tiempo
t2=-0.003:Ts:0.003;
%Se�al Sinc a generar
xt=Amplitud*sinc(2*F0*t2);
figure(2);
stem(t2,xt)
%%
%Representaci�n en el dominio de la frecuencia
%Ejemplo: Se ha analizado una funci�n de una se�al peri�dica cuyos
%coeficientes b_n(seno) del desarrollo en serie de Fourier son
%b_n=2*((-1)^n)/n*pi

%Representamos con el comando stem la contribuci�n de cada uno de los
%arm�nicos desde n=1,2,3...
n=1:11;     %Intervalo de representaci�n
bn=(-1).^n*2./(n*pi);
stem(bn)
title('Espectro de frecuencias')
xlabel('n')
ylabel('b_n')
xlim([0 12])    %Indicamos el rango limitado de representaci�n en el eje X
%%
%Ejemplo suma de arm�nicos de las funciones x1=sin(t) y x2=sin(2t), x=x1+x2

%Definimos el eje temporal
t=linspace(0,5*pi,400);
x=sin(5*t)+sin(6*t);
y=2*cos(0.5*t);
hold on
plot(t,x,'b')
plot(t,y,'r','linewidth',1.5)
plot(t,-y,'r','linewidth',1.5)
hold off
xlabel('t')
ylabel('x')
set(gca,'XTick',0:pi:5*pi)
%set(gca,'XTickLabel',['0','\pi','2\pi','3\pi','4\pi','5\pi'])
%%
%Ejemplo 3: Respuesta en frecuencia de un filtro
%Definicion del filtro
num=[1 1.1];
den=[1 0 -0.1];
%Dibujamos la respuesta en frecuencia de nuestro filtro con freqz
freqz(num,den)
figure(3);
Fs=8000;
freqz(num,den,1024,Fs);
f=[0,200,400];
[H,f]=freqz(num,den,f,Fs);
%Respuesta en magnitud expresada en dB
plot(f/pi,20*log10(abs(H)))
xlabel('Normalized Frequency (\times\pi rad/sample)')
ylabel('Magnitude (dB)')
%%
% Representaci�n en frecuencia de un filtro IIR H
% Frecuencias de representaci�n del filtro (en radianes)
% Utilizamos una buena resoluci�n para representarlo gr�ficamente (0.01 en este caso).
w = [0:0.01:pi];
% Definimos el filtro:
% Funci�n de transferencia H(z) con z = e^jw
H = (1.0 - exp(-1i*w*2)) ./ (1.0 - 1.0605*exp(-1i*w) + 0.5625*exp(-1i*w*2));
% Normalizamos el filtro, buscando el valor m�ximo del m�dulo (importante)
% Obtenemos un valor real por el que dividimos todo el filtro
[H_max,p] = max(abs(H));
H_norm = H ./ H_max;
% El valor del filtro en la frecuencia 0 es infinito,
% pero deber�a tener ganancia 0 (al ser un filtro pasa-altos)
H_norm(1) = 0.0;
% Dibujamos magnitud sin normalizar y fase del filtro H
figure (1);
subplot(2,2,1); plot(w, abs(H));
title ('Filtro H (Magnitud)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
figure (1);
subplot(2,2,2); plot(w, unwrap(angle(H)));
title ('Filtro H (Fase)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Fase[rad]');
grid on;
% Dibujamos magnitud normalizada en escala lineal y en dB del filtro H
figure (1);
subplot(2,2,3); plot(w, abs(H_norm));
title ('Filtro H (Magnitud Normalizada)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;
figure (1);
subplot(2,2,4); plot(w, 20*log10(abs(H_norm)));
title ('Filtro H (Magnitud en dB)');
xlabel('Frecuencia [rad/muestra]');
ylabel('Magnitud');
grid on;

