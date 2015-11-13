////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
//#include "stm32.h"
#include "stm32f429i_discovery_ioe.cpp"

//--//

void Touch_ISR(GPIO_PIN Pin, BOOL PinState, void* Param);
BOOL GetCalibrationPoint(TOUCH_PANEL_CALIBRATION_POINT* point);

GPIO_INTERRUPT_SERVICE_ROUTINE g_touchIsrProc;

#define TOUCH_SCREEN_INTEERUPT_PIN	0x89

BOOL HAL_TOUCH_PANEL_Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
	/* Configure the needed pins */
	IOE_GPIO_Config();

	/* I2C initialization */
	IOE_I2C_Config();

	/* Read IO Expander ID  */
	if (IOE_IsOperational())
	{
		return IOE_NOT_OPERATIONAL;
	}

	/* Generate IO Expander Software reset */
	IOE_Reset();

	/* IO Expander configuration */
	/* Touch Panel controller and ADC configuration */
	IOE_FnctCmd(IOE_ADC_FCT, ENABLE);
	IOE_TP_Config();

	/* Configure the interrupts */
	g_touchIsrProc = touchIsrProc;
	CPU_GPIO_EnableInputPin(TOUCH_SCREEN_INTEERUPT_PIN, FALSE, Touch_ISR, GPIO_INT_EDGE_BOTH, RESISTOR_PULLUP);

	/* Enable the Global interrupt */
	IOE_GITCmd(ENABLE);

	/* Enable the Global GPIO Interrupt */
	IOE_GITConfig((uint8_t)(IOE_GIT_TOUCH /*| IOE_GIT_FTH | IOE_GIT_FOV*/), ENABLE);

	/* Read the GPIO_IT_STA to clear all pending bits if any */
	I2C_ReadDeviceRegister(IOE_REG_GPIO_INT_STA);


	/* Configuration is OK */
	return TRUE;
}

BOOL HAL_TOUCH_PANEL_Disable()
{
	return FALSE;
}

void HAL_TOUCH_PANEL_GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY)
{
	uint32_t xDiff, yDiff, x, y;
	static uint32_t _x = 0, _y = 0;

	static BOOL TouchDetected;
	static BOOL PrevTouchDetected = 0;

	/* Save previous touch state */
	PrevTouchDetected = TouchDetected;

	/* Check if the Touch detect event happened */
	TouchDetected = I2C_ReadDeviceRegister(IOE_REG_TP_CTRL) & 0x80;

	if (TouchDetected)
	{
		if (PrevTouchDetected)
			*pTipState = TouchSampleValidFlag | TouchSamplePreviousDownFlag | TouchSampleDownFlag;
		else
			*pTipState = (TouchSampleValidFlag | TouchSampleDownFlag);

		x = IOE_TP_Read_X();
		y = IOE_TP_Read_Y();

		if ((x >= 237) || (x < 3))
		{
			/* Ignore this touch event */
			*pTipState = TouchSampleIgnore;
		}
		else
		{
			if (PrevTouchDetected)
				*pTipState = TouchSampleValidFlag | TouchSamplePreviousDownFlag | TouchSampleDownFlag;
			else
				*pTipState = (TouchSampleValidFlag | TouchSampleDownFlag);
		}
		xDiff = x > _x ? (x - _x) : (_x - x);
		yDiff = y > _y ? (y - _y) : (_y - y);
		if (xDiff + yDiff > 5)
		{
			/* Update the X position */
			_x = x;

			/* Update the Y position */
			_y = y;
		}
	}
	else
	{
		if (PrevTouchDetected)
			*pTipState = TouchSampleValidFlag | TouchSamplePreviousDownFlag;
		else
			*pTipState = TouchSampleIgnore;
	}

	*pUnCalX = _x;
	*pUnCalY = _y;
	// *pUnCalX = _y;
	// *pUnCalY = 239 - _x;  
}

HRESULT HAL_TOUCH_PANEL_GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
	if (lpOutput == NULL)
	{
		return FALSE;
	}

	switch (iIndex)
	{
	case TOUCH_PANEL_SAMPLE_RATE_ID:
	{
		TOUCH_PANEL_SAMPLE_RATE  *pSampleRate = (TOUCH_PANEL_SAMPLE_RATE*)lpOutput;

		pSampleRate->CurrentSampleRateSetting = g_TouchPanel_Sampling_Settings.SampleRate.CurrentSampleRateSetting;
		pSampleRate->MaxTimeForMoveEvent_ticks = g_TouchPanel_Sampling_Settings.SampleRate.MaxTimeForMoveEvent_ticks;
		pSampleRate->SamplesPerSecondLow = g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondLow;
		pSampleRate->SamplesPerSecondHigh = g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondHigh;
		break;
	}
	case TOUCH_PANEL_CALIBRATION_POINT_COUNT_ID:
	{
		TOUCH_PANEL_CALIBRATION_POINT_COUNT *pCalibrationPts = (TOUCH_PANEL_CALIBRATION_POINT_COUNT*)lpOutput;

		pCalibrationPts->cCalibrationPoints = 5;
		pCalibrationPts->flags = 0;

		break;
	}
	case TOUCH_PANEL_CALIBRATION_POINT_ID:
		return GetCalibrationPoint((TOUCH_PANEL_CALIBRATION_POINT*)lpOutput);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}


void Touch_ISR(GPIO_PIN Pin, BOOL PinState, void* Param)
{

	if (IOE_GetGITStatus(IOE_GIT_TOUCH) == SET)
	{
		if (g_touchIsrProc)
		{
			if (I2C_ReadDeviceRegister(IOE_REG_TP_CTRL) & 0x80)
				g_touchIsrProc(Pin, FALSE, NULL);
			else
				g_touchIsrProc(Pin, TRUE, NULL);
		}
	}

	/* Read the GPIO_IT_STA to clear all pending bits if any */
	I2C_ReadDeviceRegister(IOE_REG_GPIO_INT_STA);

	/* Clear the interrupt pending bit and enable the FIFO again */
	I2C_WriteDeviceRegister(IOE_REG_INT_STA, 0xFF);
	I2C_WriteDeviceRegister(IOE_REG_FIFO_STA, 0x01);
	I2C_WriteDeviceRegister(IOE_REG_FIFO_STA, 0x00);
}

BOOL GetCalibrationPoint(TOUCH_PANEL_CALIBRATION_POINT* point)
{
	int dX = point->cDisplayWidth / 20;
	int dY = point->cDisplayHeight / 20;

	switch (point->PointNumber)
	{
	case    0:
		point->CalibrationX = point->cDisplayWidth / 2;
		point->CalibrationY = point->cDisplayHeight / 2;
		break;

	case    1:
		point->CalibrationX = dX * 2;
		point->CalibrationY = dY * 2;
		break;

	case    2:
		point->CalibrationX = dX * 2;
		point->CalibrationY = point->cDisplayHeight - dY * 2;
		break;

	case    3:
		point->CalibrationX = point->cDisplayWidth - dX * 2;
		point->CalibrationY = point->cDisplayHeight - dY * 2;
		break;

	case    4:
		point->CalibrationX = point->cDisplayWidth - dX * 2;
		point->CalibrationY = dY * 2;
		break;

	default:
		point->CalibrationX = point->cDisplayWidth / 2;
		point->CalibrationY = point->cDisplayHeight / 2;

		return FALSE;
	}

	return TRUE;
}
