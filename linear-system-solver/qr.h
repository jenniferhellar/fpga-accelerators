#ifndef QR__H
#define QR__H
#ifdef __cplusplus
extern "C" {
#endif
/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "qr_hw.h"
/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 qr_BaseAddress;
} qr_Config;
#endif
/**
* The qr driver instance data. The user is required to
* allocate a variable of this type for every qr device in the system.
* A pointer to a variable of this type is then passed to the driver
* API functions.
*/
typedef struct {
    u32 qr_BaseAddress;
    u32 IsReady;
} qr;
/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define qr_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define qr_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define qr_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define qr_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif
/************************** Function Prototypes *****************************/
#ifndef __linux__
int qr_Initialize(qr *InstancePtr, u16 DeviceId);
qr_Config* qr_LookupConfig(u16 DeviceId);
int qr_CfgInitialize(qr *InstancePtr, qr_Config *ConfigPtr);
#else
int qr_Initialize(qr *InstancePtr, const char* InstanceName);
int qr_Release(qr *InstancePtr);
#endif
/**
* Write to write4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write4 instance to operate on.
* @param	Data is value to be written to gateway write4.
*
* @return	None.
*
* @note    .
*
*/
void qr_write4_write(qr *InstancePtr, u32 Data);
/**
* Read from write4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write4 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_write4_read(qr *InstancePtr);
/**
* Write to write3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write3 instance to operate on.
* @param	Data is value to be written to gateway write3.
*
* @return	None.
*
* @note    .
*
*/
void qr_write3_write(qr *InstancePtr, u32 Data);
/**
* Read from write3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write3 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_write3_read(qr *InstancePtr);
/**
* Write to write2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write2 instance to operate on.
* @param	Data is value to be written to gateway write2.
*
* @return	None.
*
* @note    .
*
*/
void qr_write2_write(qr *InstancePtr, u32 Data);
/**
* Read from write2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write2 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_write2_read(qr *InstancePtr);
/**
* Write to write1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write1 instance to operate on.
* @param	Data is value to be written to gateway write1.
*
* @return	None.
*
* @note    .
*
*/
void qr_write1_write(qr *InstancePtr, u32 Data);
/**
* Read from write1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the write1 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_write1_read(qr *InstancePtr);
/**
* Write to start gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the start instance to operate on.
* @param	Data is value to be written to gateway start.
*
* @return	None.
*
* @note    .
*
*/
void qr_start_write(qr *InstancePtr, u32 Data);
/**
* Read from start gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the start instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_start_read(qr *InstancePtr);
/**
* Write to read4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read4 instance to operate on.
* @param	Data is value to be written to gateway read4.
*
* @return	None.
*
* @note    .
*
*/
void qr_read4_write(qr *InstancePtr, u32 Data);
/**
* Read from read4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read4 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_read4_read(qr *InstancePtr);
/**
* Write to read3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read3 instance to operate on.
* @param	Data is value to be written to gateway read3.
*
* @return	None.
*
* @note    .
*
*/
void qr_read3_write(qr *InstancePtr, u32 Data);
/**
* Read from read3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read3 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_read3_read(qr *InstancePtr);
/**
* Write to read2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read2 instance to operate on.
* @param	Data is value to be written to gateway read2.
*
* @return	None.
*
* @note    .
*
*/
void qr_read2_write(qr *InstancePtr, u32 Data);
/**
* Read from read2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read2 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_read2_read(qr *InstancePtr);
/**
* Write to read1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read1 instance to operate on.
* @param	Data is value to be written to gateway read1.
*
* @return	None.
*
* @note    .
*
*/
void qr_read1_write(qr *InstancePtr, u32 Data);
/**
* Read from read1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the read1 instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_read1_read(qr *InstancePtr);
/**
* Write to reset gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the reset instance to operate on.
* @param	Data is value to be written to gateway reset.
*
* @return	None.
*
* @note    .
*
*/
void qr_reset_write(qr *InstancePtr, u32 Data);
/**
* Read from reset gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the reset instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_reset_read(qr *InstancePtr);
/**
* Write to enable gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the enable instance to operate on.
* @param	Data is value to be written to gateway enable.
*
* @return	None.
*
* @note    .
*
*/
void qr_enable_write(qr *InstancePtr, u32 Data);
/**
* Read from enable gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the enable instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_enable_read(qr *InstancePtr);
/**
* Write to acol4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol4 instance to operate on.
* @param	Data is value to be written to gateway acol4.
*
* @return	None.
*
* @note    .
*
*/
void qr_acol4_write(qr *InstancePtr, int Data);
/**
* Read from acol4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol4 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_acol4_read(qr *InstancePtr);
/**
* Write to acol3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol3 instance to operate on.
* @param	Data is value to be written to gateway acol3.
*
* @return	None.
*
* @note    .
*
*/
void qr_acol3_write(qr *InstancePtr, int Data);
/**
* Read from acol3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol3 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_acol3_read(qr *InstancePtr);
/**
* Write to acol2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol2 instance to operate on.
* @param	Data is value to be written to gateway acol2.
*
* @return	None.
*
* @note    .
*
*/
void qr_acol2_write(qr *InstancePtr, int Data);
/**
* Read from acol2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol2 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_acol2_read(qr *InstancePtr);
/**
* Write to acol1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol1 instance to operate on.
* @param	Data is value to be written to gateway acol1.
*
* @return	None.
*
* @note    .
*
*/
void qr_acol1_write(qr *InstancePtr, int Data);
/**
* Read from acol1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the acol1 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_acol1_read(qr *InstancePtr);
/**
* Read from done gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the done instance to operate on.
*
* @return	u32
*
* @note    .
*
*/
u32 qr_done_read(qr *InstancePtr);
/**
* Read from row1 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the row1 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_row1_read(qr *InstancePtr);
/**
* Read from row2 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the row2 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_row2_read(qr *InstancePtr);
/**
* Read from row3 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the row3 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_row3_read(qr *InstancePtr);
/**
* Read from row4 gateway of qr. Assignments are LSB-justified.
*
* @param	InstancePtr is the row4 instance to operate on.
*
* @return	int
*
* @note    .
*
*/
int qr_row4_read(qr *InstancePtr);
#ifdef __cplusplus
}
#endif
#endif
