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


#ifndef _SPE_HARDWARE_SPE_HARDWARE_NATIVERTC_H_
#define _SPE_HARDWARE_SPE_HARDWARE_NATIVERTC_H_

namespace Spe
{
    namespace Hardware
    {
        struct NativeRTC
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static INT8 get_IsInitialized( HRESULT &hr );
            static void Native_GetTime( INT32 * param0, INT32 * param1, INT32 * param2, INT32 * param3, INT32 * param4, INT32 * param5, HRESULT &hr );
            static void Native_SetTime( INT32 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, INT32 param5, HRESULT &hr );
            static INT8 Native_Initialize( UINT32 param0, UINT32 param1, HRESULT &hr );
            static void Native_Uninitialize( HRESULT &hr );
            static void Native_SetDayLightSaving( UINT32 param0, UINT32 param1, HRESULT &hr );
            static void Native_SetCoarseCalibration( UINT32 param0, UINT32 param1, HRESULT &hr );
            static void Native_SetCoarseCalibrationState( INT8 param0, HRESULT &hr );
            static void Native_SetSmoothCalibration( UINT32 param0, UINT32 param1, UINT32 param2, HRESULT &hr );
        };
    }
}
#endif  //_SPE_HARDWARE_SPE_HARDWARE_NATIVERTC_H_
