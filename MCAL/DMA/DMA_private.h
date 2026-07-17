/*
*************** DMA_private.h ***************
*  Author : Ammar Mohamed Hraga
*  layer  : MCAL
*/

#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H




#define TCIF0_4 5
#define TCIF1_5 11
#define TCIF2_6 21
#define TCIF3_7 27

#define HTIF0_4 4
#define HTIF1_5 10
#define HTIF2_6 20
#define HTIF3_7 26

#define TEIF0_4 3
#define TEIF1_5 9
#define TEIF2_6 19
#define TEIF3_7 25

#define DMEIF0_4 2
#define DMEIF1_5 8
#define DMEIF2_6 18
#define DMEIF3_7 24

#define FEIF0_4 0
#define FEIF1_5 6
#define FEIF2_6 16
#define FEIF3_7 22



#define CTCIF0_4 5
#define CTCIF1_5 11
#define CTCIF2_6 21
#define CTCIF3_7 27

#define CHTIF0_4 4
#define CHTIF1_5 10
#define CHTIF2_6 20
#define CHTIF3_7 26

#define CTEIF0_4 3
#define CTEIF1_5 9
#define CTEIF2_6 19
#define CTEIF3_7 25

#define CDMEIF0_4 2
#define CDMEIF1_5 8
#define CDMEIF2_6 18
#define CDMEIF3_7 24



#define DMA_CR_EN_BIT         0
#define DMA_CR_DMEIE_BIT 	  1
#define DMA_CR_TETE_BIT       2
#define DMA_CR_HTIE_BIT       3
#define DMA_CR_TCIE_BIT       4




#define DMA_CR_DIR_BIT_POS     6
#define DMA_CR_CIRC_BIT_POS    8
#define DMA_CR_PINC_BIT_POS    9
#define DMA_CR_MINC_BIT_POS    10
#define DMA_CR_PSIZE_BIT_POS   11
#define DMA_CR_MSIZE_BIT_POS   13
#define DMA_CR_PL_BIT_POS      16
#define DMA_CR_DBM_BIT_POS     18
#define DMA_CR_PBURST_BIT_POS  21
#define DMA_CR_MBURST_BIT_POS  23
#define DMA_CR_CHSEL_BIT_POS   25

#endif
