/**
  ******************************************************************************
  * @file    STM324x7i_eval_lcd.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-January-2013
  * @brief   This file contains all the functions prototypes for the STM324x7i_eval_lcd.c
  *          driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LCDControllers_H
#define _LCDControllers_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_spi.h"

class LCDControllers
{
	public:
		static void Init(void);
		static void Clear(uint16_t Color);
		static void SetCursor(uint16_t Xpos, uint16_t Ypos);
		static void DrawChar(uint8_t row, uint8_t column, unsigned char c);
		static void SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, UINT16 Width, UINT16 Height);
		static void DrawPict(UINT16 Xpos, UINT16 Ypos, UINT16 Width, UINT16 Height ,const uint32_t *pBitmap);

		static void WriteCommand(UINT8 address);
		static void WriteData(UINT8 data);
};
#endif
