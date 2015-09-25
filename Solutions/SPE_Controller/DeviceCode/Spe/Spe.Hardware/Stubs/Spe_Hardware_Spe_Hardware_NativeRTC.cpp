//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------


#include <tinyhal.h>

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rtc.h"

#include "Spe_Hardware.h"
#include "Spe_Hardware_Spe_Hardware_NativeRTC.h"

using namespace Spe::Hardware;

static RTC_InitTypeDef  RTC_InitStructure;
static RTC_DateTypeDef	RTC_DateStruct;
static RTC_TimeTypeDef  RTC_TimeStruct;

INT8 NativeRTC::get_IsInitialized(HRESULT &hr)
{
	return (RTC_ReadBackupRegister(RTC_BKP_DR0) == 0x32F2);
}

void NativeRTC::Native_GetTime(INT32 * param0, INT32 * param1, INT32 * param2, INT32 * param3, INT32 * param4, INT32 * param5, HRESULT &hr)
{
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

	*param0 = RTC_DateStruct.RTC_Year + 2000;
	*param1 = RTC_DateStruct.RTC_Month;
	*param2 = RTC_DateStruct.RTC_Date;

	*param3 = RTC_TimeStruct.RTC_Hours;
	*param4 = RTC_TimeStruct.RTC_Minutes;
	*param5 = RTC_TimeStruct.RTC_Seconds;
}

void NativeRTC::Native_SetTime(INT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, HRESULT &hr)
{
	RTC_DateStruct.RTC_Year = param0 - 2000;
	RTC_DateStruct.RTC_Month = param1;
	RTC_DateStruct.RTC_Date = param2;

	RTC_TimeStruct.RTC_Hours = param3;
	RTC_TimeStruct.RTC_Minutes = param4;
	RTC_TimeStruct.RTC_Seconds = param5;

	RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
}

INT8 NativeRTC::Native_Initialize(UINT32 param0, UINT32 param1, HRESULT &hr)
{
	ErrorStatus status = SUCCESS;

	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);

	if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x32F2)
	{
		/* Configure the RTC data register and RTC prescaler */
		RTC_StructInit(&RTC_InitStructure);

		/* Reset RTC Domain */
		RCC_BackupResetCmd(ENABLE);

		RCC_BackupResetCmd(DISABLE);

		switch (param0)
		{
		case RCC_RTCCLKSource_LSE:
		{
									 /* Enable the LSE OSC */
									 RCC_LSEConfig(RCC_LSE_ON);

									 UINT64 _UINT64_Target = HAL_Time_CurrentTicks() + CPU_MillisecondsToTicks((UINT32)param1);

									 /* Wait till LSE is ready */
									 while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && HAL_Time_CurrentTicks() <= _UINT64_Target);

									 if (HAL_Time_CurrentTicks() > _UINT64_Target)
									 {
										 status = ERROR;
									 }
									 break;
		}

		case RCC_RTCCLKSource_LSI:
			if (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
			{
				/* The RTC Clock may varies due to LSI frequency dispersion */
				/* Enable the LSI OSC */
				RCC_LSICmd(ENABLE);

				/* Wait till LSI is ready */
				while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
			}

			/* Configure the RTC prescaler */
			RTC_InitStructure.RTC_SynchPrediv = 0xF9;
			break;

		case RCC_RTCCLKSource_HSE_Div2:
		case RCC_RTCCLKSource_HSE_Div3:
		case RCC_RTCCLKSource_HSE_Div4:
		case RCC_RTCCLKSource_HSE_Div5:
		case RCC_RTCCLKSource_HSE_Div6:
		case RCC_RTCCLKSource_HSE_Div7:
		case RCC_RTCCLKSource_HSE_Div8:
		case RCC_RTCCLKSource_HSE_Div9:
		case RCC_RTCCLKSource_HSE_Div10:
		case RCC_RTCCLKSource_HSE_Div11:
		case RCC_RTCCLKSource_HSE_Div12:
		case RCC_RTCCLKSource_HSE_Div13:
		case RCC_RTCCLKSource_HSE_Div14:
		case RCC_RTCCLKSource_HSE_Div15:
		case RCC_RTCCLKSource_HSE_Div16:
		case RCC_RTCCLKSource_HSE_Div17:
		case RCC_RTCCLKSource_HSE_Div18:
		case RCC_RTCCLKSource_HSE_Div19:
		case RCC_RTCCLKSource_HSE_Div20:
		case RCC_RTCCLKSource_HSE_Div21:
		case RCC_RTCCLKSource_HSE_Div22:
		case RCC_RTCCLKSource_HSE_Div23:
		case RCC_RTCCLKSource_HSE_Div24:
		case RCC_RTCCLKSource_HSE_Div25:
		case RCC_RTCCLKSource_HSE_Div26:
		case RCC_RTCCLKSource_HSE_Div27:
		case RCC_RTCCLKSource_HSE_Div28:
		case RCC_RTCCLKSource_HSE_Div29:
		case RCC_RTCCLKSource_HSE_Div30:
		case RCC_RTCCLKSource_HSE_Div31:
			/* Configure the RTC prescaler */
			RTC_InitStructure.RTC_SynchPrediv = SYSTEM_CRYSTAL_CLOCK_HZ / (RTC_InitStructure.RTC_AsynchPrediv + 1) / ((param0 & 0x00FF0000) >> 16) - 1;
			break;

		default:
			status = ERROR;
			break;
		}

		if (status == SUCCESS)
		{
			/* Select the RTC Clock Source */
			RCC_RTCCLKConfig(param0);

			/* Enable the RTC Clock */
			RCC_RTCCLKCmd(ENABLE);

			/* Wait for RTC APB registers synchronisation */
			RTC_WaitForSynchro();

			status = RTC_Init(&RTC_InitStructure);

			/* Enable RTC Alarm A Interrupt */
			//RTC_ITConfig(RTC_IT_ALRA, ENABLE);

			/* Enable the alarm */
			//RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

			/* Clear the RTC Alarm Flag */
			RTC_ClearFlag(RTC_FLAG_ALRAF);

			/* Set the date to 0000y 00m 00d */
			RTC_DateStructInit(&RTC_DateStruct);

			RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);

			/* Set the time to 00h 00mn 00s AM */
			RTC_TimeStructInit(&RTC_TimeStruct);

			RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);

			RTC_BypassShadowCmd(ENABLE);

			/* Indicator for the RTC configuration */
			RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
		}
	}
	else
	{
		/* Wait for RTC APB registers synchronisation */
		RTC_WaitForSynchro();

		/* Clear the RTC Alarm Flag */
		RTC_ClearFlag(RTC_FLAG_ALRAF);
	}

	return status;
}

void NativeRTC::Native_Uninitialize(HRESULT &hr)
{
	if (RTC_ReadBackupRegister(RTC_BKP_DR0) == 0x32F2)
	{
		RTC_DeInit();

		if (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == SET)
		{
			/* Disable the LSE OSC */
			RCC_LSEConfig(RCC_LSE_OFF);
		}

		/* Indicator for the RTC configuration */
		RTC_WriteBackupRegister(RTC_BKP_DR0, 0xFFFF);
	}
}

void NativeRTC::Native_SetDayLightSaving(UINT32 param0, UINT32 param1, HRESULT &hr)
{
	RTC_DayLightSavingConfig(param0, param1);
}

void NativeRTC::Native_SetCoarseCalibration(UINT32 param0, UINT32 param1, HRESULT &hr)
{
	RTC_CoarseCalibConfig(param0, param1);
}

void NativeRTC::Native_SetCoarseCalibrationState(INT8 param0, HRESULT &hr)
{
	RTC_CoarseCalibCmd((FunctionalState)param0);
}

void NativeRTC::Native_SetSmoothCalibration(UINT32 param0, UINT32 param1, UINT32 param2, HRESULT &hr)
{
	RTC_SmoothCalibConfig(param0, param1, param2);
}

