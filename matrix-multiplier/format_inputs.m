function [ Aout, Bout ] = format_inputs( A, B, start_time, is_notvector )
    A_row1_val = A(1,:);
    A_row2_val = A(2,:);
    A_row3_val = A(3,:);
    A_row4_val = A(4,:);

    B_col1_val = [B(:,1)]';
    if is_notvector
        B_col2_val = [B(:,2)]';
        B_col3_val = [B(:,3)]';
        B_col4_val = [B(:,4)]';
    end

    time_base = 0:3;
    time1 = start_time + time_base;
    time2 = time1 + 1;
    time3 = time1 + 2;
    time4 = time1 + 3;

    A_row1 = timeseries(A_row1_val,time1);
    A_row2 = timeseries(A_row2_val,time2);
    A_row3 = timeseries(A_row3_val,time3);
    A_row4 = timeseries(A_row4_val,time4);
    Aout = [A_row1; A_row2; A_row3; A_row4];

    B_col1 = timeseries(B_col1_val,time1);
    if is_notvector
        B_col2 = timeseries(B_col2_val,time2);
        B_col3 = timeseries(B_col3_val,time3);
        B_col4 = timeseries(B_col4_val,time4);
        Bout = [B_col1; B_col2; B_col3; B_col4];
    else
        Bout = B_col1;
    end
end
