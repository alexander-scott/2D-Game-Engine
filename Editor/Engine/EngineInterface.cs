using System;
using System.Runtime.InteropServices;

namespace SimpleSampleEditor.Engine
{
    class EngineInterface
    {
        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr InitaliseEngine(IntPtr window, int Width, int Height, string filePath);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartEngineLoop(IntPtr gamePtr);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LoadNewScene(IntPtr gamePtr, string filePath);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PlayStarted(IntPtr gamePtr);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PlayStopped(IntPtr gamePtr);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanD3D(IntPtr gamePtr);

        #region Input

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LeftMouseClick(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LeftMouseRelease(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RightMouseClick(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RightMouseRelease(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseMove(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyDown(IntPtr gamePtr, int keyCode);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyUp(IntPtr gamePtr, int keyCode);

        #endregion

    }
}
