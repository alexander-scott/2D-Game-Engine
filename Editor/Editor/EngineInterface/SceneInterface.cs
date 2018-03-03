using System;
using System.Runtime.InteropServices;

namespace GEPAA_Editor.Engine
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SceneItem
    {
        public uint GameObjectID;
        public uint GameObjectParentID;
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string GameObjectName;
        public uint ComponentCount;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct InspectorField
    {
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string FieldName;
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string FieldValue;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct InspectorComponent
    {
        public InspectorField[] Fields;
        public uint FieldCount;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Inspector
    {
        public InspectorComponent[] Components;
        public uint ComponentCount;
    };

    class SceneInterface
    {
        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetGameObjectCount(IntPtr sceneManagerPtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PopulateHierarchyItems(IntPtr sceneManagerPtr, int itemCount);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PopulateInspector(IntPtr sceneManagerPtr, ulong gameObjectID);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeMemory(IntPtr ptr);
    }
}
