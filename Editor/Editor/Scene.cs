using SimpleSampleEditor.EditorComponents;
using SimpleSampleEditor.EditorHierachy;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace SimpleSampleEditor
{
    class Scene
    {
        public string Name;
        public string FilePath;

        public bool HasChanged = false;
        public bool HasSavedOnce = false;
    }
}
