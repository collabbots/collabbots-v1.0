function [Qr, IK_FLAG] = ik_3dof_cylindrical(L, r_pt, Q0, Qmax, Qmin)
% Solves the following inverse kinematics problem:
% Qr = T{[r, theta, z], L}, given Q0 (initial joint angles), where:
%   1. Qr (1x3) is the result vector in joint space (equal to span{[q1, q2, q3]}, or Q)
%   conataining joint angles of the 3 DOF robot to reach a point in space.
%   2. T{} is the non-linear transform that maps 3D space onto joint space, Q.
%   3. [r, theta, z] are the cylindrical coordinates of the point where the
%   reach point.
%   4. L (1x2) is a vector containing arm link lengths between the 3 joints.
%   5. Take Qmax and Qmin for max and min angles. 
%   6. IK_FLAG tells if the solution has been successfully found. It is:
%       false (0), if no valid solution was found, and
%       true (1), if a valid solution has been found.
%   NOTE: This function only applies to arms with similar designs as the
%   CollabBots arm.    
    % TODO: Update the comments above. Have grammtical errors and unfinished
    % sentences.
    [Qr, EXIT_FLAG] = fsolve(@ik_3dof_cyl, Q0);
    
    % TODO: The function always enters this, even after solving successfully. 
    %       Look again into fsolve documentation!
    % check if solved and validate solution
    if (EXIT_FLAG ~= 1)
       IK_FLAG = false; 
    elseif (Qr <= Qmax) && (Qr >= Qmin)
       IK_FLAG = true;  
    else
        IK_FLAG = false;
    end
    
    % formulates the inverse kinematics problem
    function F = ik_3dof_cyl(Q)
        F(1) = Q(1) - r_pt(2); % theta
        F(2) = L(1)*cos(Q(2)) + L(2)*cos(Q(2)-Q(3)) - r_pt(1); %r
        F(3) = L(1)*sin(Q(2)) + L(2)*sin(Q(2)-Q(3)) - r_pt(3); %z
    end
end