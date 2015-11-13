

#include <tinyhal.h>

#include "stm32f4xx.h"
#include "netmf_errors.h"

#include "Spe_Hardware.h"
#include "Spe_Hardware_Spe_Hardware_NativeADC.h"

#define STM32F4_AD_SAMPLE_TIME 2
#define STM32F4_AD_NUM ARRAYSIZE_CONST_EXPR(g_STM32F4_AD_Channel)  
#define STM32_AD_FIRST_CHANNEL 10

#define MIN_SAMPLINGINTERVAL_MICROS 2
#define WHILE_COST 7						//While(var--) takes 7 ticks
#define ADC_LOOP_DELAY_MICROSECONDS 1		//234 ticks = 33.4 usClock =~ 1.393us // (1usClock = 7ticks)

#if STM32F4_ADC == 1
#define ADCx ADC1
#define RCC_APB2ENR_ADCxEN RCC_APB2ENR_ADC1EN
#elif STM32F4_ADC == 3
#define ADCx ADC3
#define RCC_APB2ENR_ADCxEN RCC_APB2ENR_ADC3EN
#else
#error wrong STM32F4_ADC value (1 or 3)
#endif

using namespace Spe::Hardware;

extern const BYTE g_STM32F4_AD_Channel[] = STM32F4_AD_CHANNELS;

bool IsAvailableConfiguration(INT32 samplingInterval, INT32 averageCount)
{
	if (samplingInterval < averageCount * MIN_SAMPLINGINTERVAL_MICROS)
		return false;

	return true;
}

void NativeADC::NativeADCInitialize(CLR_RT_HeapBlock* pMngObj, INT32 pin, HRESULT &hr)
{
	::AD_Initialize((ANALOG_CHANNEL)pin, -1);
}

void NativeADC::NativeADCRead(CLR_RT_HeapBlock* pMngObj, INT32 pin, INT32 count, INT32 samplingInterval, INT32 averageCount, CLR_RT_TypedArray_UINT16 buffer, HRESULT &hr)
{
	//param0: pin, param1: count, param2: samplingInterval, param3: averageCount, param4: buffer
	if (!IsAvailableConfiguration(samplingInterval, averageCount))
	{
		hr = CLR_E_NOT_SUPPORTED;
		return;
	}

	if ((UINT32)pin >= STM32F4_AD_NUM)
		hr = CLR_E_INDEX_OUT_OF_RANGE;

	//ADCx->DR;
	ADCx->SQR3 = g_STM32F4_AD_Channel[pin];

	//UINT16 *averageBuffer = NULL;
	//averageBuffer = (UINT16*)malloc(averageCount * sizeof(UINT16));
	if (averageCount > 100)
	{
		hr = CLR_E_NOT_SUPPORTED;
		return;
	}
	UINT16 averageBuffer[100];

	for (int i = 0; i < count; i++)
	{
		//---ADC sampling---
		for (int j = 0; j < averageCount; j++)					//For loop takes 4 ticks
		{
			ADCx->CR2 |= ADC_CR2_SWSTART;
			while (!(ADCx->SR & ADC_SR_EOC));					//(SWSTART & EOC) takes 200 ticks
			averageBuffer[j] = (UINT16)ADCx->DR;				//ADCx->DR takes 25 ticks
		}

		//Averaging 
		UINT32 sum = 0;
		for (int j = 0; j < averageCount; j++)
		{
			sum += averageBuffer[j];
		}
		buffer[i] = sum / averageCount;

		//depending on averageCount and ADC_LOOP_DELAY_MICROSECONDS
		int ticksPerUS = 168;
		int expectedTotalTicks = samplingInterval * ticksPerUS;
		int wasteTicks = 211 * averageCount + 9 * averageCount;

		int delay = expectedTotalTicks - wasteTicks;
		HAL_Time_Sleep_MicroSeconds(delay / ticksPerUS + 1);	//+1 for rounding up
	}

	free(averageBuffer);
}

INT32 NativeADC::NativeADCRead(CLR_RT_HeapBlock* pMngObj, INT32 pin, INT32 averageCount, HRESULT &hr)
{
	//Averaging 한 값으로 받도록 처리해야 함
	return ::AD_Read((ANALOG_CHANNEL)pin);
}

void NativeADC::NativeADCReadMinMax(CLR_RT_HeapBlock* pMngObj, INT32 pin, INT32 count, INT32 samplingInterval, INT32 averageCount, CLR_RT_TypedArray_UINT16 buffer, UINT16 * min, UINT16 * max, HRESULT &hr)
{
	//param0: pin, param1: count, param2: samplingInterval, param3: averageCount, param4: buffer
	NativeADCRead(pMngObj, pin, count, samplingInterval, averageCount, buffer, hr);

	*min = buffer[0];
	*max = buffer[0];

	for (int i = 0; i < count; i++)
	{
		if (*min > buffer[i])
			*min = buffer[i];
		else if (*max < buffer[i])
			*max = buffer[i];
	}
}

INT32 NativeADC::NativeADCReadSquareSum(CLR_RT_HeapBlock* pMngObj, INT32 pin, INT32 count, INT32 samplingInterval, INT32 averageCount, CLR_RT_TypedArray_UINT32 buffer, HRESULT &hr)
{
	//param0: pin, param1: count, param2: samplingInterval, param3: averageCount, param4: buffer
	//param0: pin, param1: count, param2: samplingInterval, param3: averageCount, param4: buffer
	if (!IsAvailableConfiguration(samplingInterval, averageCount))
	{
		hr = CLR_E_NOT_SUPPORTED;
		return 0;
	}

	if ((UINT32)pin >= STM32F4_AD_NUM)
		hr = CLR_E_INDEX_OUT_OF_RANGE;

	//ADCx->DR;
	ADCx->SQR3 = g_STM32F4_AD_Channel[pin];

	//UINT16 *averageBuffer = NULL;
	//averageBuffer = (UINT16*)malloc(averageCount * sizeof(UINT16));
	if (averageCount > 100)
	{
		hr = CLR_E_NOT_SUPPORTED;
		return 0;
	}
	UINT16 averageBuffer[100];

	for (int i = 0; i < count; i++)
	{
		//---ADC sampling---
		for (int j = 0; j < averageCount; j++)					//For loop takes 4 ticks
		{
			ADCx->CR2 |= ADC_CR2_SWSTART;
			while (!(ADCx->SR & ADC_SR_EOC));					//(SWSTART & EOC) takes 200 ticks
			averageBuffer[j] = (UINT16)ADCx->DR;				//ADCx->DR takes 25 ticks
		}

		//Averaging 
		UINT32 sum = 0;
		for (int j = 0; j < averageCount; j++)
		{
			sum += averageBuffer[j];
		}
		buffer[i] = sum / averageCount;

		//depending on averageCount and ADC_LOOP_DELAY_MICROSECONDS
		int ticksPerUS = 168;
		int expectedTotalTicks = samplingInterval * ticksPerUS;
		int wasteTicks = 211 * averageCount + 9 * averageCount;

		int delay = expectedTotalTicks - wasteTicks;
		HAL_Time_Sleep_MicroSeconds(delay / ticksPerUS + 1);	//+1 for rounding up
	}

	int sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += buffer[i];
	}
	int average = sum / count;

	int squareSum = 0;
	for (int i = 0; i < count; i++)
	{
		buffer[i] -= average;
		squareSum += (buffer[i] * buffer[i]);
	}

	return squareSum;
}

