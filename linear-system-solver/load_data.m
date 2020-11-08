% A = [0.69 0.5054 0.5914 0.5547;     % Matrix
%     0.3784 0.2577 0.2073 0.6262; 
%     0.3401 0.8438 0.0687 0.4099; 
%     0.8799 0.3194 0.9805 0.0850];

A1 = [0.1, 0.1, 0.4, 0.3;
    0.2, 0.8, 0.6, 0.5;
    0.9, 0.1, 0.3, 0.2;
    0.3, 0.1, 0.4, 0.6];

% Input data at various times, for various lengths of time
A1col1 = [kron(fliplr(A1(:,1)'),ones(1,3)),zeros(1,617)];   
A1col2 = [kron(fliplr(A1(:,2)'),ones(1,4)),zeros(1,617)]; 
A1col3 = [kron(fliplr(A1(:,3)'),ones(1,2)),zeros(1,617)]; 
A1col4 = [kron(fliplr(A1(:,4)'),ones(1,3)),zeros(1,617)];

Acol1 = timeseries([zeros(1,4),A1col1]);
Acol2 = timeseries([zeros(1,4),A1col2]);
Acol3 = timeseries([zeros(1,4),A1col3]);
Acol4 = timeseries([zeros(1,4),A1col4]);

% Write after data is available
row1_write = timeseries([zeros(1,4),ones(1,2),zeros(1,1),ones(1,2),zeros(1,1),ones(1,2),zeros(1,1),ones(1,2),zeros(1,750)]);
row2_write = timeseries([zeros(1,4),ones(1,3),zeros(1,1),ones(1,3),zeros(1,1),ones(1,3),zeros(1,1),ones(1,3),zeros(1,750)]);
row3_write = timeseries([zeros(1,4),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,750)]);
row4_write = timeseries([zeros(1,4),ones(1,2),zeros(1,1),ones(1,2),zeros(1,1),ones(1,2),zeros(1,1),ones(1,2),zeros(1,750)]);

% Enable and start
enable = timeseries([zeros(1,3),ones(1,3),zeros(1,750)]);
start_array = [zeros(1,30),ones(1,10),zeros(1,800)];
start = timeseries(start_array);

% Read results out
row1_read = timeseries([zeros(1,700),ones(1,2),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,750)]);
row2_read = timeseries([zeros(1,700),ones(1,3),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),zeros(1,14),zeros(1,600),ones(1,7),zeros(1,750)]);
row3_read = timeseries([zeros(1,700),ones(1,4),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),zeros(1,15),zeros(1,600),ones(1,6),zeros(1,750)]);
row4_read = timeseries([zeros(1,700),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),ones(1,1),zeros(1,1),zeros(1,16),zeros(1,600),ones(1,5),zeros(1,750)]);

% Reset the system
rst = timeseries([zeros(1,614),ones(1,7),zeros(1,750)]);

%% Check result

R = [out_row1(705),out_row1(708),out_row1(710),out_row1(712); 
    0, out_row2(705), out_row2(709), out_row2(711); 
    0, 0, out_row3(705),out_row3(710); 
    0, 0, 0, out_row4(705)];
Qt = [out_row1(714), out_row1(716), out_row1(718), out_row1(720); 
    out_row2(713), out_row2(715), out_row2(717), out_row2(719); 
    out_row3(712), out_row3(714), out_row3(716), out_row3(718); 
    out_row4(707), out_row4(709), out_row4(711), out_row4(713)];
Anew = Qt'*R

