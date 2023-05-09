% Funcion que calcula implanta el modelo de la bicicleta en el robot.
function[newPose] = bikeKinematics(tita, v, L, gamma)
    % tita: Orientación del robot
    % v: Velocidad lineal del robot
    % L: Distancia entre ruedas
    % gamma: Ángulo de giro de la rueda delantera
    % newPose: Pose del robot en el instante t+dt

    % Implementación del modelo cinemático
    newPose(1) = v*cos(tita);
    newPose(2) = v*sin(tita);
    newPose(3) = v*tan(gamma)/L;
end
