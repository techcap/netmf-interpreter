////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for the MCBSTM32F400 board (STM32F4): Copyright (c) Oberon microsystems, Inc.
//
//  *** STM32F4DISCOVERY Board specific IO Port Initialization ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "stm32f4xx.h"

#ifdef STM32F4_SDRAM
#include "stm32f429i_discovery_sdram.h"
#endif

/* Pin Configuration Register Values
0x0  Analog Input
0x1  Output 10Mhz
0x2  Output  2Mhz
0x3  Output 50Mhz
0x4  Floating Input (default)
0x5  Open-Drain 10Mhz
0x6  Open-Drain  2Mhz
0x7  Open-Drain 50Mhz
0x8  Input with pull up/down
0x9  Alternate Output 10Mhz
0xA  Alternate Output  2Mhz
0xB  Alternate Output 50Mhz
0xC     -
0xD  Alternate Open-Drain 10Mhz
0xE  Alternate Open-Drain  2Mhz
0xF  Alternate Open-Drain 50Mhz
*/

// Define the generic port table, only one generic extensionn port type supported
// and that is the ITM hardware trace port on Channel 0.
extern GenericPortTableEntry const Itm0GenericPort;
extern GenericPortTableEntry const* const g_GenericPorts[TOTAL_GENERIC_PORTS] = { &Itm0GenericPort };

extern void STM32F4_GPIO_Pin_Config(GPIO_PIN pin, UINT32 mode, GPIO_RESISTOR resistor, UINT32 alternate);    // Workaround, since CPU_GPIO_DisablePin() does not correctly initialize pin speeds

void __section("SectionForBootstrapOperations") BootstrapCode_GPIO()
{
	//SWD
	CPU_GPIO_ReservePin(13, TRUE);
	CPU_GPIO_ReservePin(14, TRUE);
	CPU_GPIO_ReservePin(16 + 3, TRUE);

	// Enable GPIO clocks for ports A - I
	RCC->AHB1ENR |=
		RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN |
		RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN |
		RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOHEN | RCC_AHB1ENR_GPIOIEN;

	//// TODO: Restore at the end of bootloader?
	//CPU_GPIO_EnableOutputPin(LED3, FALSE);
	//CPU_GPIO_EnableOutputPin(LED4, FALSE);
	//CPU_GPIO_EnableOutputPin(LED5, FALSE);
	//CPU_GPIO_EnableOutputPin(LED6, FALSE);

#ifdef STM32F4_SDRAM
	SDRAM_Init();
#endif
}
