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


#ifndef _SPE_HARDWARE_SPE_HARDWARE_NATIVEADC_H_
#define _SPE_HARDWARE_SPE_HARDWARE_NATIVEADC_H_

namespace Spe
{
    namespace Hardware
    {
        struct NativeADC
        {
            // Helper Functions to access fields of managed object
            static INT32& Get_channel( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_Spe_Hardware_Spe_Hardware_NativeADC::FIELD__channel ); }

            static float& Get_scale( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_float( pMngObj, Library_Spe_Hardware_Spe_Hardware_NativeADC::FIELD__scale ); }

            static float& Get_offset( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_float( pMngObj, Library_Spe_Hardware_Spe_Hardware_NativeADC::FIELD__offset ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static void NativeADCInitialize( CLR_RT_HeapBlock* pMngObj, INT32 param0, HRESULT &hr );
            static void NativeADCRead( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, CLR_RT_TypedArray_UINT16 param4, HRESULT &hr );
            static INT32 NativeADCRead( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, HRESULT &hr );
            static void NativeADCReadMinMax( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, CLR_RT_TypedArray_UINT16 param4, UINT16 * param5, UINT16 * param6, HRESULT &hr );
            static INT32 NativeADCReadSquareSum( CLR_RT_HeapBlock* pMngObj, INT32 param0, INT32 param1, INT32 param2, INT32 param3, CLR_RT_TypedArray_UINT32 param4, HRESULT &hr );
        };
    }
}
#endif  //_SPE_HARDWARE_SPE_HARDWARE_NATIVEADC_H_
