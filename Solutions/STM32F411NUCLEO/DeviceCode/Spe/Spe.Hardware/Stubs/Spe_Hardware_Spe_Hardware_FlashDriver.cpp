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


#include "Spe_Hardware.h"
#include "Spe_Hardware_Spe_Hardware_FlashDriver.h"
#include <tinyhal.h>

extern struct BlockStorageDevice  g_STM32F4_BS;

using namespace Spe::Hardware;

INT32 FlashDriver::NativeRead( INT32 address, UINT32 numBytes, CLR_RT_TypedArray_UINT8 buffer, HRESULT &hr )
{
    INT32 retVal = 0; 

	g_STM32F4_BS.Read(address, numBytes, &(buffer[0]));

    return retVal;
}

INT32 FlashDriver::NativeWrite( INT32 address, UINT32 numBytes, CLR_RT_TypedArray_UINT8 buffer, HRESULT &hr )
{
    INT32 retVal = 0; 
	g_STM32F4_BS.Write(address, numBytes, &(buffer[0]), FALSE);
    return retVal;
}

