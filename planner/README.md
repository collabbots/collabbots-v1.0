# planner
Plans and controls the tasks each robot has to perform to achieve its goal, based on inputs from the vision module.
1. The kinematics module solves the forward and inverse kinematics for the 3DOF Collabbots arm. It also handles visualization 
of the arm state.
2. The trajectory module solves/updates the trajectory for an arm  on the fly (real-time) based on inputs about obstacles in space from the vision module, with predictive planning of dynamic obstacles like another robotic arm. This module does not need or take information about the other arm(s) from the driver or kinematics module, and is just based on vision for that purpose.
3. The visualization module displays the current state of the system, the planned trajectories of the robotic arms, and status of the structure being built by the robots.

