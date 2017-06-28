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


#ifndef _SPE_HARDWARE_SPE_HARDWARE_FLASHDRIVER_H_
#define _SPE_HARDWARE_SPE_HARDWARE_FLASHDRIVER_H_

namespace Spe
{
    namespace Hardware
    {
        struct FlashDriver
        {
            // Helper Functions to access fields of managed object
            // Declaration of stubs. These functions are implemented by Interop code developers
            static INT32 NativeRead( INT32 param0, UINT32 param1, CLR_RT_TypedArray_UINT8 param2, HRESULT &hr );
            static INT32 NativeWrite( INT32 param0, UINT32 param1, CLR_RT_TypedArray_UINT8 param2, HRESULT &hr );
        };
    }
}
#endif  //_SPE_HARDWARE_SPE_HARDWARE_FLASHDRIVER_H_
