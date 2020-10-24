#ifndef __MATRIXMUL_H__
#define __MATRIXMUL_H__

#include <cmath>
using namespace std;

// Uncomment this line to compare TB vs HW C-model and/or RTL
//#define HW_COSIM

#define MAT_A_ROWS 4
#define MAT_A_COLS 4
#define MAT_B_ROWS 4
#define MAT_B_COLS 4

// Prototype of top level function for C-synthesis
void matrixmul(
      short a[MAT_A_ROWS][MAT_A_COLS],
      short b[MAT_B_ROWS][MAT_B_COLS],
      short res[MAT_A_ROWS][MAT_B_COLS]);

#endif // __MATRIXMUL_H__ not defined

