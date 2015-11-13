////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

//--//

//HRESULT Watchdog_Enable( UINT32 TimeoutMilliseconds, WATCHDOG_INTERRUPT_CALLBACK callback, void* context )
//{
//    return EmulatorNative::GetIWatchdogDriver()->Enable( TimeoutMilliseconds );
//}
//
//void Watchdog_Disable()
//{
//    EmulatorNative::GetIWatchdogDriver()->Disable();
//}
//
//void Watchdog_ResetCpu()
//{
//    EmulatorNative::GetIWatchdogDriver()->ResetCpu();
//}
//
//void Watchdog_ResetCounter()
//{
//    EmulatorNative::GetIWatchdogDriver()->ResetCounter();
//}

HRESULT Watchdog_Enable(UINT32 TimeoutMilliseconds, WATCHDOG_INTERRUPT_CALLBACK isr, void* context)
{
	return CLR_E_FAIL;
}

void Watchdog_Disable()
{
}

void Watchdog_ResetCpu()
{
}

void Watchdog_ResetCounter()
{
}