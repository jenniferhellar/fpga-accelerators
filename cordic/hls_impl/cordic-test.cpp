/*
	Testbench
*/
#include <math.h>
#include "cordic.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double abs_double(double var){
	if ( var < 0)
	var = -var;
	return var;
}

const int NUM_DEGREE=180;

int main(int argc, char **argv)
{	
    FILE *fp;

    FIX_16_3 a_hw, b_hw, c_hw, mag_hw, theta_hw;

    // Initial vector
	FIX_16_3 x = 1;
	FIX_16_3 y = 0;
	FIX_16_3 z = 0;
	bool mode = 1;

	double a_sw, b_sw, mag_sw;
	double cos_z, sin_z, theta_sw;

	//Error checking
	double Total_Error_a=0.0;
	double Total_Error_b=0.0;
	double Total_Error_a1=0.0;
	double Total_Error_c1=0.0;
	double error_a=0.0, error_b=0.0, error_a1=0.0, error_c1=0.0;

	fp=fopen("out.dat","w");
	fprintf(fp, "Initial vector at angle -pi/4\n\n");
	for(int i=-NUM_DEGREE;i<NUM_DEGREE;i++) {
			z = (i*pi/180);
			mode = 1;

			// Get hardware result for rotation mode
			cordic(mode, x, y, z, a_hw, b_hw, c_hw);

			// Get software result
			cos_z = cos((double)z);
			sin_z = sin((double)z);
			a_sw = cos_z*(double)x - sin_z*(double)y;
			b_sw = sin_z*(double)x + cos_z*(double)y;

			// Calculate error
			error_a=abs_double((double)a_hw-a_sw);
			error_b=abs_double((double)b_hw-b_sw);
			Total_Error_a=Total_Error_a+error_a;
			Total_Error_b=Total_Error_b+error_b;

			fprintf(fp, "Rotation: degree=%f, a_sw=%f, a_hw=%f, b_sw=%f, b_hw=%f\n", (double)i, a_sw, (double)a_hw, b_sw, (double)b_hw
					);

			mode = 0;
			// Get hardware result for arctan mode
			cordic(mode, (FIX_16_3)(a_sw), (FIX_16_3)(b_sw), 0, mag_hw, b_hw, theta_hw);

			// Get software result
			mag_sw = sqrt(double(pow(a_sw,2)+pow(b_sw,2)));
			if(z <= -pihalf){
				theta_sw = atan(double(-a_sw/b_sw)) - (double)pihalf;
			}
			else if(z >= pihalf){
				theta_sw = atan(double(-a_sw/b_sw)) + (double)pihalf;
			}
			else
				theta_sw = atan(double(b_sw/a_sw));

			// Calculate error
			error_a1 = abs_double((double)mag_hw-mag_sw);
			error_c1 = abs_double((double)theta_hw-theta_sw);
			Total_Error_a1 = Total_Error_a1+error_a1;
			Total_Error_c1 = Total_Error_c1+error_c1;

			fprintf(fp, "Atan: mag_sw=%f, mag_hw=%f, theta_sw=%f, theta_hw=%f\n\n", mag_sw, (double)mag_hw, theta_sw, (double)theta_hw);
	}
	fclose(fp);
	printf ("Total_Error_a=%f, Total_Error_b=%f, Total_Error_mag=%f, Total_Error_theta=%f\n", Total_Error_a, Total_Error_b, Total_Error_a1, Total_Error_c1);
	return 0;
}
