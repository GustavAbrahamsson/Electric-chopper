%% Calculations Electric chopper
clc

u = 37; % V
kV = 120;
T_min = 2; % Nm
T_max = 4; % Nm
m_T = 12; % motor sprocket number of teeth
a_T_in = 27; % axle sprocket in
a_T_out = 14; % axle sprocket out
w_T = 92; % wheel sprocket
w_r = 0.254; % m, wheel radius

w_motor = u*kV*pi/30 % rad/s, motor rotation speed
w_axle = w_motor * m_T/a_T_in % rad/s, axle rotation speed
w_wheel = w_axle * a_T_out/w_T % rad/s, wheel rotation speed
k_total =  a_T_in/m_T * w_T/a_T_out % transmission ratio
v = w_wheel * w_r * 3.6 % km/h, speed
T_out_min = T_min * k_total % min torque
T_out_max = T_max * k_total % max torque
