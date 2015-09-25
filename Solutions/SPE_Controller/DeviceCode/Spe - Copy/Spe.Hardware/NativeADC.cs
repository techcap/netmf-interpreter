using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;
using Microsoft.SPOT.Hardware;

namespace Spe.Hardware
{
    public class NativeADC
    {
        public static int AveragecountPerSample = 10;

        private const int RAW_DATA_RANGE = 4096;

        private int channel;
        public Cpu.AnalogChannel Channel
        {
            get
            {
                return (Cpu.AnalogChannel)channel;
            }
        }

        public int Precision
        {
            get
            {
                return 12;
            }
        }

        private float scale = 1;
        public float Scale
        {
            get { return scale; }
            set { scale = value; }
        }

        private float offset;
        public float Offset
        {
            get { return offset; }
            set { offset = value; }
        }

        public NativeADC(Cpu.AnalogChannel channel)
        {
            this.channel = (int)channel;

            NativeADCInitialize(this.channel);
        }

        public float Read()
        {
            return GetValue(NativeADCRead(this.channel, AveragecountPerSample));
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="count"></param>
        /// <param name="samplingInterval">microsecons, multiple of AverageCountPerSample</param>
        /// <returns></returns>
        public float[] Read(int count, int samplingInterval)
        {
            ushort[] readBuffer = ReadRaw(count, samplingInterval);

            float[] values = new float[count];
            for (int i = 0; i < count; i++)
            {
                values[i] = GetValue(readBuffer[i]);
            }

            return values;
        }

        public int ReadRaw()
        {
            return NativeADCRead((int)Channel, AveragecountPerSample);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="count"></param>
        /// <param name="samplingInterval">microsecons, multiple of AverageCountPerSample</param>
        /// <returns></returns>
        public ushort[] ReadRaw(int count, int samplingInterval)
        {
            ushort[] readBuffer = new ushort[count];
            NativeADCRead(channel, count, samplingInterval, AveragecountPerSample, readBuffer);

            ushort[] result = new ushort[count];
            for (int i = 0; i < count; i++)
            {
                result[i] = (ushort)readBuffer[i];
            }

            return result;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="count"></param>
        /// <param name="samplingInterval">microsecons, multiple of AverageCountPerSample</param>
        /// <param name="max"></param>
        /// <param name="min"></param>
        public void ReadRawMinMax(int count, int samplingInterval, out ushort min, out ushort max)
        {
            ushort[] readBuffer = new ushort[count];
            NativeADCReadMinMax(channel, count, samplingInterval, AveragecountPerSample, readBuffer, out min, out max);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="count"></param>
        /// <param name="samplingInterval">microsecons, multiple of AverageCountPerSample</param>
        /// <param name="max"></param>
        /// <param name="min"></param>
        public void ReadMinMax(int count, int samplingInterval, out float min, out float max)
        {
            ushort _min;
            ushort _max;

            ushort[] readBuffer = new ushort[count];
            NativeADCReadMinMax((int)Channel, count, samplingInterval, AveragecountPerSample, readBuffer, out _min, out _max);

            min = GetValue(_min);
            max = GetValue(_max);
        }

        public int ReadRawRMS(int count, int samplingInterval)
        {
            UInt32[] readBuffer = new UInt32[count];
            int squareSum = NativeADCReadSquareSum((int)Channel, count, samplingInterval, AveragecountPerSample, readBuffer);
            return (int)System.Math.Sqrt(squareSum / count);
        }

        public float ReadRMS(int count, int samplingInterval)
        {
            int rmsRaw = ReadRawRMS(count, samplingInterval);
            return rmsRaw * Scale / (float)RAW_DATA_RANGE;
        }

        private float GetValue(int rawValue)
        {
            return rawValue * Scale / (float)RAW_DATA_RANGE + Offset;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal void NativeADCInitialize(int pin);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal void NativeADCRead(int pin, int count, int samplingInterval, int averageCount, ushort[] readBuffer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal int NativeADCRead(int pin, int averageCount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal void NativeADCReadMinMax(int pin, int count, int samplingInterval, int averageCount, ushort[] readBuffer, out ushort min, out ushort max);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal int NativeADCReadSquareSum(int pin, int count, int samplingInterval, int averageCount, UInt32[] readBuffer);
    }
}
