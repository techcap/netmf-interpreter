////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "..\LCDController_HAL\LCDControllers.h"

//--//

DISPLAY_CONTROLLER_CONFIG g_LcdController_Config;

UINT8 _UINT8_CurrentRow,_UINT8_CurrentColumn,_UINT8_MaxRows,_UINT8_MaxColumns;

BOOL LCD_Initialize()
{
	g_LcdController_Config.BitsPerPixel = 16;

	g_LcdController_Config.Width = 320;
	g_LcdController_Config.Height = 240;

	_UINT8_MaxColumns = g_LcdController_Config.Width / Font_Width();
	_UINT8_MaxRows = g_LcdController_Config.Height / Font_Height();

    LCD_Controller_Initialize(g_LcdController_Config);
    return TRUE;
}

BOOL LCD_Uninitialize()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return TRUE;
}

void LCD_Clear()
{
	LCDControllers::Clear(0x0000);
}

void LCD_BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    LCDControllers::DrawPict(x,y,width,height,reinterpret_cast<const uint32_t *>(data));
}

void LCD_BitBlt( int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta )
{
	NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
}

void LCD_WriteChar( unsigned char c, int row, int col )
{
	LCDControllers::DrawChar(row,col,c);
}

void LCD_WriteFormattedChar( unsigned char c )
{
	if (_UINT8_CurrentColumn > _UINT8_MaxColumns || c == '\n')
	{
		_UINT8_CurrentColumn = 0;
		_UINT8_CurrentRow++;
	}
	else
	{
		_UINT8_CurrentColumn++;
	}

	if (_UINT8_CurrentRow > _UINT8_MaxRows)
	{
		_UINT8_CurrentRow = 0;
		LCD_Clear();
	}

	LCDControllers::DrawChar(_UINT8_CurrentRow,_UINT8_CurrentColumn,c);
}

INT32 LCD_GetWidth()
{
    return g_LcdController_Config.Width;
}

INT32 LCD_GetHeight()
{
    return g_LcdController_Config.Height;
}

INT32 LCD_GetBitsPerPixel()
{
    return g_LcdController_Config.BitsPerPixel;
}

UINT32 LCD_GetPixelClockDivider()
{
    return g_LcdController_Config.PixelClockDivider;
}
INT32 LCD_GetOrientation()
{
    return g_LcdController_Config.Orientation;
}
void LCD_PowerSave( BOOL On )
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
}

UINT32* LCD_GetFrameBuffer()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return NULL;
}

UINT32 LCD_ConvertColor(UINT32 color)
{
    return color;
}


//--//


