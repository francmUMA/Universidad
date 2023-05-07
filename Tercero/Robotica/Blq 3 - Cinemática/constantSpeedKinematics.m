function [newPose] = constantSpeedKinematics(xinit,v,deltat)

new_x = xinit(1) + v(1) * deltat * cos(xinit(3)) - v(2) * deltat * sin(xinit(3));
new_y = xinit(2) + v(1) * deltat * sin(xinit(3)) - v(2) * deltat * cos(xinit(3));
new_t = xinit(3) + v(3) * deltat;

newPose = [new_x new_y new_t];
end