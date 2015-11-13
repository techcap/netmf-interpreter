////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

//--//
#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)
#define IWDG_ReloadCounter			((uint16_t)0xAAAA)
#define IWDG_StartWatchDog			((uint16_t)0xCCCC)
#define IWDG_Prescaler_256          ((uint8_t)0x06)
#define TIM_IT_CC4                  ((uint16_t)0x0010)

static uint32_t uwLsiFreq = 0;
uint16_t tmpCC4[2] = { 0, 0 };
__IO uint32_t uwCaptureNumber = 0;
__IO uint32_t uwPeriodValue = 0;

static uint32_t GetLSIFrequency(void);
void TIM5_IRQHandler(void);


HRESULT Watchdog_Enable(UINT32 TimeoutMilliseconds, WATCHDOG_INTERRUPT_CALLBACK isr, void* context)
{
	uwLsiFreq = 32768; //GetLSIFrequency(); Timer: For measuring exact lsi freq

	IWDG->KR = IWDG_WriteAccess_Enable;
	IWDG->PR = IWDG_Prescaler_256;
	/*if (TimeoutMilliseconds < 8 || TimeoutMilliseconds > 32768)
		return CLR_E_FAIL;*/

	uint32_t timeout = 4095; //32 seconds
	IWDG->RLR = timeout;
	IWDG->KR = IWDG_ReloadCounter;
	IWDG->KR = IWDG_StartWatchDog;

	return S_OK;
}

void Watchdog_Disable()
{
}

void Watchdog_ResetCpu()
{
}

void Watchdog_ResetCounter()
{
	IWDG->KR = IWDG_ReloadCounter;
}


void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)
	{
		tmpCC4[uwCaptureNumber++] = TIM_GetCapture4(TIM5);
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
		if (uwCaptureNumber >= 2)
		{
			uwPeriodValue = (uint16_t)(0xFFFF - tmpCC4[0] + tmpCC4[1] + 1);
		}
	}
}

static uint32_t GetLSIFrequency(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	RCC_ClocksTypeDef  RCC_ClockFreq;

	RCC_LSICmd(ENABLE);

	/* Wait till LSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{
	}

	/* TIM5 configuration *******************************************************/
	/* Enable TIM5 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	/* Connect internally the TIM5_CH4 Input Capture to the LSI clock output */
	TIM_RemapConfig(TIM5, TIM5_LSI);

	/* Configure TIM5 prescaler */
	TIM_PrescalerConfig(TIM5, 0, TIM_PSCReloadMode_Immediate);

	/* TIM5 configuration: Input Capture mode ---------------------
	The LSI oscillator is connected to TIM5 CH4
	The Rising edge is used as active edge,
	The TIM5 CCR4 is used to compute the frequency value
	------------------------------------------------------------ */
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);

	/* Enable TIM5 Interrupt channel */
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable TIM5 counter */
	TIM_Cmd(TIM5, ENABLE);

	/* Reset the flags */
	TIM5->SR = 0;

	/* Enable the CC4 Interrupt Request */
	TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);


	/* Wait until the TIM5 get 2 LSI edges (refer to TIM5_IRQHandler() in
	stm32f4xx_it.c file) ******************************************************/
	/*while (uwCaptureNumber != 2)
	{
	}*/
	
	/* Deinitialize the TIM5 peripheral registers to their default reset values */
	TIM_DeInit(TIM5);

	/* Compute the LSI frequency, depending on TIM5 input clock frequency (PCLK1)*/
	/* Get SYSCLK, HCLK and PCLKx frequency */
	RCC_GetClocksFreq(&RCC_ClockFreq);

	/* Get PCLK1 prescaler */
	if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0)
	{
		/* PCLK1 prescaler equal to 1 => TIMCLK = PCLK1 */
		return ((RCC_ClockFreq.PCLK1_Frequency / uwPeriodValue) * 8);
	}
	else
	{ /* PCLK1 prescaler different from 1 => TIMCLK = 2 * PCLK1 */
		return (((2 * RCC_ClockFreq.PCLK1_Frequency) / uwPeriodValue) * 8);
	}
}