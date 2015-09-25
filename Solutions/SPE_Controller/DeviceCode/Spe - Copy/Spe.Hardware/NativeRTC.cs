using System;
using System.Threading;
using System.Runtime.CompilerServices;

namespace Spe.Hardware
{
    public static class NativeRTC
    {
        public enum RTC_CalibSign : uint
        {
            Positive = 0x00000000,
            Negative = 0x00000080
        }

        public enum RTC_SmoothCalibPeriod : uint
        {
            Short = 0x00004000,
            Medium = 0x00002000,
            Long = 0x00000000
        }

        public enum RTC_SmoothCalibPlusPulses : uint
        {
            Set = 0x00008000,
            Reset = 0x00000000
        }

        public enum RTC_DayLightSaving : uint
        {
            AddOneHour = 0x00020000,
            SubstractOneHour = 0x00010000
        }

        public enum RTC_StoreOperation : uint
        {
            Set = 0x00040000,
            Reset = 0x00000000
        }

        public enum RTC_CLKSource : uint
        {
            LSE = 0x00000100,
            LSI = 0x00000200,
            HSE = 0x00190300
            //HSE_Div2 = 0x00020300,
            //HSE_Div3 = 0x00030300,
            //HSE_Div4 = 0x00040300,
            //HSE_Div5 = 0x00050300,
            //HSE_Div6 = 0x00060300,
            //HSE_Div7 = 0x00070300,
            //HSE_Div8 = 0x00080300,
            //HSE_Div9 = 0x00090300,
            //HSE_Div10 = 0x000A0300,
            //HSE_Div11 = 0x000B0300,
            //HSE_Div12 = 0x000C0300,
            //HSE_Div13 = 0x000D0300,
            //HSE_Div14 = 0x000E0300,
            //HSE_Div15 = 0x000F0300,
            //HSE_Div16 = 0x00100300,
            //HSE_Div17 = 0x00110300,
            //HSE_Div18 = 0x00120300,
            //HSE_Div19 = 0x00130300,
            //HSE_Div20 = 0x00140300,
            //HSE_Div21 = 0x00150300,
            //HSE_Div22 = 0x00160300,
            //HSE_Div23 = 0x00170300,
            //HSE_Div24 = 0x00180300,
            //HSE_Div25 = 0x00190300,
            //HSE_Div26 = 0x001A0300,
            //HSE_Div27 = 0x001B0300,
            //HSE_Div28 = 0x001C0300,
            //HSE_Div29 = 0x001D0300,
            //HSE_Div30 = 0x001E0300,
            //HSE_Div31 = 0x001F0300
        }

        public static DateTime DateTime
        {
            set
            {
                Native_SetTime(value.Year, value.Month, value.Day, value.Hour, value.Minute, value.Second);
            }
            get
            {
                Int32 _Int32_Year = 2000, _Int32_Month = 1, _Int32_Day = 1, _Int32_Hour = 0, _Int32_Minute = 0, _Int32_Second = 0;

                Native_GetTime(ref _Int32_Year, ref _Int32_Month, ref _Int32_Day, ref _Int32_Hour, ref _Int32_Minute, ref _Int32_Second);

                return new DateTime(_Int32_Year, _Int32_Month, _Int32_Day, _Int32_Hour, _Int32_Minute, _Int32_Second);
            }
        }

        public static bool Initialize(RTC_CLKSource source, UInt32 timeout)
        {
            return Native_Initialize(source, timeout);
        }

        public static void Uninitialize()
        {
            Native_Uninitialize();
        }

        public static void SetDayLinghtSaving(RTC_DayLightSaving dayLightSaving, RTC_StoreOperation storeOperation)
        {
            Native_SetDayLightSaving(dayLightSaving, storeOperation);
        }

        public static void SetCoarseCalibration(RTC_CalibSign calibSign, UInt32 value)
        {
            Native_SetCoarseCalibration(calibSign, value);
        }

        public static void SetCoarseCalibrationState(bool state)
        {
            Native_SetCoarseCalibrationState(state);
        }

        public static void SetSmoothCalibration(RTC_SmoothCalibPeriod smoothCalibPeriod, RTC_SmoothCalibPlusPulses smoothCalibPlusPulses, UInt32 smouthCalibMinusPulsesValue)
        {
            Native_SetSmoothCalibration(smoothCalibPeriod, smoothCalibPlusPulses, smouthCalibMinusPulsesValue);
        }

        extern public static bool IsInitialized
        {
            [MethodImplAttribute(MethodImplOptions.InternalCall)]
            get;
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_GetTime(ref Int32 year, ref Int32 month, ref Int32 day, ref Int32 hour, ref Int32 minute, ref Int32 second);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_SetTime(Int32 year, Int32 month, Int32 day, Int32 hour, Int32 minute, Int32 second);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal bool Native_Initialize(RTC_CLKSource source, UInt32 timeout);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_Uninitialize();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_SetDayLightSaving(RTC_DayLightSaving dayLightSaving, RTC_StoreOperation storeOperation);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_SetCoarseCalibration(RTC_CalibSign calibSign, UInt32 value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_SetCoarseCalibrationState(bool state);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static internal void Native_SetSmoothCalibration(RTC_SmoothCalibPeriod smoothCalibPeriod, RTC_SmoothCalibPlusPulses smoothCalibPlusPulses, UInt32 smouthCalibMinusPulsesValue);
    }
}
