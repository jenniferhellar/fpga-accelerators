#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// .h file for software solver
#include "solver.h"
// .h file based on your .hls design
//#include "t_fixed.h"
// The c++ file for the fixed point data type
#include "ap_fixed.h"
// The .h files from C:\ELEC522\cavallar\fixed_SDK\SG\netlist_IP\ip\drivers\gen_sdk_v1_0\src
#include "qr.h"
#include "qr_hw.h"
// Memory map file from C:\ELEC522\cavallar\fixed_SDK\SG\netlist_IP\ip_catalog\gen_sdk.sdk\add_bsp\ps7_cortexa9_0\include
#include "xparameters.h"
// The Xilinx time function file for measuring ARM core cycles
#include "xtime_l.h"

using namespace std;

void print_m(double m[4][4]){
    //prints a matrix in a matlab friendly format
    float val;
    printf("[");
    for (int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            val = (float)m[i][j];
            printf("%f ", val);
        }
        if (i != 3){
            printf(";\n");
        }
    }
    printf("];\n\n");
}
// Convert from a floating point number to an integer for AXI interface
// Algorithm modified from notes from Pengfei Xu - Rice, to be more general
//from signed fixed 16,13 (input is double) to int, Sysgen calls it 16,3
int get_int (double fixed_input){
	// printf ("fixed output from double input is %f\n",fixed_input);
	int get_int = 0;
	int i;
	double fixed_left = fixed_input;
	// check if negative based on MSB
	if (fixed_input<0) {
		get_int +=pow(2,15);
		fixed_left = -fixed_left;
	}
	// for 16,13, then start with 2.0; for 16,14 then start with 1.0 sets the largest integer
	double div =2.0;
	// use pow(2,13) for 16,13l use pow(2,14) for 16,14
	int inc = pow(2,13);
	// max iterations
	for (i=0;i<15;i++){
		if (fixed_left > div){
			get_int += inc;
			// printf ("get_int is %d, inc is %d, fixed_left is %f, div is %f\n",get_int, inc, fixed_left, div);
			fixed_left-=div;
		}
		div=0.5*div;
		inc/=2;
	}
	return get_int;
}
// Convert from an integer number from AXI interface to fixed point (floating point type)
// Algorithm modified from notes from Pengfei Xu - Rice, to be more general
//from signed integer fixed 16,13 Sysgen calls it 16,3 to integer and fraction
double get_double (int hex_input){
	// printf ("double output fixed_input is %d\n", hex_input);
	double get_double = 0;
	int left = hex_input;
	// use pow(2,13) for 16,13l use pow(2,14) for 16,14
	int div = pow(2,13);
	// for 16,13, then start with 2.0; for 16,14 then start with 1.0 sets the largest integer
	double inc = 2.0;
	int sign_bit =1;
	int i;
	// check if negative based on MSB
	if (left>pow(2,15)) {
		sign_bit =-1;
		left-=pow(2,15);
	}
	// max iterations
	for (i=0;i<15;i++){
		if (left>div){
			get_double+=inc;
			// printf ("get_double is %f, inc is %f, left is %d, div is %d\n",get_double, inc, left, div);
			left-=div;
		}
		inc*=0.5;
		div/=2;
	}
	get_double *= sign_bit;
	//printf ("get_double is %f\n",get_double);
	return get_double;
}

double abs_double(double var){
	if ( var < 0)
	var = -var;
	return var;
}

// Needed to copy and paste definitions for I/O functions from the .h files in
// C:\ELEC522\cavallar\fixed_SDK\SG\netlist_IP\ip\drivers\gen_sdk_v1_0\src
// Define the "gen_sdk_WriteReg" function based on your project name in gen_sdk.h
// Your .h files will be based on your project name
#define qr_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define qr_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

int main(int argc, char **argv)
{
	// Variables for timing and counts
    unsigned long long tt;
	int tt_print;
	double tt_seconds;
	XTime start_time_co;
	XTime stop_time_co;

    // Ax = b
    double a[4][4] = {{0.1, 0.1, 0.4, 0.3},
    		{0.2, 0.8, 0.6, 0.5},
    		{0.9, 0.1, 0.3, 0.2},
    		{0.3, 0.1, 0.4, 0.6}};

//    double a[4][4] = {{0.4218,    0.6557,    0.6787,    0.6555},
//    	      {0.9157,    0.0357,    0.7577,    0.1712},
//    	      {0.7922,    0.8491,    0.7431,    0.7060},
//    	      {0.9595,    0.9340,    0.3922,    0.0318}};

//    double a[4][4] = {{0.3517,    0.9172,    0.3804,    0.5308},
//    	      {0.8308,    0.2858,    0.5678,    0.7792},
//    	      {0.5853,    0.7572,    0.0759,    0.9340},
//    	      {0.5497,    0.7537,    0.0540,    0.1299}};

    double b[4] = {0.2, 0.1, 0.8, 0.4};
    double x[4];

    printf("-- Start of the Program --\n");

	// Get the starting time in cycle counts
	XTime_GetTime(&start_time_co);

    // Input to linear system solver
    solver(a, b, x);

	// Capture the stop time
	XTime_GetTime(&stop_time_co);

	printf("x = [%f; %f; %f; %f]\n", x[0], x[1], x[2], x[3]);	// Should be [0.8034, -0.3796, 0.2957, 0.1311]

	// Error calculation by recalculating b = A*x
	double error = 0.0;
	double b_new[4];
	double sum;
	for(int i = 0; i < 4; i++){		// Matrix-vector multiplication
		sum = 0;
		for(int j = 0; j < 4; j++){
			sum = sum + a[i][j]*x[j];
		}
		b_new[i] = sum;
		error = error + abs_double(b[i] - (double)b_new[i]);
	}
	printf("b_new = [%f; %f; %f; %f]\n", b_new[0], b_new[1], b_new[2], b_new[3]);

	printf("error in reconstructed b = %f\n", error);		// gives 0.006641

    // Compute timing on ARM PS hardware
    tt = stop_time_co - start_time_co;
    tt_print = (unsigned) tt;
    printf("Done, Total time steps for PS internal (including ap_fixed emulation) = %d \n", tt_print);
    tt_seconds = COUNTS_PER_SECOND;
    printf("Cycle counts per second for ARM A9 core for PS internal add = %le \n", tt_seconds);
    tt_seconds = (float) tt_print / tt_seconds;
    printf("Time in seconds for PS ARM software internal add = times steps / COUNTS_PER_SECOND = %le \n", tt_seconds);

    // Get the starting time in cycle counts
    XTime_GetTime(&start_time_co);

    // Convert A to int for transmitting to PL
    int a_int[4][4];
    for(int i = 0; i < 4; i++){
    	for(int j = 0; j < 4; j++){
    		a_int[i][j] = get_int(a[i][j]);
    	}
    }

	// Generate the result on hardware using the integer converted values
	// Send data over AXI - find these parameters from the ip folder from Sysgen
	// The base address is in the xparameters.h file which should be located in the board support bss folder

	// Enable QR module
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ENABLE, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ENABLE, 0);

	// Transmit 1st row
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL1, a_int[3][0]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL2, a_int[3][1]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL3, a_int[3][2]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL4, a_int[3][3]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 1);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 0);

	// 2nd row
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL1, a_int[2][0]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL2, a_int[2][1]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL3, a_int[2][2]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL4, a_int[2][3]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 1);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 0);

	// 3rd row
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL1, a_int[1][0]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL2, a_int[1][1]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL3, a_int[1][2]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL4, a_int[1][3]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 1);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 0);

	// 4th row
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL1, a_int[0][0]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL2, a_int[0][1]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL3, a_int[0][2]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ACOL4, a_int[0][3]);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 1);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE1, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE2, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE3, 0);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_WRITE4, 0);

	// Start computation
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_START, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_START, 0);

	int done_out;
	do
		done_out = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_DONE);
	while(done_out == 0);

	int r_int[4][4];
	int qt_int[4][4];

	// Read first row of R
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	r_int[0][0] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	r_int[0][1] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	r_int[0][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	r_int[0][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	// Read first row of Qt
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	qt_int[0][0] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	qt_int[0][1] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	qt_int[0][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 1);
	qt_int[0][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ1, 0);

	// Read second row of R
	r_int[1][0] = 0;

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	r_int[1][1] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	r_int[1][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	r_int[1][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	// Read second row of Qt
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	qt_int[1][0] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	qt_int[1][1] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	qt_int[1][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 1);
	qt_int[1][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW2);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ2, 0);

	// Read third row of R
	r_int[2][0] = 0;
	r_int[2][1] = 0;

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 1);
	r_int[2][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW3);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 1);
	r_int[2][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW3);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 0);

	// Read third row of Qt
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 1);
	qt_int[2][0] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW3);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 1);
	qt_int[2][1] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW3);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 1);
	qt_int[2][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW3);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 1);
	qt_int[2][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW3);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ3, 0);

	// Read fourth row of R
	r_int[3][0] = 0;
	r_int[3][1] = 0;
	r_int[3][2] = 0;

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 1);
	r_int[3][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW4);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 0);

	// Read fourth row of Qt
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 1);
	qt_int[3][0] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW4);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 1);
	qt_int[3][1] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW4);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 1);
	qt_int[3][2] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW4);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 0);

	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 1);
	qt_int[3][3] = qr_ReadReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_ROW4);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_READ4, 0);

	// Reset the accelerator
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_RESET, 1);
	qr_WriteReg(XPAR_QR_1_QR_S_AXI_BASEADDR, QR_RESET, 0);

    // Convert R and Qt from int
    double r[4][4];
    double qt[4][4];
    for(int i = 0; i < 4; i++){
    	for(int j = 0; j < 4; j++){
    		r[i][j] = get_double(r_int[i][j]);
    		qt[i][j] = get_double(qt_int[i][j]);
    	}
    }

	// Matrix-vector multiplication y = Qt*b
    double y[4];
    double sum1;
	for(int i = 0; i < 4; i++){
		sum1 = 0;
		for(int j = 0; j < 4; j++){
			sum1 = sum1 + qt[i][j]*b[j];
		}
		y[i] = sum1;
	}

	// Back-substitution
	x[3] = y[3]/r[3][3];
	x[2] = (y[2] - (r[2][3]*x[3]))/r[2][2];
	x[1] = (y[1] - (r[1][2]*x[2]) - (r[1][3]*x[3]))/r[1][1];
	x[0] = (y[0] - (r[0][1]*x[1]) - (r[0][2]*x[2]) - (r[0][3]*x[3]))/r[0][0];

	// Capture the stop time
	XTime_GetTime(&stop_time_co);

	printf("x = [%f; %f; %f; %f]\n", x[0], x[1], x[2], x[3]);	// Should be [0.8034, -0.3796, 0.2957, 0.1311]

	// Error calculation by recalculating b = A*x
	double error1 = 0.0;
	double b_new1[4];
	double sum2;
	for(int i = 0; i < 4; i++){		// Matrix-vector multiplication
		sum2 = 0;
		for(int j = 0; j < 4; j++){
			sum2 = sum2 + a[i][j]*x[j];
		}
		b_new1[i] = sum2;
		error1 = error1 + abs_double(b[i] - (double)b_new1[i]);
	}
	printf("b_new = [%f; %f; %f; %f]\n", b_new1[0], b_new1[1], b_new1[2], b_new1[3]);

	printf("error in reconstructed b = %f\n", error1);

    // Compute timing on ARM PS hardware
    tt = stop_time_co - start_time_co;
    tt_print = (unsigned) tt;
    printf("Done, Total time steps for PL internal (including ap_fixed emulation) = %d \n", tt_print);
    tt_seconds = COUNTS_PER_SECOND;
    printf("Cycle counts per second for PL internal = %le \n", tt_seconds);
    tt_seconds = (float) tt_print / tt_seconds;
    printf("Time in seconds for PL internal = times steps / COUNTS_PER_SECOND = %le \n", tt_seconds);

    printf("-- End of the Program --\n");

	return 0;
}
