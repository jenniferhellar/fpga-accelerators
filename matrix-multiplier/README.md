## Systolic Matrix Multiplier
@author Jennifer Hellar
@email jenniferhellar@gmail.com
@date 09/18/2018 

## Hardware target
Xilinx Zedboard for University Development - Xilinx Zynq-7000 chip

## Development software
--------------------------------- Version Log ----------------------------------
Version                                 Path
System Generator 2017.4                 C:/Xilinx/Vivado/2017.4
Matlab 9.2.0.556344 (R2017a)            C:\Program Files\MATLAB\R2017a
Vivado 2017.4                           C:/Xilinx/Vivado/2017.4

## Architecture
A 2D square array of 16 processing elements to accelerate 4x4 matrix 
multiplication and matrix-vector multiplication.  The design includes control 
signals to load, compute, and unload the array.

## Data generation
The data is generated in the Matlab workspace on the host PC and streamed in a 
systolic manner into the rows and columns of the SysGen model.
