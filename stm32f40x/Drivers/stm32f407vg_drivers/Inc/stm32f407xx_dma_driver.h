#ifndef __STM32F4XX_DMA_DRIVER_H_
#define __STM32F4XX_DMA_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	_vo uint32_t CR;
	_vo uint32_t NDTR;
	_vo uint32_t PAR;
	_vo uint32_t M0AR;
	_vo uint32_t M1AR;
	_vo uint32_t FCR;
}DMA_Stream_RegDef_t;

typedef struct
{
	_vo uint32_t LISR;
	_vo uint32_t HISR;
	_vo uint32_t LIFCR;
	_vo uint32_t HIFCR;
}DMA_RegDef_t;

#define DMA1		((DMA_RegDef_t *) DMA1_BASEADDR)
#define DMA1_STREAM0			((DMA_Stream_RegDef_t *) DMA1_STREAM0_BASEADDR)
#define DMA1_STREAM1			((DMA_Stream_RegDef_t *) DMA1_STREAM1_BASEADDR)
#define DMA1_STREAM2			((DMA_Stream_RegDef_t *) DMA1_STREAM2_BASEADDR)
#define DMA1_STREAM3			((DMA_Stream_RegDef_t *) DMA1_STREAM3_BASEADDR)
#define DMA1_STREAM4			((DMA_Stream_RegDef_t *) DMA1_STREAM4_BASEADDR)
#define DMA1_STREAM5			((DMA_Stream_RegDef_t *) DMA1_STREAM5_BASEADDR)
#define DMA1_STREAM6			((DMA_Stream_RegDef_t *) DMA1_STREAM6_BASEADDR)
#define DMA1_STREAM7			((DMA_Stream_RegDef_t *) DMA1_STREAM7_BASEADDR)
#define DMA2		((DMA_RegDef_t *) DMA2_BASEADDR)
#define DMA2_STREAM0			((DMA_Stream_RegDef_t *) DMA2_STREAM0_BASEADDR)
#define DMA2_STREAM1			((DMA_Stream_RegDef_t *) DMA2_STREAM1_BASEADDR)
#define DMA2_STREAM2			((DMA_Stream_RegDef_t *) DMA2_STREAM2_BASEADDR)
#define DMA2_STREAM3			((DMA_Stream_RegDef_t *) DMA2_STREAM3_BASEADDR)

typedef struct 
{
	uint32_t Channel;					/* Channel */
	uint32_t Direction;				/* M2P, M2M, P2M */
	uint32_t PeriAddrIncre;		/* tang dia chi hay khong */
	uint32_t MemAddrIncre;		/* tang dia chi hay khong */
	uint32_t PeriDataWidth;   /* Peripheral data width */
	uint32_t MemDataWidth;		/* Memory data with */
	uint32_t Mode;						/* Circular/ Normal/ Flow Control */
	uint32_t Priority;				/* Priority */
	uint32_t FIFOMode;				/* FIFO mode or Direct mode */
	uint32_t FIFOThreshold;		/* FIFO threshold level */
	uint32_t MemBurst;				/* truyen rieng le hoac truyen tung dot 4,8,16 bit */
	uint32_t PerBurst;				/* truyen rieng le hoac truyen tung dot 4,8,16 bit */
	uint32_t StreamBaseAddr;	/* DMA Stram Base Address */
	uint32_t StreamIndex;			/* DMA Stream Index */
}MCL_Config_t;

typedef struct
{
	DMA_RegDef_t *pDMAx;
	DMA_Stream_RegDef_t *pSTREAMx;
	MCL_Config_t MCLConfig;
	uint32_t ErrorConde;
	uint8_t State;
}MCL_Handle_t;

#endif /* __STM32F4XX_CAN_DRIVER_H_ */
