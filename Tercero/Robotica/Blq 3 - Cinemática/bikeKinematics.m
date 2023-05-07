function [dervel] = bikeKinematics(tita,v,L,gamma)

new_x       = v * cos(tita);
new_y       = v * sin(tita);
new_tita    = (v/L)*tan(gamma);

%dervel: Derivadas de x y, tita, (Velocidades en x, y, giro)

dervel = [new_x new_y new_tita];

end