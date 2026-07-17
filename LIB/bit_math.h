/*
*************** bit_math.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : LIB
*/

#ifndef BIT_MATH_H
#define BIT_MATH_H 

#define REGISTER_SIZE 32

#define SET_BIT(reg,bit) (reg|=(1UL<<(bit)))
#define CLR_BIT(reg,bit) (reg&=(~(1UL<<(bit))))
#define TOG_BIT(reg,bit) (reg^=(1UL<<(bit)))
#define GET_BIT(reg,bit) ((reg&(1UL<<(bit)))>>(bit))
#define IS_BIT_SET(reg,bit) ((reg&(1UL<<(bit)))>>(bit))
#define IS_BIT_CLR(reg,bit) (!((reg&(1UL<<(bit)))>>(bit)))
#define ROL(reg,num)  (reg=(reg<<(REGISTER_SIZE-((num)%REGISTER_SIZE)))|(reg>>((num)%REGISTER_SIZE)))
#define ROR(reg,num)  (reg=(reg>>(REGISTER_SIZE-((num)%REGISTER_SIZE)))|(reg<<((num)%REGISTER_SIZE)))

#endif 