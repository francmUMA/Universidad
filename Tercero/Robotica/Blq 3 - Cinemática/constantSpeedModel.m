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

