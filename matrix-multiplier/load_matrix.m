%% Run three matrices back-to-back

% First set of matrices to multiply
matrix_A = ones(4,4);
matrix_B = ones(4,4);
[A,B] = format_inputs(matrix_A, matrix_B, 0, true);
A_row1 = A(1,:); A_row2 = A(2,:); A_row3 = A(3,:); A_row4 = A(4,:);
B_col1 = B(1,:); B_col2 = B(2,:); B_col3 = B(3,:); B_col4 = B(4,:);

% Second set of matrices to multiply
matrix_A1 = [1 2 3 4; 5 6 7 8; 4 3 2 1; 8 7 6 5];
matrix_B1 = ones(4,4);
[A1,B1] = format_inputs(matrix_A1, matrix_B1, 6, true); % Start at time 6
A_row1 = append(A_row1,A1(1,:));
A_row2 = append(A_row2,A1(2,:));
A_row3 = append(A_row3,A1(3,:));
A_row4 = append(A_row4,A1(4,:));
B_col1 = append(B_col1,B1(1,:));
B_col2 = append(B_col2,B1(2,:));
B_col3 = append(B_col3,B1(3,:));
B_col4 = append(B_col4,B1(4,:));

% Third set of matrices to multiply
matrix_A2 = 4*ones(4,4);
matrix_B2 = [1 0 0 0; 0 2 0 0; 0 0 4 0; 0 0 0 8];
[A2,B2] = format_inputs(matrix_A2, matrix_B2, 12, true); % Start at time 12
A_row1 = append(A_row1,A2(1,:));
A_row2 = append(A_row2,A2(2,:));
A_row3 = append(A_row3,A2(3,:));
A_row4 = append(A_row4,A2(4,:));
B_col1 = append(B_col1,B2(1,:));
B_col2 = append(B_col2,B2(2,:));
B_col3 = append(B_col3,B2(3,:));
B_col4 = append(B_col4,B2(4,:));

% None of the above are vectors
notvector = [true,true,true];
isnotvector = timeseries(notvector,[0,6,12]);

%% Run matrix-vector-matrix

% First set of matrices
matrix_A = ones(4,4);
matrix_B = ones(4,4);
[A,B] = format_inputs(matrix_A, matrix_B, 0, true);
A_row1 = A(1,:); A_row2 = A(2,:); A_row3 = A(3,:); A_row4 = A(4,:);
B_col1 = B(1,:); B_col2 = B(2,:); B_col3 = B(3,:); B_col4 = B(4,:);

% Matrix-vector multiply
matrix_A2 = 4*ones(4,4);
vector_B2 = ones(4,1);
[A2,B2] = format_inputs(matrix_A2, vector_B2, 6, false);
A_row1 = append(A_row1,A2(1,:));
A_row2 = append(A_row2,A2(2,:));
A_row3 = append(A_row3,A2(3,:));
A_row4 = append(A_row4,A2(4,:));
B_col1 = append(B_col1,B2(1,:));

% Matrix-matrix multiply
matrix_A1 = 2*ones(4,4);
matrix_B1 = ones(4,4);
[A1,B1] = format_inputs(matrix_A1, matrix_B1, 12, true);
A_row1 = append(A_row1,A1(1,:));
A_row2 = append(A_row2,A1(2,:));
A_row3 = append(A_row3,A1(3,:));
A_row4 = append(A_row4,A1(4,:));
B_col1 = append(B_col1,B1(1,:));
B_col2 = append(B_col2,B1(2,:));
B_col3 = append(B_col3,B1(3,:));
B_col4 = append(B_col4,B1(4,:));

% Second input is a vector
notvector = [true,false,true];
isnotvector = timeseries(notvector,[0,6,12]);

%% Extract and format outputs

raw = [C_row1'; C_row2'; C_row3'; C_row4'];
if notvector(1)
    output1 = [raw(1,10:13); raw(2,11:14); raw(3,12:15); raw(4,13:16)];
else
    output1 = [raw(1,10); raw(2,11); raw(3,12); raw(4,13)];
end
if notvector(2)
    output2 = [raw(1,16:19); raw(2,17:20); raw(3,18:21); raw(4,19:22)];
else
    output2 = [raw(1,16); raw(2,17); raw(3,18); raw(4,19)];
end
if notvector(3)
    output3 = [raw(1,22:25); raw(2,23:26); raw(3,24:27); raw(4,25:28)];
else
    output3 = [raw(1,22); raw(2,23); raw(3,24); raw(4,25)];
end
