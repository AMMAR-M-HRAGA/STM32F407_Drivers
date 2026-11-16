/*
*************** MPU_private.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/


#ifndef MPU_PRIVATE_H
#define MPU_PRIVATE_H




#define ENABLE  1
#define DISABLE 0

#define MPU_CTRL_ENABLE     0
#define MPU_CTRL_HFNMIENA   1
#define MPU_CTRL_PRIVDEFENA 2


#define MPU_RASR_ENABLE 0

#define MPU_RASR_SIZE_SHIFT     1
#define MPU_RASR_SRD_SHIFT      8
#define MPU_RASR_AP_SHIFT   	24
#define MPU_RASR_XN_SHIFT  		28
#define MPU_RASR_MEM_TYPE_SHIFT 6

#define REGION_MAX_NUMBER 7U

#define MPU_TYPE_NORMAL_WB_NWA  0x0B  // Normal mode write-back and no Write-Allocate (TEX=1 ,C=0 ,B=1 ,S=1 )

#define MPU_TYPE_DEVICE         0x02  // Device memory for Peripherals. (TEX=0 ,C=0 ,B=1 ,S=0 )

#define MPU_STRONGLY_ORDERED    0x00  // Strongly Ordered Memory for System Control Registers











#endif
