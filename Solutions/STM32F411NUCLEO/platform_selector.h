#ifndef _PLATFORM_STM32F411NUCLEO_SELECTOR_H_
#define _PLATFORM_STM32F411NUCLEO_SELECTOR_H_

/////////////////////////////////////////////////////////
//
// processor and features
//

#if defined(PLATFORM_ARM_STM32F411NUCLEO)

#define HAL_SYSTEM_NAME "STM32F411NUCLEO"

#define PLATFORM_ARM_STM32F4  // STM32F4XX

#define STM32F40_41xxx

#define USB_ALLOW_CONFIGURATION_OVERRIDE 1

//
// processor and features
//
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//
// constants
//

// System clock
#define SYSTEM_CLOCK_HZ                  96000000   //  96 MHz
#define SYSTEM_CYCLE_CLOCK_HZ            96000000   //  96 MHz
#define SYSTEM_APB1_CLOCK_HZ             48000000   //  48 MHz
#define SYSTEM_APB2_CLOCK_HZ             96000000   //  96 MHz

// FIXME: HSEBYP is not currently supported
#define SYSTEM_CRYSTAL_CLOCK_HZ           8000000   // 8 MHz external clock

#define CLOCK_COMMON_FACTOR               1000000   // GCD(SYSTEM_CLOCK_HZ, 1M)

#define SLOW_CLOCKS_PER_SECOND            1000000   // 1 MHz
#define SLOW_CLOCKS_TEN_MHZ_GCD           1000000   // GCD(SLOW_CLOCKS_PER_SECOND, 10M)
#define SLOW_CLOCKS_MILLISECOND_GCD          1000   // GCD(SLOW_CLOCKS_PER_SECOND, 1k)

#define SUPPLY_VOLTAGE_MV                    3300   // 3.3V supply

// Memory
#define FLASH_MEMORY_Base               0x08000000
#define FLASH_MEMORY_Size               0x00080000  // 512K
#define SRAM1_MEMORY_Base               0x20000000
#define SRAM1_MEMORY_Size               0x00020000  // 128K

// GPIO
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
// The remaining ports are not broken out - except PD2, PH0 and PH1,
// which are deliberately omitted to reduce memory consumption (PD2)
// and to keep the range continuous (PH0, PH1).

#define TOTAL_GPIO_PORT                 (GPIO_PORTC + 1)
#define TOTAL_GPIO_PINS                 (TOTAL_GPIO_PORT*16)

#define PORT_PIN(port,pin)              (((int)port)*16 + (pin))

// Communication

#define TOTAL_USART_PORT                2 // FIXME: 3

#define USART_DEFAULT_PORT              COM1
#define USART_DEFAULT_BAUDRATE          115200

#define TOTAL_GENERIC_PORTS             1 // 1 generic port extensions (ITM channel 0 )
#define ITM_GENERIC_PORTNUM             0 // ITM0 is index 0 in generic port interface table

// FIXME: Link how to view ITM output

#define DEBUG_TEXT_PORT                 ITM0
#define STDIO                           ITM0
#define DEBUGGER_PORT                   USB1
#define MESSAGING_PORT                  USB1

#define TOTAL_USB_CONTROLLER            1
#define USB_MAX_QUEUES                  4  // 4 endpoints (EP0 + 3)

// System Timer Configuration
#define STM32F4_32B_TIMER 2
#define STM32F4_16B_TIMER 3

// COM1 (0) - USART1 (APB2)
// COM2 (1) - USART2 (APB1)

//                              USART1 (APB2)             USART2 (ABP1)
#define STM32F4_UART_TXD_PINS { PORT_PIN(GPIO_PORTA,  9), PORT_PIN(GPIO_PORTA, 2) }
#define STM32F4_UART_RXD_PINS { PORT_PIN(GPIO_PORTA, 10), PORT_PIN(GPIO_PORTA, 3) }


//                              USART2                   USART6                   USART1
//#define STM32F4_UART_RXD_PINS { PORT_PIN(GPIO_PORTA, 3) } //, PORT_PIN(GPIO_PORTC,  7), PORT_PIN(GPIO_PORTA, 10) }
//#define STM32F4_UART_TXD_PINS { PORT_PIN(GPIO_PORTA, 2) } //, PORT_PIN(GPIO_PORTC,  6), PORT_PIN(GPIO_PORTA,  9) }
// RX                                                    PORT_PIN(GPIO_PORTA, 12), PORT_PIN(GPIO_PORTB,  3)
// TX                                                    PORT_PIN(GPIO_PORTA, 11), PORT_PIN(GPIO_PORTA, 15)
// RX                                                                              PORT_PIN(GPIO_PORTB,  7)
// TX                                                                              PORT_PIN(GPIO_PORTA,  6)
//#define STM32F4_UART_CTS_PINS {(BYTE)GPIO_PIN_NONE } //, 51, 59} // GPIO_PIN_NONE, D3, D11
//#define STM32F4_UART_RTS_PINS {(BYTE)GPIO_PIN_NONE } //, 52, 60} // GPIO_PIN_NONE, D4, D12

// FIXME: Pin Configuration
#define STM32F4_ADC 3
#define STM32F4_AD_CHANNELS {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}

#define STM32F4_PWM_TIMER {4,4,4,4}
#define STM32F4_PWM_CHNL  {0,1,2,3}
#define STM32F4_PWM_PINS  {60,61,62,63} // PD12-PD15

#define STM32F4_SPI_SCLK_PINS {5, 29, 42} // PA5, PB13, PC10
#define STM32F4_SPI_MISO_PINS {6, 30, 43} // PA6, PB14, PC11
#define STM32F4_SPI_MOSI_PINS {7, 31, 44} // PA7, PB15, PC12

#define STM32F4_I2C_PORT     1
#define STM32F4_I2C_SCL_PIN  PORT_PIN( GPIO_PORTB, 8 ) // PB8
#define STM32F4_I2C_SDA_PIN  PORT_PIN( GPIO_PORTB, 9 ) // PB9


// User LEDs
#define LED2                            PORT_PIN(GPIO_PORTA, 5) // Green

// TinyBooter entry using GPIO
#define TINYBOOTER_ENTRY_GPIO_PIN       PORT_PIN(GPIO_PORTC, 13)  // 'User' button
#define TINYBOOTER_ENTRY_GPIO_STATE     FALSE                     // Active low
#define TINYBOOTER_ENTRY_GPIO_RESISTOR  RESISTOR_DISABLED         // No internal resistor, there is external pull-up (R30)

//
// constants
/////////////////////////////////////////////////////////

#include <processor_selector.h>

#endif // PLATFORM_ARM_STM32F411NUCLEO

#endif // _PLATFORM_STM32F411NUCLEO_SELECTOR_H_
