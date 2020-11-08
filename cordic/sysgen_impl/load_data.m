%% 1. Rotation mode: load test data

z_array = (-pi+pi/180):1*pi/180:pi;  % Angles to rotate through
x_val = 1;                   % Initial vector
y_val = 0;

last_sample = (41*(length(z_array)+1));

% Upsample all inputs by latency of block
z_in = upsample(z_array,41);    
x_in = upsample(x_val*ones(1,length(z_array)),41);
y_in = upsample(y_val*ones(1,length(z_array)),41);

% Convert to timeseries 
mode = timeseries(ones(1,last_sample-1));
z = timeseries(z_in);
x = timeseries(x_in);
y = timeseries(y_in);

%% 2. Rotation mode: plot data and calculate error

% Calculate true rotation for each angle
a_sw = cos(z_array)*x_val - sin(z_array)*y_val;
b_sw = sin(z_array)*x_val + cos(z_array)*y_val;

% Extract the results
a_vals = downsample(a_out,41)';
b_vals = downsample(b_out,41)';

% Plot results with expected values
time = 42:41:last_sample;
plot(time,a_sw,'*',time,a_vals(2:(length(z_array)+1)),'+')
legend('x expected','x calculated')
title('X-coordinate Output (Rotation Mode)')
xlabel('Clock cycle')
grid on
figure()
plot(time,b_sw,'*',time,b_vals(2:(length(z_array)+1)),'+');
legend('y expected','y calculated')
title('Y-coordinate Output (Rotation Mode)')
xlabel('Clock cycle')
grid on

% Average errors: a: 0.0015, b: 0.0012
avg_error_a = sum(abs(a_sw-a_vals(2:(length(z_array)+1))))/length(z_array);
avg_error_b = sum(abs(b_sw-b_vals(2:(length(z_array)+1))))/length(z_array);

%% 3. Arctan mode: load test data

z_array = (-pi+pi/180):1*pi/180:pi;
x_val = 1;       
y_val = 0;

last_sample = (41*(length(z_array)+1));

% Generate vectors by rotating original vector
x_vectors = (cos(z_array)*x_val - sin(z_array)*y_val);
y_vectors = (sin(z_array)*x_val + cos(z_array)*y_val);

z_in = zeros(1,last_sample-41);
x_in = upsample(x_vectors,41);
y_in = upsample(y_vectors,41);

mode = timeseries(zeros(1,last_sample-1));
z = timeseries(z_in);
x = timeseries(x_in);
y = timeseries(y_in);

%% 4. Arctan mode: plot data and calculate error

mag_vals = downsample(a_out,41)';
angle_vals = downsample(c_out,41)';

mag_sw = sqrt(x_vectors.^2+y_vectors.^2);
angle_sw = atan2(y_vectors,x_vectors);

time = 42:41:last_sample;
plot(time,mag_sw,'*',time,mag_vals(2:(length(z_array)+1)),'+')
legend('Magnitude expected','Magnitude calculated')
title('Magnitude Output (Arctan Mode)')
xlabel('Clock cycle')
grid on
figure()
plot(time,angle_sw,'*',time,angle_vals(2:(length(z_array)+1)),'+');
legend('Angle expected','Angle calculated')
title('Angle Output (Arctan Mode)')
xlabel('Clock cycle')
grid on

% mag: 0.0012, angle: 0.000319
avg_error_mag = sum(abs(mag_sw-mag_vals(2:(length(z_array)+1))))/length(z_array);
avg_error_angle = sum(abs(angle_sw-angle_vals(2:(length(z_array)+1))))/length(z_array);

%% 5. Rotation mode: Load data for SINCOS cordic block 

z_array = (-pi+pi/180):1*pi/180:pi;  % Angles to rotate through
x_val = 1;                   % Initial vector
y_val = 0;

z_in = z_array;
x_in = x_val*ones(1,length(z_array));
y_in = y_val*ones(1,length(z_array));

% Convert to timeseries 
z = timeseries(z_in);
x = timeseries(x_in);
y = timeseries(y_in);

%% 6. Rotation mode: Calculate SINCOS error
% Calculate true rotation for each angle
a_sw = cos(z_array)*x_val - sin(z_array)*y_val;
b_sw = sin(z_array)*x_val + cos(z_array)*y_val;

% Extract the results
a_vals = a_out(16:end)';
b_vals = b_out(16:end)';

% Average errors: a: 0.0311, b: 0.0033
avg_error_a = sum(abs(a_sw-a_vals))/length(z_array);
avg_error_b = sum(abs(b_sw-b_vals))/length(z_array);

%% 7. Arctan mode: Load data for SINCOS/Arctan cordic block 

z_array = (-pi+pi/180):1*pi/180:pi;
x_val = 1;       
y_val = 0;

% Generate vectors by rotating original vector
x_vectors = (cos(z_array)*x_val - sin(z_array)*y_val);
y_vectors = (sin(z_array)*x_val + cos(z_array)*y_val);

z_in = zeros(1,length(z_array));
x_in = x_vectors;
y_in = y_vectors;

z = timeseries(z_in);
x = timeseries(x_in);
y = timeseries(y_in);

%% Arctan mode: Calculate SINCOS Arctan error 

mag_sw = sqrt(x_vectors.^2+y_vectors.^2);
angle_sw = atan2(y_vectors,x_vectors);

mag_vals = a_out(15:end-1)';
angle_vals = c_out(15:end-1)';

% mag: 0.000888, angle: 0.000125
avg_error_mag = sum(abs(mag_sw-mag_vals))/length(z_array);
avg_error_angle = sum(abs(angle_sw-angle_vals))/length(z_array);

