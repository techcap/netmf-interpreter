#include <tinyhal.h>
#include "LCDControllers.h"

extern DISPLAY_CONTROLLER_CONFIG g_LcdController_Config;

/*
struct SPI_CONFIGURATION
{
GPIO_PIN       DeviceCS;
BOOL           CS_Active;             // False = LOW active,      TRUE = HIGH active
BOOL           MSK_IDLE;              // False = LOW during idle, TRUE = HIGH during idle
BOOL           MSK_SampleEdge;        // False = sample falling edge, TRUE = samples on rising
BOOL           MD_16bits;
UINT32         Clock_RateKHz;
UINT32         CS_Setup_uSecs;
UINT32         CS_Hold_uSecs;
UINT32         SPI_mod;
GPIO_FLAG      BusyPin;
};
*/

//SPI_CONFIGURATION g_LCDController_SPI_Config =
//{
//	SPI_A025DL02_CS, //DeviceCS
//	SPI_A025DL02_CS_ACTIVE, //CSActive
//	SPI_A025DL02_MSK_IDLE, //MSK_Idle
//	SPI_A025DL02_MSK_SAMPLE_EDGE, //Msk_SampleEdge
//	SPI_A025DL02_16BIT_OP, //MD_16bits
//	SPI_A025DL02_CLOCK_RATE_KHZ, //Clock_RateKHz
//	SPI_A025DL02_CS_SETUP_USEC, //CS_Setup_uSecs;
//	SPI_A025DL02_CS_HOLD_USEC, //CS_Hold_uSec
//	5, //SPI_mod;
//	{
//		SPI_A025DL02_BUSYPIN,
//		SPI_A025DL02_BUSYPIN_ACTIVESTATE,
//	}, //Busypin
//};

void LCDControllers::Init(void)
{ 
	SPI_InitTypeDef    SPI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI6, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_SPI6);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_SPI6);

	SPI_I2S_DeInit(SPI6);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI6, &SPI_InitStructure);

	SPI_Cmd(SPI6, ENABLE);

	WriteCommand(0x28);
	WriteData(0x00);
	WriteData(0x06);

	WriteCommand(0x00);
	WriteData(0x00);
	WriteData(0x01);

	WriteCommand(0x01);
	WriteData(0x72);
	WriteData(0xEF);

	WriteCommand(0x02);
	WriteData(0x06);
	WriteData(0x00);

	WriteCommand(0x11);
	WriteData(0x62);
	WriteData(0x00); //for rotate //0x30 

	WriteCommand(0x10);
	WriteData(0x00);
	WriteData(0x00);

	WriteCommand(0x07);
	WriteData(0x00);
	WriteData(0x33);
}

void LCDControllers::Clear(UINT16 Color)
{
	SetDisplayWindow(0, 0, g_LcdController_Config.Width, g_LcdController_Config.Height);

	WriteCommand(0x22);

	for(int index = 0; index < g_LcdController_Config.Width * g_LcdController_Config.Height; index++)
	{
		WriteData(Color >> 8);
		WriteData(Color & 0x00FF);
	}
}

void LCDControllers::SetCursor(UINT16 Xpos, UINT16 Ypos)
{
	WriteCommand(0x4E);
	WriteData(Xpos >> 8);
	WriteData(Xpos & 0x00FF);

	WriteCommand(0x4F);
	WriteData(0x00);
	WriteData(Ypos);
}

void LCDControllers::DrawChar(UINT8 row, UINT8 column, unsigned char c)
{
	// UINT8 index,_UINT8_FontWidth,_UINT8_FontHeight;
	// UINT16 _UINT16_X,_UINT16_Y;

	// const unsigned char* buffer = Font_GetGlyph(c);

	// _UINT8_FontWidth = Font_Width();
	// _UINT8_FontHeight = Font_Height();
	// _UINT16_X = column * _UINT8_FontWidth;
	// _UINT16_Y = row * _UINT8_FontHeight;

	// SetDisplayWindow(_UINT16_X,_UINT16_Y,_UINT8_FontWidth,_UINT8_FontHeight);

	// WriteCommand(0x22);

	// for(index = 0;index < _UINT8_FontWidth * _UINT8_FontHeight;index++)
	// {
		// if ((buffer[index / _UINT8_FontWidth] >> 7 - index % _UINT8_FontHeight) & 0x01 == 0x01)
		// {
			// WriteData(0XFF);
			// WriteData(0XFF);
		// }
		// else
		// {
			// WriteData(0X00);
			// WriteData(0X00);
		// }
	// }
}

void LCDControllers::SetDisplayWindow(UINT16 Xpos, UINT16 Ypos, UINT16 Width, UINT16 Height)
{
	WriteCommand(0x44);
	WriteData(Ypos + Height - 1);
	WriteData(Ypos);

	WriteCommand(0x45);
	WriteData(Xpos >> 8);
	WriteData(Xpos & 0x00FF);

	WriteCommand(0x46);
	WriteData((Xpos + Width - 1) >> 8);
	WriteData((Xpos + Width - 1) & 0x00FF);

	SetCursor(Xpos, Ypos);
}

void LCDControllers::DrawPict(UINT16 Xpos, UINT16 Ypos, UINT16 Width, UINT16 Height ,const uint32_t *pBitmap)
{
	const uint16_t *bitmap_ptr = ((const uint16_t*)pBitmap);

	SetDisplayWindow(Xpos, Ypos, Width, Height);

	WriteCommand(0x22);

	for(int index = 0;index < Width * Height;index++)
	{
		WriteData(bitmap_ptr[index] >> 8);
		WriteData(bitmap_ptr[index] & 0x00FF);
	}
}

void LCDControllers::WriteCommand(UINT8 address)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);

	GPIO_ResetBits(GPIOC, GPIO_Pin_2);

	SPI_I2S_SendData(SPI6, address);

	while (SPI_I2S_GetFlagStatus(SPI6, SPI_I2S_FLAG_BSY) != RESET);

	GPIO_SetBits(GPIOC, GPIO_Pin_2);

	GPIO_SetBits(GPIOD, GPIO_Pin_13);
}

void LCDControllers::WriteData(UINT8 data)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);

	SPI_I2S_SendData(SPI6, data);

	while (SPI_I2S_GetFlagStatus(SPI6, SPI_I2S_FLAG_BSY) != RESET);

	GPIO_SetBits(GPIOC, GPIO_Pin_2);
}
