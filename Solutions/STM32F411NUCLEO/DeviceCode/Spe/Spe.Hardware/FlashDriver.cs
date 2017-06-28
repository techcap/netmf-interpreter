using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;

namespace Spe.Hardware
{
    public class FlashDriver
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static internal int NativeRead(int startAddress, uint count, byte[] buffer);
        public static byte[] Read(int startAddress, uint count)
        {
            var buffer = new byte[count];

            NativeRead(startAddress, count, buffer);

            return buffer;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static internal int NativeWrite(int startAddress, uint count, byte[] buffer);
        public static void Write(int startAddress, byte[] buffer)
        {
            NativeWrite(startAddress, (uint)buffer.Length, buffer);
        }
    }
}
