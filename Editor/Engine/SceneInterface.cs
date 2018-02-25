using System;
using System.Runtime.InteropServices;

namespace SimpleSampleEditor.Engine
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct HierarchyItem
    {
        public uint GameObjectID;
        public uint GameObjectParentID;
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string GameObjectName;
    };

    class SceneInterface
    {
        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetGameObjectCount(IntPtr window);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PopulateHierarchyItems(IntPtr window, int itemCount);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeHierarchyMemory(IntPtr hierarchy);
    }
}
