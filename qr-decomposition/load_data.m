%% Load data into workspace - one matrix

is_two = 0;

start_array = [1, zeros(1,599)];    % New matrix pulse
start = timeseries(start_array);

A = [0.69 0.5054 0.5914 0.5547;     % Matrix
    0.3784 0.2577 0.2073 0.6262; 
    0.3401 0.8438 0.0687 0.4099; 
    0.8799 0.3194 0.9805 0.0850];

col1 = kron(fliplr(A(:,1)'),ones(1,43));    % Reverse column, upsample & hold vals
col2 = [zeros(1,44),kron(fliplr(A(:,2)'),ones(1,43))]; 
col3 = [zeros(1,88),kron(fliplr(A(:,3)'),ones(1,43))]; 
col4 = [zeros(1,132),kron(fliplr(A(:,4)'),ones(1,43))];
Acol1 = timeseries(col1); Acol2 = timeseries(col2);     % Convert to timeseries
Acol3 = timeseries(col3); Acol4 = timeseries(col4);

I = [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1];   % Identity matrix
Icol1 = timeseries([zeros(1,176),kron(fliplr(I(:,1)'),ones(1,43))]);
Icol2 = timeseries([zeros(1,220),kron(fliplr(I(:,2)'),ones(1,43))]);
Icol3 = timeseries([zeros(1,264),kron(fliplr(I(:,3)'),ones(1,43))]);
Icol4 = timeseries([zeros(1,308),kron(fliplr(I(:,4)'),ones(1,43))]);

%% Load data into workspace - two matrices

is_two = 1;

start_array = [1, zeros(1,176), 1, zeros(1,599)];    % New matrix pulse
start = timeseries(start_array);

A1 = [0.69 0.5054 0.5914 0.5547;     % Matrix
    0.3784 0.2577 0.2073 0.6262; 
    0.3401 0.8438 0.0687 0.4099; 
    0.8799 0.3194 0.9805 0.0850];
A2 = [0.69 0.5054 0.5914 0.5547;     % Matrix
    0.3784 0.2577 0.2073 0.6262; 
    0.3401 0.8438 0.0687 0.4099; 
    0.8799 0.3194 0.9805 0.0850];

A1col1 = [kron(fliplr(A1(:,1)'),ones(1,43)),zeros(1,5)];    % Reverse column, upsample & hold vals
A1col2 = [zeros(1,44),kron(fliplr(A1(:,2)'),ones(1,43)),zeros(1,5)]; 
A1col3 = [zeros(1,88),kron(fliplr(A1(:,3)'),ones(1,43)),zeros(1,5)]; 
A1col4 = [zeros(1,132),kron(fliplr(A1(:,4)'),ones(1,43)),zeros(1,5)];

A2col1 = [kron(fliplr(A2(:,1)'),ones(1,43)),zeros(1,5)];    % Reverse column, upsample & hold vals
A2col2 = [kron(fliplr(A2(:,2)'),ones(1,43)),zeros(1,5)]; 
A2col3 = [kron(fliplr(A2(:,3)'),ones(1,43)),zeros(1,5)]; 
A2col4 = [kron(fliplr(A2(:,4)'),ones(1,43)),zeros(1,5)];

Acol1 = timeseries([A1col1,A2col1]); 
Acol2 = timeseries([A1col2,A2col2]);     % Convert to timeseries
Acol3 = timeseries([A1col3,A2col3]); 
Acol4 = timeseries([A1col4,A2col4]);

I = [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1];   % Identity matrix
I1 = [kron(fliplr(I(:,1)'),ones(1,43)),zeros(1,5)];
I2 = [kron(fliplr(I(:,2)'),ones(1,43)),zeros(1,5)];
I3 = [kron(fliplr(I(:,3)'),ones(1,43)),zeros(1,5)];
I4 = [kron(fliplr(I(:,4)'),ones(1,43)),zeros(1,5)];
Icol1 = timeseries([zeros(1,176),I1,I1]);
Icol2 = timeseries([zeros(1,220),I2,I2]);
Icol3 = timeseries([zeros(1,264),I3,I3]);
Icol4 = timeseries([zeros(1,308),I4,I4]);%% Load data into workspace - one matrix

%% Extract and reconstruct the results

out1 = downsample(out_row1(177:end),45);
out2 = downsample(out_row2(265:end),45);
out3 = downsample(out_row3(353:end),45);
out4 = [out_row4(393), out_row4(438), out_row4(483), out_row4(528), out_row4(576)]';

R = [out1(1:4)'; [0 out2(1:3)']; [0 0 out3(1:2)']; [0 0 0 out4(1)']];
Q = [out1(5:8)'; out2(4:7)'; out3(3:6)'; out4(2:5)']';

A_new = Q*R;
error = sum(sum(abs(A-A_new)));

if(is_two)
    out1_2 = downsample(out_row1(354:end),45);
    out2_2 = downsample(out_row2(442:end),45);
    out3_2 = downsample(out_row3(530:end),45);
    out4_2 = [out_row4(570), out_row4(615), out_row4(660), out_row4(705), out_row4(750)]';
    
    R2 = [out1_2(1:4)'; [0 out2_2(1:3)']; [0 0 out3_2(1:2)']; [0 0 0 out4_2(1)']];
    Q2 = [out1_2(5:8)'; out2_2(4:7)'; out3_2(3:6)'; out4_2(2:5)']';
    
    A_new2 = Q2*R2;
    error_2 = sum(sum(abs(A-A_new2)));
end

