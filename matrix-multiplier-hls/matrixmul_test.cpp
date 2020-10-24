#include <iostream>
#include "matrixmul.h"

using namespace std;

int main(int argc, char **argv)
{
   short in_mat_a[4][4] = {
      {1,20,3,40},
      {50,6,70,8},
      {9,100,11,120},
	  {130,14,15,160}
   };
   short in_mat_b[4][4] = {
      {10,1,5,1},
      {1,2,1,1},
      {23,1,7,1},
	  {1,12,1,1}
   };
   short hw_result[4][4], sw_result[4][4];
   int err_cnt = 0;

   // Generate the expected result
   // Iterate over the rows of the A matrix
   for(int i = 0; i < MAT_A_ROWS; i++) {
      for(int j = 0; j < MAT_B_COLS; j++) {
         // Iterate over the columns of the B matrix
         sw_result[i][j] = 0;
         // Do the inner product of a row of A and col of B
         for(int k = 0; k < MAT_B_ROWS; k++) {
            sw_result[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
         }
      }
   }

#ifdef HW_COSIM
   // Run the AutoESL matrix multiply block
   matrixmul(in_mat_a, in_mat_b, hw_result);
#endif

   // Print result matrix
   cout << "{" << endl;
   //cout << setw(6);
   for (int i = 0; i < MAT_A_ROWS; i++) {
      cout << "{";
      for (int j = 0; j < MAT_B_COLS; j++) {
#ifdef HW_COSIM
         cout << hw_result[i][j];
         // Check HW result against SW
         if (hw_result[i][j] != sw_result[i][j]) {
            err_cnt++;
            cout << "*";
         }
#else
         cout << sw_result[i][j];
#endif
         if (j == MAT_B_COLS - 1)
            cout << "}" << endl;
         else
            cout << ",";
      }
   }
   cout << "}" << endl;

#ifdef HW_COSIM
   if (err_cnt)
      cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
   else
      cout << "Test passed." << endl;
#endif
   return err_cnt;
}

