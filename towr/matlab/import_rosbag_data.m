%% Plot towr rosbags in matlab
%
% The bags can be generated using
% towr_ros/src/exe/rosbag_geom_msg_extractor.cc.
%
% Author: Alexander Winkler

clc;
clear all;
close all;

%% Extract the desired 3D vectors from the bag
filePath = '~/Documents/thesis/extracted bags/matlab_universalPL_flat_walk_90_60.bag';
bag_all = rosbag(filePath);

t0 = 0.0; %bag_all.StartTime;
T  = bag_all.EndTime;

selectOptions = {'Time', [t0 T] };
bag = select(bag_all, selectOptions{:});

%% base motion
%Base position and orientation
bag_base_pose = select(bag, 'Topic', 'base_pose');
ts_base_pos = timeseries(bag_base_pose, 'Position.X', 'Position.Y', 'Position.Z', ... 
                                        'Orientation.X', 'Orientation.Y', 'Orientation.Z', 'Orientation.W');
%Base velocity                                    
bag_base_twist = select(bag, 'Topic', 'base_twist');
ts_base_vel = timeseries(bag_base_twist, 'Linear.X', 'Linear.Y', 'Linear.Z');

bag_base_acc  = select(bag, 'Topic', 'base_acc');
ts_base_acc = timeseries(bag_base_acc, 'Z');

%% endeffector motion
bag_foot_0 = select(bag, 'Topic', 'foot_pos_0');
ts_foot_LF = timeseries(bag_foot_0, 'X', 'Y', 'Z');

bag_foot_1 = select(bag, 'Topic', 'foot_pos_1');
ts_foot_RF = timeseries(bag_foot_1, 'X', 'Y', 'Z');

bag_foot_2 = select(bag, 'Topic', 'foot_pos_2');
ts_foot_LH = timeseries(bag_foot_2, 'X', 'Y','Z');

bag_foot_3 = select(bag, 'Topic', 'foot_pos_3');
ts_foot_RH = timeseries(bag_foot_3, 'X', 'Y','Z');

%% endeffector forces
bag_force_0 = select(bag, 'Topic', 'foot_force_0');
ts_force_LF = timeseries(bag_force_0, 'X', 'Y','Z');

bag_force_1 = select(bag, 'Topic', 'foot_force_1');
ts_force_RF  = timeseries(bag_force_1, 'X', 'Y','Z');

bag_force_2 = select(bag, 'Topic', 'foot_force_2');
ts_force_LH  = timeseries(bag_force_2, 'X', 'Y','Z');

bag_force_3 = select(bag, 'Topic', 'foot_force_3');
ts_force_RH  = timeseries(bag_force_3, 'X', 'Y','Z');


%% 
t = ts_base_pos.Time; 
dt = t(2)-t(1);

% base acceleration
base_zdd = ts_base_acc.Data(:,1);

% foot position world frame
foot_LF.position = [ts_foot_LF.Data(:,1) ts_foot_LF.Data(:,2) ts_foot_LF.Data(:,3)];
foot_RF.position = [ts_foot_RF.Data(:,1) ts_foot_RF.Data(:,2) ts_foot_RF.Data(:,3)];
foot_LH.position = [ts_foot_LH.Data(:,1) ts_foot_LH.Data(:,2) ts_foot_LH.Data(:,3)];
foot_RH.position = [ts_foot_RH.Data(:,1) ts_foot_RH.Data(:,2) ts_foot_RH.Data(:,3)];

%foot velocity world frame
for i=1:length(ts_foot_LF.Data(:,1))-1
    foot_LF.velocity(i+1,:) = (foot_LF.position(i+1,:)-foot_LF.position(i,:))/dt;
    foot_RF.velocity(i+1,:) = (foot_RF.position(i+1,:)-foot_LF.position(i,:))/dt;
    foot_LH.velocity(i+1,:) = (foot_LH.position(i+1,:)-foot_LF.position(i,:))/dt;
    foot_RH.velocity(i+1,:) = (foot_RH.position(i+1,:)-foot_LF.position(i,:))/dt;
end

% foot force
foot_LF.force = [ts_force_LF.Data(:,1) ts_force_LF.Data(:,2) ts_force_LF.Data(:,3)];
foot_RF.force = [ts_force_RF.Data(:,1) ts_force_RF.Data(:,2) ts_force_RF.Data(:,3)];
foot_LH.force = [ts_force_LH.Data(:,1) ts_force_LH.Data(:,2) ts_force_LH.Data(:,3)];
foot_RH.force = [ts_force_RH.Data(:,1) ts_force_RH.Data(:,2) ts_force_RH.Data(:,3)];


%% error

m = 20.52;   % weight of the robot
g = 9.81; % gravity acceleration
F_ext = foot_LF.force(:,3) + foot_RF.force(:,3) + foot_LH.force(:,3) + foot_RH.force(:,3);
base_zdd_dynamics = 1/m*F_ext - g;
% calculate Root mean square error
base_zdd_error = base_zdd_dynamics - base_zdd;
norm_sqare = norm(base_zdd_error)^2;
n = size(t,1); % number of sampled points
RMSE = sqrt(norm_sqare/n) 
