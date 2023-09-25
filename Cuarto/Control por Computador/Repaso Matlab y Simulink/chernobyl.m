segundosporanyo = 365 * 24 * 60 * 60;
segundospordia = 24 * 60 * 60;
toneladaKg = 1000;

k_c137 = log(2)/30*segundosporanyo;
k_y131 = log(2)/8*segundospordia;

figure(1);
hold on;
subplot(2,1,1);
plot(out.tout, out.media_c137, 'g');
plot(out.tout, out.media_y131);
title("Evolución de la cantidad por año");
xlabel("Años"), ylabel("Cantidad (Kg)");
hold off;
