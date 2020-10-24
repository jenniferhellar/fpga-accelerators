#include "matrixmul.h"

void matrixmul(
      short a[MAT_A_ROWS][MAT_A_COLS],
      short b[MAT_B_ROWS][MAT_B_COLS],
      short res[MAT_A_ROWS][MAT_B_COLS])
{
#pragma HLS INTERFACE ap_fifo port=res
#pragma HLS INTERFACE ap_fifo port=b
#pragma HLS ARRAY_RESHAPE variable=b complete dim=1
#pragma HLS ARRAY_RESHAPE variable=a complete dim=2
#pragma HLS INTERFACE ap_fifo port=a
	short a_row[MAT_A_ROWS];
	short b_copy[MAT_B_ROWS][MAT_B_COLS];
	short tmp = 0;

    // Iterate over the rows of the A matrix
    Row: for(int i = 0; i < MAT_A_ROWS; i++) {
      // Iterate over the columns of the B matrix
      Col: for(int j = 0; j < MAT_B_COLS; j++) {
#pragma HLS PIPELINE
        // Do the inner product of a row of A and col of B
        tmp = 0;
        if(j==0)
        	RD_ROW: for(int k = 0; k < MAT_A_ROWS; k++)
        		a_row[k] = a[i][k];
        if(i==0)
        	RD_COL: for(int k = 0; k < MAT_B_ROWS; k++)
        		b_copy[k][j] = b[k][j];
        Product: for(int k = 0; k < MAT_B_ROWS; k++) {
          tmp += a_row[k] * b_copy[k][j];
        }
        res[i][j] = tmp;
      }
    }
}


