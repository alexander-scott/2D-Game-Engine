using GEPAA_Editor.Engine;
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace GEPAA_Editor.EditorControls
{
    public class Inspector
    {
        private ListView _listView;

        public Inspector(ListView lv)
        {
            _listView = lv;
        }

        public void GameObjectClicked(IntPtr sceneManager, int id, int componentCount)
        {
            // First work out how many fields each component has
            IntPtr fieldCountPtr = SceneInterface.GetComponentFieldCounts(sceneManager, (ulong)id);
            int intSize = sizeof(int);

            int[] fieldCount = new int[componentCount];
            for (int i = 0; i < componentCount; i++)
            {
                IntPtr data = new IntPtr(fieldCountPtr.ToInt64() + intSize * i);
                fieldCount[i] = (int)Marshal.PtrToStructure(data, typeof(int));
            }

            for (int i = 0; i < componentCount; i++)
            {
                IntPtr fieldsPtr = SceneInterface.PopulateInspector(sceneManager, (ulong)id, i);
                int structSize = Marshal.SizeOf(typeof(InspectorField));

                // Parse the data recieved from the engine
                IntPtr data = new IntPtr(fieldsPtr.ToInt64() + structSize * i);
                InspectorField field = (InspectorField)Marshal.PtrToStructure(data, typeof(InspectorField));
            }
        }
    }
}
