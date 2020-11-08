// The file cordic.h holds definitions for the data types and constant values
#include "solver.h"

void solver(
		double a[4][4],
		double b[4],
		double x[4])
{
    // Convert A to fixed point
    FIX_16_3 a_fix[4][4];
    for(int i = 0; i < 4; i++){
    	for(int j = 0; j < 4; j++){
    		a_fix[i][j] = a[i][j];
    	}
    }

    // QR decomposition of A returns Qt and R in FIX_16_3
    FIX_16_3 r_fix[4][4], qt_fix[4][4];
    qr_sw(a_fix, qt_fix, r_fix);

    // Convert Qt and R back to double
    double qt[4][4];
    double r[4][4];
    for(int i = 0; i < 4; i++){
    	for(int j = 0; j < 4; j++){
    		qt[i][j] = qt_fix[i][j];
    		r[i][j] = r_fix[i][j];
    	}
    }

	// Matrix-vector multiplication y = Qt*b
    double y[4];
    double sum;
	for(int i = 0; i < 4; i++){
		sum = 0;
		for(int j = 0; j < 4; j++){
			sum = sum + qt[i][j]*b[j];
		}
		y[i] = sum;
	}

	// Back-substitution
	x[3] = y[3]/r[3][3];
	x[2] = (y[2] - (r[2][3]*x[3]))/r[2][2];
	x[1] = (y[1] - (r[1][2]*x[2]) - (r[1][3]*x[3]))/r[1][1];
	x[0] = (y[0] - (r[0][1]*x[1]) - (r[0][2]*x[2]) - (r[0][3]*x[3]))/r[0][0];
}

void qr_sw(
	  FIX_16_3 a[4][4],
	  FIX_16_3 qt[4][4],
	  FIX_16_3 r[4][4])
{
	FIX_16_3 r_temp[4][4];
	FIX_16_3 qt_temp[4][4];

	int col, row, rot_col;
	for(row = 0; row < 4; row++){
		for(col = 0; col < 4; col++){
			r_temp[row][col] = a[row][col];
			qt_temp[row][col] = 0;
		}
	}

	qt_temp[0][0] = 1; qt_temp[1][1] = 1; qt_temp[2][2] = 1; qt_temp[3][3] = 1;

	FIX_16_3 x, y, x1, y1;
	FIX_16_3 x_out, y_out, z_out, angle;

	for(col = 0; col < 4; col++){
		for(row = 2; row >= col; row--){
			x = r_temp[row][col];
			y = r_temp[row+1][col];

			// Perform atan
			cordic(0, x, -y, 0, x_out, y_out, z_out);

			r_temp[row][col] = x_out;
			r_temp[row+1][col] = 0;
			angle = z_out;

			// Propagate rotation to the rest of the R matrix
			for(rot_col = col+1; rot_col < 4; rot_col++){
				x = r_temp[row][rot_col];
				y = r_temp[row+1][rot_col];
				cordic(1, x, y, angle, x_out, y_out, z_out);
				r_temp[row][rot_col] = x_out;
				r_temp[row+1][rot_col] = y_out;
			}

			// Propagate rotation through Q matrix cols
			for(rot_col = 0; rot_col < 4; rot_col++){
				x = qt_temp[row][rot_col];
				y = qt_temp[row+1][rot_col];
				cordic(1, x, y, angle, x_out, y_out, z_out);
				qt_temp[row][rot_col] = x_out;
				qt_temp[row+1][rot_col] = y_out;
			}
		}
	}

	for(row = 0; row < 4; row++){
		for(col = 0; col < 4; col++){
			r[row][col] = r_temp[row][col];
			qt[row][col] = qt_temp[row][col];
		}
	}
}

// The cordic_phase array holds the angle for the current rotation
// The scaling_factors array holds the power of 2 to multiply by for current iteration adjustment

void cordic(bool mode, FIX_16_3 x, FIX_16_3 y, FIX_16_3 z, FIX_16_3 &a, FIX_16_3 &b, FIX_16_3 &c)
{
	// Initialize outputs to zero
	a = 0;
	b = 0;
	c = 0;

	// Vector we will iteratively rotate
	FIX_16_3 current_x;
	FIX_16_3 current_y;

	/* angle is the angle of rotation (= z +/- pi if z is out of our normal range)
	 * theta tracks the accumulated cordic phases
	 *
	 * phase holds the current cordic phase taken from the array
	 * x_shift and y_shift are temporary variables to store the shifted (multiplied by 2^-k) versions of x, y
	 * flag tracks initial conditions to determine necessary post-processing
	 */

	FIX_16_3 angle;
	FIX_16_3 theta = 0;
	FIX_16_3 x_shift, y_shift = 0;
	FIX_16_3 phase;
	char flag = 0;

	/* Pre-processing Control Logic */
	if(mode){					// Rotation is Mode 1
		if(z < -pihalf){			// If rotation greater than pi/2 in either direction
			angle = z + pi;			// Shift back into normal range and set appropriate flag
			flag = 2;
		}
		else if(z > pihalf){
			angle = z - pi;
			flag = 1;
		}
		else{						// Otherwise, normal rotation
			angle = z;
			flag = 0;
		}
		current_x = x;
		current_y = y;
	}
	else{						// Arctan mode
		if(x < 0){					// Check the quadrant of input vector & pre-rotate into I or IV
			if(y >= 0){				// Quadrant II
				current_x = y;
				current_y = -x;
				flag = 3;
			}
			else{
				current_x = -y;		// Quadrant III
				current_y = x;
				flag = 4;
			}
		}
		else{						// Quadrant I or IV (normal calculation)
			current_x = x;
			current_y = y;
			flag = 0;
		}
	}

	/* Main loop */
	RotationLoop: for (int k = 0; k < 32; k++){
		// Multiply by 2^(-k) at each iteration
		x_shift = (current_y >> k);
		y_shift = (current_x >> k);
		phase = cordic_phase[k];

		// Perform rotation by pos or neg angle
		if((mode == 1 && theta < angle) || (mode == 0 && current_y < 0)){
			current_x = current_x - x_shift;
			current_y = current_y + y_shift;
			theta = theta + phase;
		}
		else{
			current_x = current_x + x_shift;
			current_y = current_y - y_shift;
			theta = theta - phase;
		}
	}

	bool negshift;
	char factor;

	/* Approximate scale factor correction */
	ScaleLoop: for (int i = 0; i < 4; i++){
		factor = scaling_factors[i];
		x_shift = current_x >> factor;
		y_shift = current_y >> factor;
		negshift = (i == 0 || i == 2);
		if(negshift)
			current_x = current_x - x_shift;
		else
			current_x = current_x + x_shift;

		if(negshift && (mode == 1))
			current_y = current_y - y_shift;
		else
			current_y = current_y + y_shift;
	}

	/* Post-processing adjustments and assignment to output */
	if(mode){				// Rotation mode
		if(flag){
			a = -current_x;		// Flip signs if z was beyond -pi/2 < z < pi/2
			b = -current_y;
		}
		else{
			a = current_x;		// Normal case
			b = current_y;
		}
		c = 0;
	}
	else{					// Arctan mode
		a = current_x;
		b = 0;
		c = -theta;					// c is opposite the true angle of our vector
		if(flag==3)
				c = c + pihalf;		// Quadrant II adjustment
		if(flag==4)
				c = c - pihalf;		// Quadrant III adjustment
	}
}
