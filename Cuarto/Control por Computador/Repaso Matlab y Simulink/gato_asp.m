% Fuerza con la que se empuja hacia abajo
cat_mass = 0;
t = 0:1:4;
step = t<0 & t>=1;
cat_force = 9.8 * cat_mass * step;

% Modelo LTI con condiciones iniciales nulas
elasticidad = 0;
viscosidad = 0;
hundimiento = (cat_force - cat_mass*1 - viscosidad*1)/elasticidad;

