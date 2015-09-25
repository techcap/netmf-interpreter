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


#ifndef _SPE_HARDWARE_SPE_HARDWARE_NATIVESERIALPORT_H_
#define _SPE_HARDWARE_SPE_HARDWARE_NATIVESERIALPORT_H_

namespace Spe
{
    namespace Hardware
    {
        struct NativeSerialPort
        {
            // Helper Functions to access fields of managed object
            //static INT32& Get_baudRate( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_Spe_Hardware_Spe_Hardware_NativeSerialPort::FIELD__baudRate ); }

            //static LPCSTR& Get_portName( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_LPCSTR( pMngObj, Library_Spe_Hardware_Spe_Hardware_NativeSerialPort::FIELD__portName ); }

            // Declaration of stubs. These functions are implemented by Interop code developers
            static void NativeSerialComm_Open( CLR_RT_HeapBlock* pMngObj, UINT8 param0, INT32 param1, HRESULT &hr );
            static void NativeSerialComm_Close( CLR_RT_HeapBlock* pMngObj, UINT8 param0, HRESULT &hr );
            static void NativeSerialComm_Write( CLR_RT_HeapBlock* pMngObj, UINT8 param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, HRESULT &hr );
            static INT32 NativeSerialComm_Read( CLR_RT_HeapBlock* pMngObj, UINT8 param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, HRESULT &hr );
            static INT32 NativeSerialComm_WriteAndRead( CLR_RT_HeapBlock* pMngObj, UINT8 param0, CLR_RT_TypedArray_UINT8 param1, INT32 param2, INT32 param3, CLR_RT_TypedArray_UINT8 param4, INT32 param5, INT32 param6, HRESULT &hr );
        };
    }
}
#endif  //_SPE_HARDWARE_SPE_HARDWARE_NATIVESERIALPORT_H_
