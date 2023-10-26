syms Ra S La Kb J B Kc Kt Ka Vext

A = [1 0 0 0 0 0;
        1 -(Ra + S*La) -1 0 0 0;
        0 -Kt 0 1 0 0;
        0 0 1 0 -S*Kb 0;
        0 0 0 1 -(S^(2) * J + S*B) 0;
        0 0 0 0 -S*Kc 1
];

E = [Ka*Vext; 0; 0; 0; 0; 0];
I = A \ E;

Vo = I(1);
d_thita = I(6);
ia = I(3);

Ka = 1;
Kt = 1;
Kb = 0.5;
B = 0.1;
J = 5e-6;
Kc = 1/(2*pi);
Ra = 50;

out_ej2 = sim("motor_dc_sim_2022.slx", 10);
figure();
hold on;
plot(out_ej2.tout, out_ej2.Vin, 'g');
plot(out_ej2.tout, out_ej2.Vo);
plot(out_ej2.tout, out_ej2.Vo ./ out_ej2.Vin, 'b');
hold off;

figure();
hold on;
plot(out_ej2.tout, out_ej2.Vin, 'g');
plot(out_ej2.tout, out_ej2.thita);
hold off;

figure();
hold on;
plot(out_ej2.tout, out_ej2.Vin, 'g');
plot(out_ej2.tout, out_ej2.Ia);
hold off;