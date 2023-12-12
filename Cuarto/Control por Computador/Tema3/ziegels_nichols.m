num_g = 1;
den_g = poly([-2;-3;-4]);
g = tf(num_g, den_g);
kcr = 210;
pcr = 10.6 - 9.37;
% ----------------------- P --------------------%
p_controller = kcr / 2;

% ----------------------- PI -------------------%
kp_pi = 0.45*kcr;
ki_pi = 1.2*(kcr/pcr);
cero_pos = ki_pi / kp_pi;

% ----------------------- PID ------------------%
kp_pid = 0.6*kcr;
ki_pid = 2* (kcr/pcr);
kd_pid = (1/8)*kcr*pcr;
poles_pos = roots([kd_pid kp_pid ki_pid]);