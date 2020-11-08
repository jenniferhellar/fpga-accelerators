#include "qr.h"
#ifndef __linux__
int qr_CfgInitialize(qr *InstancePtr, qr_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->qr_BaseAddress = ConfigPtr->qr_BaseAddress;

    InstancePtr->IsReady = 1;
    return XST_SUCCESS;
}
#endif
void qr_write4_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 0, Data);
}
u32 qr_write4_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 0);
    return Data;
}
void qr_write3_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 4, Data);
}
u32 qr_write3_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 4);
    return Data;
}
void qr_write2_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 8, Data);
}
u32 qr_write2_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 8);
    return Data;
}
void qr_write1_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 12, Data);
}
u32 qr_write1_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 12);
    return Data;
}
void qr_start_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 16, Data);
}
u32 qr_start_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 16);
    return Data;
}
void qr_read4_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 20, Data);
}
u32 qr_read4_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 20);
    return Data;
}
void qr_read3_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 24, Data);
}
u32 qr_read3_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 24);
    return Data;
}
void qr_read2_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 28, Data);
}
u32 qr_read2_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 28);
    return Data;
}
void qr_read1_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 32, Data);
}
u32 qr_read1_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 32);
    return Data;
}
void qr_reset_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 36, Data);
}
u32 qr_reset_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 36);
    return Data;
}
void qr_enable_write(qr *InstancePtr, u32 Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 40, Data);
}
u32 qr_enable_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 40);
    return Data;
}
void qr_acol4_write(qr *InstancePtr, int Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 44, Data);
}
int qr_acol4_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 44);
    return Data;
}
void qr_acol3_write(qr *InstancePtr, int Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 48, Data);
}
int qr_acol3_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 48);
    return Data;
}
void qr_acol2_write(qr *InstancePtr, int Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 52, Data);
}
int qr_acol2_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 52);
    return Data;
}
void qr_acol1_write(qr *InstancePtr, int Data) {

    Xil_AssertVoid(InstancePtr != NULL);

    qr_WriteReg(InstancePtr->qr_BaseAddress, 56, Data);
}
int qr_acol1_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 56);
    return Data;
}
u32 qr_done_read(qr *InstancePtr) {

    u32 Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 60);
    return Data;
}
int qr_row1_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 64);
    return Data;
}
int qr_row2_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 68);
    return Data;
}
int qr_row3_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 72);
    return Data;
}
int qr_row4_read(qr *InstancePtr) {

    int Data;
    Xil_AssertVoid(InstancePtr != NULL);

    Data = qr_ReadReg(InstancePtr->qr_BaseAddress, 76);
    return Data;
}
