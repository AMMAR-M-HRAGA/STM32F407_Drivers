/*
*************** MPU_config.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef MUP_CONFIG_H
#define MUP_CONFIG_H

#define MUP_BACKGROUND_REGION                     ENABLE
#dfeine MUP_ENABLE_IN_HARDFAULT_AND_EXCEPTION     ENABLE



           /********** REGION 0 **********/

#define MPU_REGION0_STATUS              ENABLE
#define MPU_REGION0_BASE_ADDRESS        0x08000000
#define MPU_REGION0_SIZE                MPU_SIZE_1MB
#define MPU_REGION0_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION0_XN                  MPU_XN_ENABLE   
#define MPU_REGION0_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA           


           /********** REGION 1 **********/

#define MPU_REGION1_STATUS              ENABLE
#define MPU_REGION1_BASE_ADDRESS        0x20000000
#define MPU_REGION1_SIZE                MPU_SIZE_128KB
#define MPU_REGION1_AP                  MPU_AP_PRV_RW_USR_RW
#define MPU_REGION1_XN                  MPU_XN_DISABLE      
#define MPU_REGION1_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA    


           /********** REGION 2 **********/

#define MPU_REGION2_STATUS              ENABLE
#define MPU_REGION2_BASE_ADDRESS        0x08000000
#define MPU_REGION2_SIZE                MPU_SIZE_1MB
#define MPU_REGION2_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION2_XN                  MPU_XN_DISABLE 
#define MPU_REGION2_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA         


           /********** REGION 3 **********/

#define MPU_REGION3_STATUS              ENABLE
#define MPU_REGION3_BASE_ADDRESS        0x10000000
#define MPU_REGION3_SIZE                MPU_SIZE_64KB
#define MPU_REGION3_AP                  MPU_AP_PRV_RW_USR_NO
#define MPU_REGION3_XN                  MPU_XN_DISABLE  
#define MPU_REGION3_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA        


           /********** REGION 4 **********/

#define MPU_REGION4_STATUS              DISABLE
#define MPU_REGION4_BASE_ADDRESS        0x00000000
#define MPU_REGION4_SIZE                MPU_SIZE_32KB
#define MPU_REGION4_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION4_XN                  MPU_XN_DISABLE 
#define MPU_REGION4_MEM_TYPE            MPU_TYPE_DEVICE        


           /********** REGION 5 **********/ 

#define MPU_REGION5_STATUS              DISABLE
#define MPU_REGION5_BASE_ADDRESS        0x00000000
#define MPU_REGION5_SIZE                MPU_SIZE_32KB
#define MPU_REGION5_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION5_XN                  MPU_XN_DISABLE 
#define MPU_REGION5_MEM_TYPE            MPU_TYPE_DEVICE    

   
           /********** REGION 6 **********/

#define MPU_REGION6_STATUS              DISABLE
#define MPU_REGION6_BASE_ADDRESS        0x00000000
#define MPU_REGION6_SIZE                MPU_SIZE_32KB
#define MPU_REGION6_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION6_XN                  MPU_XN_DISABLE  
#define MPU_REGION6_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA    


           /********** REGION 7 **********/

#define MPU_REGION7_STATUS              DISABLE
#define MPU_REGION7_BASE_ADDRESS        0x00000000
#define MPU_REGION7_SIZE                MPU_SIZE_32KB
#define MPU_REGION7_AP                  MPU_AP_PRV_RO_USR_RO
#define MPU_REGION7_XN                  MPU_XN_DISABLE    
#define MPU_REGION7_MEM_TYPE            MPU_TYPE_NORMAL_WB_NWA      


#endif