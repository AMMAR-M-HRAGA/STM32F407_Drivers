/*
*************** bit_math.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : LIB
*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include"stdint.h"

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

#ifndef TRUE 
#define TRUE (1U)
#endif

#ifndef FALSE 
#define FALSE (0U)
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef u8 Std_ReturnType;

#define E_OK           ((u8)0x00)
#define E_NOT_OK       ((u8)0x01)
#define E_TIMEOUT      ((u8)0x02)
#define E_NULL_PINTER  ((u8)0x03)


#endif /* STD_TYPES_H_*/