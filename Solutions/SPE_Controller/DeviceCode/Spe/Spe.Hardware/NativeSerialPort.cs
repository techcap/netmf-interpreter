using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;

namespace Spe.Hardware
{
    public class NativeSerialPort
    {
        private int baudRate;
        public int BaudRate { get { return baudRate; } }

        private string portName;
        public string PortName { get { return portName; } }

        private byte PortNumber
        {
            get
            {
                return byte.Parse(PortName.Substring(3));
            }
        }

        public NativeSerialPort(string portName, int baudRate)
        {
            this.portName = portName;
            this.baudRate = baudRate;
        }

        public void Open()
        {
            NativeSerialComm_Open(PortNumber, BaudRate);
        }

        public void Close()
        {
            NativeSerialComm_Close(PortNumber);
        }

        public virtual void Write(byte[] buffer, int offset, int count)
        {
            NativeSerialComm_Write(PortNumber, buffer, offset, count);
        }

        public virtual int Read(byte[] buffer, int offset, int count)
        {
            return NativeSerialComm_Read(PortNumber, buffer, offset, count);
        }

        public virtual int WriteAndRead(byte[] writeBuffer, int writeBufferOffset, int writeBufferCount, byte[] readBuffer, int readBufferOffset, int readBufferCount)
        {
            return NativeSerialComm_WriteAndRead(PortNumber, writeBuffer, writeBufferOffset, writeBufferCount, readBuffer, readBufferOffset, readBufferCount);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal void NativeSerialComm_Open(byte portNumber, int baudRate);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal void NativeSerialComm_Close(byte portNumber);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal void NativeSerialComm_Write(byte portNumber, byte[] writeBuffer, int offset, int count);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal int NativeSerialComm_Read(byte portNumber, byte[] readBuffer, int offset, int count);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern internal int NativeSerialComm_WriteAndRead(byte portNumber, byte[] writeBuffer, int writeBufferOffset, int writeBufferCount, byte[] readBuffer, int readBufferOffset, int readBufferCount);
    }
}
