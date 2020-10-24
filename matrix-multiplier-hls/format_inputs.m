function [ Aout, Bout ] = format_inputs( A, B)
    A_col1_val = [zeros(2,1); A(1,1); zeros(3,1); A(2,1); zeros(3,1); A(3,1); zeros(3,1);
        A(4,1); zeros(9,1)];
    A_col2_val = [zeros(2,1); A(1,2); zeros(3,1); A(2,2); zeros(3,1); A(3,2); zeros(3,1);
        A(4,2); zeros(9,1)];
    A_col3_val = [zeros(2,1); A(1,3); zeros(3,1); A(2,3); zeros(3,1); A(3,3); zeros(3,1);
        A(4,3); zeros(9,1)];
    A_col4_val = [zeros(2,1); A(1,4); zeros(3,1); A(2,4); zeros(3,1); A(3,4); zeros(3,1);
        A(4,4); zeros(9,1)];

    B_row1_val = [zeros(2,1); B(1,1:4); zeros(18,1)];
    B_row2_val = [zeros(2,1); B(2,1:4); zeros(18,1)];
    B_row3_val = [zeros(2,1); B(3,1:4); zeros(18,1)];
    B_row4_val = [zeros(2,1); B(4,1:4); zeros(18,1)];
    
    A_col1 = timeseries(A_col1_val);
    A_col2 = timeseries(A_col2_val);
    A_col3 = timeseries(A_col3_val);
    A_col4 = timeseries(A_col4_val);
    Aout = [A_col1; A_col2; A_col3; A_col4];
    
    B_row1 = timeseries(B_row1_val);
    B_row2 = timeseries(B_row2_val);
    B_row3 = timeseries(B_row3_val);
    B_row4 = timeseries(B_row4_val);
    Bout = [B_row1; B_row2; B_row3; B_row4];
end

