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

% Función que implanta el modelo de velocidad constante en el robot.
function[newPose] = constantSpeedModel(pose, v, dt)
    % Pose: Pose actual del robot
    % v: Velocidad lineal del robot
    % w: Velocidad angular del robot
    % dt: Tiempo de muestreo
    % newPose: Pose del robot en el instante t+dt

    % Implementación del modelo cinemático
    newPose(1) = pose(1) + v(1)*dt*cos(pose(3)) - v(2)*dt*sin(pose(3));
    newPose(2) = pose(2) + v(1)*dt*sin(pose(3)) + v(2)*dt*cos(pose(3));
    newPose(3) = pose(3) + v(3)*dt;
end

% Funcion que implanta el modelo diferencial en el robot.
function[newPose] = diffDriveKinematics(tita, ur, ul, L, r)
    % tita: Orientación del robot
    % ur: Velocidad angular de la rueda derecha
    % ul: Velocidad angular de la rueda izquierda
    % L: Distancia entre ruedas
    % r: Radio de las ruedas
    % newPose: Pose del robot en el instante t+dt

    % Implementación del modelo cinemático
    newPose(1) = (r/2)*(ur+ul)*cos(tita);
    newPose(2) = (r/2)*(ur+ul)*sin(tita);
    newPose(3) = (r/L)*(ur-ul);
end

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
