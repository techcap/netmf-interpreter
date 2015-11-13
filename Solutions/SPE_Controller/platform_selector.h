////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Portions (c) Oberon microsystems, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_SPE_Controller_SELECTOR_H_
#define _PLATFORM_SPE_Controller_SELECTOR_H_ 1

/////////////////////////////////////////////////////////
//
// processor and features
//


#if defined(PLATFORM_ARM_SPE_Controller)
#define HAL_SYSTEM_NAME                     "SPE_Controller"

//#define STM32F4XX
//#define PLATFORM_ARM_STM32 /* this is an old designation */
//#define PLATFORM_ARM_STM32F4_ANY /* this is our new designation for STM32F4 */
//#define PLATFORM_ARM_STM32F405RG /* this is our particular MCU */

#define STM32F429X
#define STM32F429_439xx

#define STM32F4_SDRAM

#define PLATFORM_ARM_STM32F4 1 // STM32F407 cpu

#define USB_ALLOW_CONFIGURATION_OVERRIDE  1


//
// processor and features
//
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//
// constants
//

#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTF 5
#define GPIO_PORTG 6
#define GPIO_PORTH 7
#define GPIO_PORTI 8

// The remaining ports are not broken out - except PH0 and PH1,
// which are deliberately omitted to keep the range continuous.

#define PORT_PIN(port,pin) ( ( (int)port) * 16 + ( pin ) )

// System clock
#define SYSTEM_CLOCK_HZ                 168000000   // 168 MHz
#define SYSTEM_CYCLE_CLOCK_HZ           168000000   // 168 MHz
#define SYSTEM_APB1_CLOCK_HZ             42000000   //  42 MHz
#define SYSTEM_APB2_CLOCK_HZ             84000000   //  84 MHz

#define SYSTEM_CRYSTAL_CLOCK_HZ           8000000   // 8 MHz external clock

#define SUPPLY_VOLTAGE_MV                    3300   // 3.3V supply

#define CLOCK_COMMON_FACTOR               1000000   // GCD(SYSTEM_CLOCK_HZ, 1M)

#define SLOW_CLOCKS_PER_SECOND            1000000   // 1 MHz
#define SLOW_CLOCKS_TEN_MHZ_GCD           1000000   // GCD(SLOW_CLOCKS_PER_SECOND, 10M)
#define SLOW_CLOCKS_MILLISECOND_GCD          1000   // GCD(SLOW_CLOCKS_PER_SECOND, 1k)

#define FLASH_MEMORY_Base               0x08000000
#define FLASH_MEMORY_Size               0x00200000
#define SRAM1_MEMORY_Base   0xD0000000
#define SRAM1_MEMORY_Size   0x00800000

#define TXPROTECTRESISTOR               RESISTOR_DISABLED
#define RXPROTECTRESISTOR               RESISTOR_DISABLED
#define CTSPROTECTRESISTOR              RESISTOR_DISABLED
#define RTSPROTECTRESISTOR              RESISTOR_DISABLED

#define TOTAL_GPIO_PORT                 (GPIO_PORTI + 1)
#define TOTAL_GPIO_PINS                 (TOTAL_GPIO_PORT*16)

#define INSTRUMENTATION_H_GPIO_PIN      GPIO_PIN_NONE

#define TOTAL_GENERIC_PORTS             1 // 1 generic port extensions (ITM channel 0 )
#define ITM_GENERIC_PORTNUM             0 // ITM0 is index 0 in generic port interface table

#define DEBUG_TEXT_PORT    ITM0
#define STDIO              ITM0
#define DEBUGGER_PORT      USB1
#define MESSAGING_PORT     USB1

// System Timer configuration (for main time functions)
//#define STM32_32BIT_TIMER 5 /* use 32-bit timer 5 (other option: timer 2) */

// System Timer Configuration
#define STM32F4_32B_TIMER 2
#define STM32F4_16B_TIMER 3

//Pin Configuration
#define STM32F4_ADC 1                              // ADC1 
#define STM32F4_AD_CHANNELS {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F}
// Note PA4 and PA6 is also used by DAC and LCD controller
//      PA5 is also used by DAC

// PWM Configuration
#define STM32F4_PWM_TIMER    {  10,  11,  13,/*   2,*/   9,  12,   1} /* timer numbers use one-based index */
#define STM32F4_PWM_CHNL  {   0,   0,   0,/*   2,*/   0,   1,   2} /* channel values use zero-based index */
#define STM32F4_PWM_PINS      {0x18,0x19,0x06,/*0x1A,*/0x02,0x1F,0x0A}

// SPI3Àº Ethernet
#define STM32F4_SPI_SCLK_PINS {0x05, /*0x1A,*/0xFF, 0x2A, 0x42, 0x57, 0x6D} // PB3, PB10, PC10, PE2, PF7, PG13
#define STM32F4_SPI_MISO_PINS {0x06, /*0x1E,*/0xFF, 0x2B, 0x45, 0x58, 0x6C} // PB4, PB14, PC11, PE5, PF8, PG12
#define STM32F4_SPI_MOSI_PINS {0x07, /*0x1F,*/0xFF, 0x2C, 0x46, 0x59, 0x6E} // PB5, PB15, PC12, PE6, PF9, PG14
//SPI1 PA5|PB3, PA6|PB4, PA7|PB5
//SPI2 PB10|PB13|PD3|PI1, PB14|PC2|PI2, PB15|PC3|PI3
//SPI3 PB3|PC10, PB4|PC11, PB5|PC12|PD6
//SPI4 PE2|PE12, PE5|PE13, PE6|PE14
//SPI5 PF7|PH6, PF8|PH7, PF9|PF11
//SPI6 PG13, PG12, PG14

//#define STM32_UART         {USART2,USART1,USART3, UART4}
//#define STM32_UART_NUM     {     1,     0,    2,      3} /* uart numbers use zero-based index */
//#define STM32_UART_TX_PIN  {  0x35,  0xFF,  0xFF,  0xFF}
//#define STM32_UART_RX_PIN  {  0x36,  0xFF,  0xFF,  0xFF}
//#define STM32_UART_RTS_PIN {  0x34,  0xFF,  0xFF,  0xFF} /* 0xFF = unused */
//#define STM32_UART_CTS_PIN {  0x33,  0xFF,  0xFF,  0xFF} /* 0xFF = unused */

//#define STM32F4_I2C_PORT     1
//#define STM32F4_I2C_SCL_PIN  PORT_PIN( GPIO_PORTB, 8 ) // PB8
//#define STM32F4_I2C_SDA_PIN  PORT_PIN( GPIO_PORTB, 9 ) // PB9

// UART Configuration
#define TOTAL_USART_PORT                3

#define USART_DEFAULT_PORT              COM1
#define USART_DEFAULT_BAUDRATE          115200

//#define STM32_UART         {USART6,USART3,USART2}
//#define STM32_UART_NUM     {     5,     2,     1} /* uart numbers use zero-based index */
//#define STM32_UART_TX_PIN  {  0x26,  0x1A,  0x35}
//#define STM32_UART_RX_PIN  {  0x27,  0x1B,  0x36}
//#define STM32_UART_CTS_PIN {  0xFF,  0xFF,  0xFF} /* 0xFF = unused */
//#define STM32_UART_RTS_PIN {  0xFF,  0xFF,  0xFF} /* 0xFF = unused */

#define STM32F4_UART_RXD_PINS {0x27, 0x1B, 0x36} // PB7, D6, C11
#define STM32F4_UART_TXD_PINS {0x26, 0x1A, 0x35} // PB6, D5, C10
#define STM32F4_UART_CTS_PINS {(BYTE)GPIO_PIN_NONE, (BYTE)GPIO_PIN_NONE, (BYTE)GPIO_PIN_NONE} // GPIO_PIN_NONE, D3, D11
#define STM32F4_UART_RTS_PINS {(BYTE)GPIO_PIN_NONE, (BYTE)GPIO_PIN_NONE, (BYTE)GPIO_PIN_NONE} // GPIO_PIN_NONE, D4, D12

//// User LEDs
//#define LED3 PORT_PIN(GPIO_PORTD, 13) // PD.13 (orange)
//#define LED4 PORT_PIN(GPIO_PORTD, 12) // PD.12 (green)
//#define LED5 PORT_PIN(GPIO_PORTD, 14) // PD.14 (red)
//#define LED6 PORT_PIN(GPIO_PORTD, 15) // PD.15 (blue)

// TinyBooter entry using GPIO
//#define TINYBOOTER_ENTRY_GPIO_PIN       PORT_PIN(GPIO_PORTA, 0) // 'User' button
#define TINYBOOTER_ENTRY_GPIO_STATE     TRUE                    // Active high
#define TINYBOOTER_ENTRY_GPIO_RESISTOR  RESISTOR_DISABLED       // No internal resistor, there is external pull-down (R39)

//TX, RX, CTS, RTS
//USART1 PA9|PB6, PA10|PB7, PA11, PA12 
//USART2 PA2|PD5, PA3|PD6, PA0|PD3, PA1|PD4
//USART3 PB10|PC10|PD8, PB11|PC11|PD9, PB13|PD11, PB14|PD12
//UART4 PA0|PC10, PA1|PC11
//UART5 PC12, PD2
//USART6 PC6|PG14, PC7|PG9, PG13|PG15, PG8|PG12
//UART7 PE8|PF7, PE7|PF6
//UART8 PE1, PE0

//SDRAM
//A0 ,1,2,3,4,5,6 ,7 ,8, 9 ,10 ,11
//PF0,1,2,3,4,5,12,13,14,15,PG0, 1
//D0  ,1 ,2,3,4,5,6,7,8,9,10
//PD14,15,0,1

//#define STM32F4_I2C_PORT     1                                 
//#define STM32F4_I2C_SCL_PIN  0x16
//#define STM32F4_I2C_SDA_PIN  0x17

//
// constants
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// global functions
//

//
// global functions
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// communication facilities
//
#define TOTAL_USB_CONTROLLER            1
#define USB_MAX_QUEUES                  4  // 4 endpoints (EP0 + 3)




#include <processor_selector.h>

#endif // PLATFORM_ARM_SPE_Controller
//
// drivers
/////////////////////////////////////////////////////////

#endif // _PLATFORM_SPE_Controller_SELECTOR_H_
