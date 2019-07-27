%% setup
L = [0.18, 0.24]; % length of the 
rpt_cyl = [0.3, 0.8, 0.3]; % reach point in cylindrical coordinates
Q0 = [0, 0, 0]; %

%% solve
[Qr, SUCCESS] = ik_3dof_cylindrical(L, rpt_cyl, Q0);

%% visualize
%pose = 