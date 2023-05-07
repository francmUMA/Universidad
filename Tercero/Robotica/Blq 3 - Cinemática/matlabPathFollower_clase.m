% ------------------------------------------------------------------------------------------------
% PATH FOLLOWER WITH KINEMATIC MODELS
%
% Based on: 
% https://es.mathworks.com/help/robotics/examples/path-following-for-differential-drive-robot.html
% https://es.mathworks.com/help/robotics/ug/mobile-robot-kinematics-equations.html
% 
% ANA CRUZ MARTÍN, 2022
% ------------------------------------------------------------------------------------------------

clear all;
clc;

% Path waypoints
%path = [2.00 1.00; 1.25 1.75; 5.25 8.25; 7.25 8.75; 11.75 10.75; 12.00 10.00]; % segments
%path = [4.00 1.00; 2.00 1.00; 1.25 1.75; 5.25 8.25; 7.25 8.75; 11.75 10.75; 12.00 10.00; 12.00 6.00; 8.00 6.00; 11.00 7.50]; % sharp segments
path = [2.00 6.00; 4.00 6.00; 6.00 6.00; 8.00 6.00; 10.00 6.00; 12.00 6.00]; % horizontal line
%path = [6.00 2.00; 6.00 4.00; 6.00 6.00; 6.00 8.00; 6.00 10.00; 6.00 12.00]; % vertical line
%path = [0.00 0.00; 2.00 2.00; 4.00 4.00; 6.00 6.00; 8.00 8.00; 10.00 10.00; 12.00 12.00]; % 45º line

% Initial and goal robot locations
robotInitialLocation = path(1,:);
robotGoal = path(end,:);

% Initial orientation
initialOrientation = 0; % orientation = angle between robot axe and positive X axe, counterclockwise

% Current robot pose
robotCurrentPose = [robotInitialLocation initialOrientation]';

% Robot description
L = 1;          % axe length (diff drive model)
I = 1;          % inter wheel distance (bicycle model)
r = 0.05;       % wheel radius (meters)

% Path tracker (Pure Pursuit)
controller = controllerPurePursuit;
controller.Waypoints = path;
controller.DesiredLinearVelocity = 0.6;
controller.MaxAngularVelocity = 2;
controller.LookaheadDistance = 0.3;

% Distance to goal
goalRadius = 0.1; 
distanceToGoal = norm(robotInitialLocation - robotGoal);

% Simulation and plot variables
sampleTime = 0.1; 
vizRate = rateControl(1/sampleTime);   
frameSize = L/0.8;  % vehicle frame size to most closely represent vehicle with plotTransforms
figure;

% Simulation loop
while (distanceToGoal > goalRadius)         
    % Compute the controller outputs, i.e., the inputs to the robot
    [v, w] = controller(robotCurrentPose); 
 
    % kinematic model: computes the new robotCurrentPose from the old robotCurrent Pose (and velocities)
    
    %robotCurrentPose = kinematicModel(robotCurrentPose,velocities)';
    %robotCurrentPose = constantSpeedKinematics(robotCurrentPose, [1,0,0], sampleTime)';
    robotCurrentPose = bikeKinematics(initialOrientation,2,L,pi/3)';

    % Re-compute the distance to the goal     
    distanceToGoal = norm(robotCurrentPose(1:2) - robotGoal(:));  

    % Update the plot
    hold off
    
    % Plot path each instance so that it stays persistent while robot mesh
    % moves
    plot(path(:,1), path(:,2),"k--d");
    title("Path Following with Pure Pursuit and Kinematics");
    xlabel("X (m.)");
    ylabel("Y (m.)");
    hold all
    
    % Plot the path of the robot as a set of transforms
    plotTrVec = [robotCurrentPose(1:2); 0];
    plotRot = axang2quat([0 0 1 robotCurrentPose(3)]);
    plotTransforms(plotTrVec', plotRot, "MeshFilePath", "groundvehicle.stl", "Parent", gca, "View","2D", "FrameSize", frameSize);
    light;
    xlim([0 13])
    ylim([0 13])
    
    waitfor(vizRate)
end