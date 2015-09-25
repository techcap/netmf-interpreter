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
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "netmf_errors.h"

#include "Spe_Hardware.h"
#include "Spe_Hardware_Spe_Hardware_NativeSerialPort.h"

using namespace Spe::Hardware;

USART_TypeDef* GetUsart(UINT8 portNumber)
{
	USART_TypeDef* usart;
	switch (portNumber)
	{
	case 0x01:
		usart = USART6;
		break;

	case 0x02:
		usart = USART3;
		break;

	case 0x03:
		usart = USART2;
		break;

	default:
		usart = NULL;
		break;
	}

	return usart;
}

void NativeSerialPort::NativeSerialComm_Open(CLR_RT_HeapBlock* pMngObj, UINT8 portNumber, INT32 baudRate, HRESULT &hr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	USART_TypeDef* usart;
	switch (portNumber)
	{
	case 0x01:
		usart = USART6;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
		break;

	case 0x02:
		usart = USART3;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
		break;

	case 0x03:
		usart = USART2;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
		break;

	default:
		hr = CLR_E_INVALID_OPERATION;
		break;
	}

	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(usart, &USART_InitStructure);

	USART_Cmd(usart, ENABLE);
}

void NativeSerialPort::NativeSerialComm_Close(CLR_RT_HeapBlock* pMngObj, UINT8 param0, HRESULT &hr)
{
	hr = CLR_E_NOTIMPL;
}

void NativeSerialPort::NativeSerialComm_Write(CLR_RT_HeapBlock* pMngObj, UINT8 portNumber, CLR_RT_TypedArray_UINT8 buffer, INT32 offset, INT32 length, HRESULT &hr)
{
	USART_TypeDef* usart = GetUsart(portNumber);

	for (int i = offset; i < offset + length; i++)
	{
		while (!(usart->SR & USART_FLAG_TXE));
		USART_SendData(usart, buffer[i]);
	}
}

INT32 NativeSerialPort::NativeSerialComm_Read(CLR_RT_HeapBlock* pMngObj, UINT8 portNumber, CLR_RT_TypedArray_UINT8 buffer, INT32 offset, INT32 length, HRESULT &hr)
{
	USART_TypeDef* usart = GetUsart(portNumber);

	INT32 count = 0;
	while (1)
	{
		UINT32 timeout = 0x00FFFFFF;
		while (!(usart->SR & USART_FLAG_RXNE))
		{
			if (timeout-- == 0)
			{
				return count;
			}
		}

		buffer[offset + count++] = USART_ReceiveData(usart);

		if (count == length)
			return count;
	}
}

INT32 NativeSerialPort::NativeSerialComm_WriteAndRead(CLR_RT_HeapBlock* pMngObj, UINT8 portNumber, CLR_RT_TypedArray_UINT8 writeBuffer, INT32 writeBufferOffset, INT32 writeBufferCount, CLR_RT_TypedArray_UINT8 readBuffer, INT32 readBufferOffset, INT32 readBufferCount, HRESULT &hr)
{
	USART_TypeDef* usart = GetUsart(portNumber);

	for (int i = writeBufferOffset; i < writeBufferOffset + writeBufferCount; i++)
	{
		while (!(usart->SR & USART_FLAG_TXE));
		USART_SendData(usart, writeBuffer[i]);
	}

	INT32 count = 0;
	while (1)
	{
		UINT32 timeout = 0x00FFFFFF;
		while (!(usart->SR & USART_FLAG_RXNE))
		{
			if (timeout-- == 0)
			{
				//if (usart->SR & (USART_SR_LBD | USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) {
				//      set_error(sdp, sr);
				//      u->SR = 0; /* Clears the LBD bit in the SR.*/
				//}
				usart->SR = 0;
				return count;
			}
		}

		readBuffer[readBufferOffset + count++] = USART_ReceiveData(usart);

		if (count == readBufferCount)
			return count;
	}
}

