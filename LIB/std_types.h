/*
*************** std_types.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : LIB
*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include"stdint.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64; 

typedef int8_t    sint8;
typedef int16_t   sint16;    
typedef int32_t   sint32;
typedef int64_t   sint64;

typedef float     float32;
typedef double    float64;


/**********/

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64; 

typedef int8_t    s8;
typedef int16_t   s16;    
typedef int32_t   s32;
typedef int64_t   s64;

typedef float     f32;
typedef double    f64;


#define __I       volatile const  // read only reg.
#define __O       volatile        // write only reg.
#define __IO      volatile        // read and write reg.

#define STD_OFF   (0U)
#define STD_ON    (1U)


typedef uint8     boolean;

#ifndef TRUE 
#define TRUE ((boolean)1U)
#endif

#ifndef FALSE 
#define FALSE ((boolean)0U)
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif


typedef uint8 Std_ReturnType;

#define E_OK           ((u8)0x00)
#define E_NOT_OK       ((u8)0x01)
#define E_TIMEOUT      ((u8)0x02)
#define E_NULL_POINTER ((u8)0x03)
#define IDLE_STATE     ((u8)0x04)
#define BUSY_STATE     ((u8)0x05)



#endif /* STD_TYPES_H_*/