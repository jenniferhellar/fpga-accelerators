%% Load matrices
A = [1 2 8 4; 5 2 7 0; 9 10 4 2; 7 0 3 1];    % First set of matrices
B = [5 1 6 2; 0 1 2 8; 5 9 2 7; 0 5 6 3];
A1 = 4*ones(4,4);                                     % Second set of matrices
B1 = [1 0 0 0; 0 2 0 4; 8 2 5 0; 3 4 6 2];

A_col1_val = [zeros(2,1); upsample(A(:,1),4); zeros(6,1); upsample(A1(:,1),4); zeros(6,1)];
A_col2_val = [zeros(2,1); upsample(A(:,2),4); zeros(6,1); upsample(A1(:,2),4); zeros(6,1)];
A_col3_val = [zeros(2,1); upsample(A(:,3),4); zeros(6,1); upsample(A1(:,3),4); zeros(6,1)];
A_col4_val = [zeros(2,1); upsample(A(:,4),4); zeros(6,1); upsample(A1(:,4),4); zeros(6,1)];
    
B_row1_val = [zeros(2,1); B(1,1:4)'; zeros(18,1); B1(1,1:4)'; zeros(18,1)];
B_row2_val = [zeros(2,1); B(2,1:4)'; zeros(18,1); B1(2,1:4)'; zeros(18,1)];
B_row3_val = [zeros(2,1); B(3,1:4)'; zeros(18,1); B1(3,1:4)'; zeros(18,1)];
B_row4_val = [zeros(2,1); B(4,1:4)'; zeros(18,1); B1(4,1:4)'; zeros(18,1)];
    
A_col1 = timeseries(A_col1_val);
A_col2 = timeseries(A_col2_val);
A_col3 = timeseries(A_col3_val);
A_col4 = timeseries(A_col4_val);
    
B_row1 = timeseries(B_row1_val);
B_row2 = timeseries(B_row2_val);
B_row3 = timeseries(B_row3_val);
B_row4 = timeseries(B_row4_val);

%% Extract and format outputs

C1 = A*B;
C1_out = [C(6:9)';C(10:13)';C(14:17)';C(18:21)'];
C2 = A1*B1;
C2_out = [C(28:31)'; C(32:35)'; C(36:39)'; C(40:43)'];
test_passed = (sum(sum(C1 == C1_out))+sum(sum(C2 == C2_out))) == 32

