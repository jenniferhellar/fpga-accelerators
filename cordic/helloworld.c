/*
 * helloworld.c: simple test application - modified for hls_cordic
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xil_printf.h"


#include <unistd.h>
#include "xcordic.h"
#include "xparameters.h"
#include "xtime_l.h"

XCordic Hls_cordic;


// Setup and helper functions
int hls_cordic_init(XCordic *hls_cordicPtr);
void hls_cordic_start(void *InstancePtr);

int main()
{

	short mode, x, y, z, a, b, c;
	int status;

	xil_printf("-- Start of the Program --\r\n");
	printf("Enter number mode:"); scanf("%hd",&mode);
	printf("The number entered for mode was: %d \n\r", mode);
	printf("Enter number x:"); scanf("%hd",&x);
	printf("The number entered for x was: %d \n\r", x);
	printf("Enter number y:"); scanf("%hd",&y);
	printf("The number entered for y was: %d \n\r", y);
	printf("Enter number z:"); scanf("%hd",&z);
	printf("The number entered for z was: %d \n\r", z);

	a = 0;
	b = 0;
	c = 0;
	printf("Variables initialized before IP, mode= %d, x= %d, y= %d, z= %d, a= %d, b= %d, c= %d \r\n", mode, x, y, z, a, b, c);

	status = hls_cordic_init(&Hls_cordic);
	if(status != XST_SUCCESS){
		print("HLS peripheral setup failed\n\r");
		exit(-1);
	}

	XCordic_Set_mode(&Hls_cordic, mode);
	XCordic_Set_x_V(&Hls_cordic, x);
	XCordic_Set_y_V(&Hls_cordic, y);
	XCordic_Set_z_V(&Hls_cordic, z);


	if (XCordic_IsReady(&Hls_cordic))
		print("HLS peripheral is ready.  Starting... ");
	else {
		print("!!! HLS peripheral is not ready! Exiting...\n\r");
		exit(-1);
	}


// Simple non-interrupt driven test - polling
    XCordic_Start(&Hls_cordic);
    do {
       a = XCordic_Get_a_V(&Hls_cordic);
       b = XCordic_Get_b_V(&Hls_cordic);
       c = XCordic_Get_c_V(&Hls_cordic);
    } while (!XCordic_IsReady(&Hls_cordic));
    print("Detected HLS peripheral complete. Result received.\n\r");

	xil_printf("Variables after IP,  a= %d, b= %d, c= %d \r\n", a, b, c);

    return 0;
}

int hls_cordic_init(XCordic *hls_cordicPtr)
{
   XCordic_Config *cfgPtr;
   int status;

   cfgPtr = XCordic_LookupConfig(XPAR_XCORDIC_0_DEVICE_ID);
   if (!cfgPtr) {
      print("ERROR: Lookup of accelerator configuration failed.\n\r");
      return XST_FAILURE;
   }
   status = XCordic_CfgInitialize(hls_cordicPtr, cfgPtr);
   if (status != XST_SUCCESS) {
      print("ERROR: Could not initialize accelerator.\n\r");
      return XST_FAILURE;
   }
   return status;
}

void hls_cordic_start(void *InstancePtr){
   XCordic *pAccelerator = (XCordic *)InstancePtr;
   XCordic_Start(pAccelerator);
}
