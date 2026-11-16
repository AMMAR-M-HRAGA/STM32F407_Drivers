/*
*************** MPU_config.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef MUP_CONFIG_H
#define MUP_CONFIG_H

#include "MPU_interface.h"
#include "MPU_private.h"


#define MPU_BACKGROUND_REGION                     ENABLE
#define MPU_ENABLE_IN_HARDFAULT_AND_EXCEPTION     ENABLE



           /********** REGION 0 **********/

#define MPU_REGION0_STATUS              ENABLE
#define MPU_REGION0_BASE_ADDRESS        0x20000000
#define MPU_REGION0_SIZE                MPU_SIZE_32B
#define MPU_REGION0_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION0_XN                  MPU_XN_ENABLE   
#define MPU_REGION0_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA           

static MPU_RegionConfig_t MPU_RegionConfig0 = {
	
    .RegionState = MPU_REGION0_STATUS,
	.RegionNumber = 0,
	.RegionSize  = MPU_REGION0_SIZE,
	.RegionPermission = MPU_REGION0_AP,
	.RegionXNSelect = MPU_REGION0_XN,
	.RegionAddress = MPU_REGION0_BASE_ADDRESS,
	.RegionMemType = MPU_REGION0_MEM_TYPE,
};

           /********** REGION 1 **********/

#define MPU_REGION1_STATUS              ENABLE
#define MPU_REGION1_BASE_ADDRESS        0x20000000
#define MPU_REGION1_SIZE                MPU_SIZE_128KB
#define MPU_REGION1_AP                  MPU_AP_PRV_RW_USR_RW
#define MPU_REGION1_XN                  MPU_XN_DISABLE      
#define MPU_REGION1_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA    

static MPU_RegionConfig_t MPU_RegionConfig1 = {
	
    .RegionState = MPU_REGION1_STATUS,
	.RegionNumber = 1,
	.RegionSize  = MPU_REGION1_SIZE,
	.RegionPermission = MPU_REGION1_AP,
	.RegionXNSelect = MPU_REGION1_XN,
	.RegionAddress = MPU_REGION1_BASE_ADDRESS,
	.RegionMemType = MPU_REGION1_MEM_TYPE,
};


           /********** REGION 2 **********/

#define MPU_REGION2_STATUS              ENABLE
#define MPU_REGION2_BASE_ADDRESS        0x08000000
#define MPU_REGION2_SIZE                MPU_SIZE_1MB
#define MPU_REGION2_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION2_XN                  MPU_XN_DISABLE 
#define MPU_REGION2_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA         

static MPU_RegionConfig_t MPU_RegionConfig2 = {
	
    .RegionState = MPU_REGION2_STATUS,
	.RegionNumber = 2,
	.RegionSize  = MPU_REGION2_SIZE,
	.RegionPermission = MPU_REGION2_AP,
	.RegionXNSelect = MPU_REGION2_XN,
	.RegionAddress = MPU_REGION2_BASE_ADDRESS,
	.RegionMemType = MPU_REGION2_MEM_TYPE,
};


           /********** REGION 3 **********/

#define MPU_REGION3_STATUS              ENABLE
#define MPU_REGION3_BASE_ADDRESS        0x10000000
#define MPU_REGION3_SIZE                MPU_SIZE_64KB
#define MPU_REGION3_AP                  MPU_AP_PRV_RW_USR_NO
#define MPU_REGION3_XN                  MPU_XN_DISABLE  
#define MPU_REGION3_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA        

static MPU_RegionConfig_t MPU_RegionConfig3 = {
	
    .RegionState = MPU_REGION3_STATUS,
	.RegionNumber = 3,
	.RegionSize  = MPU_REGION3_SIZE,
	.RegionPermission = MPU_REGION3_AP,
	.RegionXNSelect = MPU_REGION3_XN,
	.RegionAddress = MPU_REGION3_BASE_ADDRESS,
	.RegionMemType = MPU_REGION3_MEM_TYPE,
};


           /********** REGION 4 **********/

#define MPU_REGION4_STATUS              DISABLE
#define MPU_REGION4_BASE_ADDRESS        0x00000000
#define MPU_REGION4_SIZE                MPU_SIZE_64KB
#define MPU_REGION4_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION4_XN                  MPU_XN_DISABLE 
#define MPU_REGION4_MEM_TYPE            MPU_TYPE_DEVICE        

static MPU_RegionConfig_t MPU_RegionConfig4 = {
	
    .RegionState = MPU_REGION4_STATUS,
	.RegionNumber = 4,
	.RegionSize  = MPU_REGION4_SIZE,
	.RegionPermission = MPU_REGION4_AP,
	.RegionXNSelect = MPU_REGION4_XN,
	.RegionAddress = MPU_REGION4_BASE_ADDRESS,
	.RegionMemType = MPU_REGION4_MEM_TYPE,
};



           /********** REGION 5 **********/ 

#define MPU_REGION5_STATUS              DISABLE
#define MPU_REGION5_BASE_ADDRESS        0x00000000
#define MPU_REGION5_SIZE                MPU_SIZE_64KB
#define MPU_REGION5_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION5_XN                  MPU_XN_DISABLE 
#define MPU_REGION5_MEM_TYPE            MPU_TYPE_DEVICE    

static MPU_RegionConfig_t MPU_RegionConfig5 = {
	
    .RegionState = MPU_REGION5_STATUS,
	.RegionNumber = 5,
	.RegionSize  = MPU_REGION5_SIZE,
	.RegionPermission = MPU_REGION5_AP,
	.RegionXNSelect = MPU_REGION5_XN,
	.RegionAddress = MPU_REGION5_BASE_ADDRESS,
	.RegionMemType = MPU_REGION5_MEM_TYPE,
};

   
           /********** REGION 6 **********/

#define MPU_REGION6_STATUS              DISABLE
#define MPU_REGION6_BASE_ADDRESS        0x00000000
#define MPU_REGION6_SIZE                MPU_SIZE_64KB
#define MPU_REGION6_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION6_XN                  MPU_XN_DISABLE  
#define MPU_REGION6_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA    

static MPU_RegionConfig_t MPU_RegionConfig6 = {
	
    .RegionState = MPU_REGION6_STATUS,
	.RegionNumber = 6,
	.RegionSize  = MPU_REGION6_SIZE,
	.RegionPermission = MPU_REGION6_AP,
	.RegionXNSelect = MPU_REGION6_XN,
	.RegionAddress = MPU_REGION6_BASE_ADDRESS,
	.RegionMemType = MPU_REGION6_MEM_TYPE,
};


           /********** REGION 7 **********/

#define MPU_REGION7_STATUS              DISABLE
#define MPU_REGION7_BASE_ADDRESS        0x00000000
#define MPU_REGION7_SIZE                MPU_SIZE_64KB
#define MPU_REGION7_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION7_XN                  MPU_XN_DISABLE    
#define MPU_REGION7_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA      

static MPU_RegionConfig_t MPU_RegionConfig7 = {
	
    .RegionState = MPU_REGION7_STATUS,
	.RegionNumber = 7,
	.RegionSize  = MPU_REGION7_SIZE,
	.RegionPermission = MPU_REGION7_AP,
	.RegionXNSelect = MPU_REGION7_XN,
	.RegionAddress = MPU_REGION7_BASE_ADDRESS,
	.RegionMemType = MPU_REGION7_MEM_TYPE,
};


#endif
