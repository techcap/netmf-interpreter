////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "LCDControllers.h"

//--//

BOOL LCD_Controller_Initialize( DISPLAY_CONTROLLER_CONFIG& config )
{
	LCDControllers::Init();
    return TRUE;
}

BOOL LCD_Controller_Uninitialize()
{
    return TRUE;
}

BOOL LCD_Controller_Enable( BOOL fEnable )
{
    return TRUE;
}
