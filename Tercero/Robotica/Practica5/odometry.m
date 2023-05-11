function [x1,y1,theta1]=odometry(x0,y0,theta0,t0,rotl0,rotr0,t1,rotl1,rotr1)
    D = 11.7;
    R = 2.7;
    deltaThetaL = rotl1 - rotl0;
    deltaThetaR = rotr1 - rotr0;
    deltaTiempo = t1 - t0;
    
    if (deltaTiempo = 0)
        x1 = x0;
        y1 = y0;
        theta1 = theta0;
    else
    	x1 = (deltaThetaL * R) + (deltaThetaR * R) / 2 * cos(theta0);
    	y1 = (deltaThetaL * R) + (deltaThetaR * R) / 2 * sin(theta0);
    	theta1 = (deltaThetaR * R) - (deltaThetaL * R) / D;
    end
       
end
