/*
*************** MPU_interface.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef MPU_INTERFACE_H
#define MPU_INTERFACE_H


#define MPU_TYPE_NORMAL_WB_NWA  0x0B  // Normal mode write-back and no Write-Allocate (TEX=1 ,C=0 ,B=1 ,S=1 )

#define MPU_TYPE_DEVICE         0x02  // Device memory for Peripherals. (TEX=0 ,C=0 ,B=1 ,S=0 )

#define MPU_STRONGLY_ORDERED    0x00  // Strongly Ordered Memory for System Control Registers




#define MPU_REGION0 0
#define MPU_REGION1 1
#define MPU_REGION2 2
#define MPU_REGION3 3
#define MPU_REGION4 4
#define MPU_REGION5 5
#define MPU_REGION6 6
#define MPU_REGION7 7

#define MPU_SIZE_32B   4
#define MPU_SIZE_1KB   9
#define MPU_SIZE_4KB   11
#define MPU_SIZE_16KB  13
#define MPU_SIZE_64KB  15
#define MPU_SIZE_128KB 16
#define MPU_SIZE_1MB   19


#define MPU_AP_PRV_NO_USR_NO    0
#define MPU_AP_PRV_RW_USR_NO    1
#define MPU_AP_PRV_RW_USR_RO    2
#define MPU_AP_PRV_RW_USR_RW    3
#define MPU_AP_PRV_RO_USR_RO    6

#define MPU_XN_ENABLE 0
#define MPU_XN_DISABLE 1


typedef struct {
	u8 RegionState;
	u8 RegionNumber;
	u8 RegionSize;
	u8 RegionPermission;
	u8 RegionXNSelect;
	u32 RegionAddress;
	u8 RegionMemType;
}MPU_RegionConfig_t;





void MPU_voidInit(void);
void MPU_voidConfigRegion(MPU_RegionConfig_t * MPU_RegionConfig );
void MPU_voidEnable(void);
void MPU_voidDisable(void);
void MemManageFault_voidEnable(void);
void MemManageFault_voidDisable(void);

#endif