function Pf = fk_3dof_cylindrical(L, Qf)
% Resolves position of joints in space, given the solution from ik module.
%   Pr is the final pose of the robot, given Qf. Pr is 2x3 a matrix, 
%   consisting of the cylindrical coordinates of the elbow and wrist (fingers)
%   of the collabbots arm.
    Pf = zeros(2, 3);
    Pf(1) = [L(1)*cos(Qf(2)) Qf(1) L(1)*sin(Qf(2))];
    Pf(2) = [L(1)*cos(Qf(2)) + L(2)*cos(Qf(2) - Qf(3)) Qf(1) L(1)*sin(Qf(2))
        + L(2)*sin(Qf(2) - Qf(3))];
end