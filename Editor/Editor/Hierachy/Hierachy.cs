using SimpleSampleEditor.EditorComponents;
using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SimpleSampleEditor.EditorHierachy
{
    public class HItem
    {
        public string GameObjectName;
        public int GameObjectID;
        public int ComponentCount;
        public HItem HierarchyParent;
        public List<HItem> HierarchyChildren;

        public bool Expanded;

        public int ChildDepthLevel;

        public HItem(string name,int gameObjectID, int componentCount)
        {
            GameObjectName = name;
            GameObjectID = gameObjectID;
            ComponentCount = componentCount;
            HierarchyChildren = new List<HItem>();

            Expanded = false;
        }
    };

    public class Hierachy
    {
        private Dictionary<int, HItem> hierarchyItems = new Dictionary<int, HItem>();
        private List<int> displayedHierarchyIDs = new List<int>();

        private ListView listView;

        public Hierachy(ListView lv, string resourcesPath)
        {
            listView = lv;

            listView.DisableSelect();
            listView.Scrollable = true;
            listView.View = View.Details;
            listView.Columns.Add(new ColumnHeader
            {
                Text = "Hierarchy",
                Name = "Hierarchy",
                Width = 100
            });
            ImageList list = new ImageList();
            list.Images.Add("ClosedTriangle", Image.FromFile(@"" + resourcesPath + "\\Editor\\ClosedTriangle.bmp"));
            list.Images.Add("OpenTriangle", Image.FromFile(@"" + resourcesPath + "\\Editor\\OpenTriangle.bmp"));

            listView.SmallImageList = list;
            listView.FullRowSelect = true;

            listView.MouseDoubleClick += ItemDoubleClicked;
            listView.MouseClick += ListView_MouseClick;
        }

        private void ListView_MouseClick(object sender, MouseEventArgs e)
        {
            // Load up hierarchy item in inspector
        }

        private void ItemDoubleClicked(object sender, MouseEventArgs e)
        {
            HItem selectedItem = hierarchyItems[displayedHierarchyIDs[listView.FocusedItem.Index]];

            // If the item has children
            if (selectedItem.HierarchyChildren.Count != 0)
            {
                if (!selectedItem.Expanded) // If not expanded we will need to make visible
                {
                    // First of all switch the icon around on this item
                    int removeIndex = listView.FocusedItem.Index;
                    listView.Items.RemoveAt(removeIndex);

                    ListViewItem newItem = new ListViewItem(selectedItem.GameObjectName);
                    newItem.IndentCount = selectedItem.ChildDepthLevel;
                    newItem.ImageIndex = 1;
                    listView.Items.Insert(removeIndex, newItem);

                    for (int i = 0; i < selectedItem.HierarchyChildren.Count; i++)
                    {
                        ListViewItem newChildItem = new ListViewItem(selectedItem.HierarchyChildren[i].GameObjectName);
                        newChildItem.IndentCount = selectedItem.HierarchyChildren[i].ChildDepthLevel;

                        if (selectedItem.HierarchyChildren[i].HierarchyChildren.Count != 0) // If the child has children add icon
                            newChildItem.ImageIndex = 0;
  
                        listView.Items.Insert(removeIndex + 1, (newChildItem));
                        displayedHierarchyIDs.Insert(removeIndex + 1, removeIndex + 1 + i);
                    }
                }
                else
                {
                    // First of all switch the icon around on this item
                    int removeIndex = listView.FocusedItem.Index;
                    listView.Items.RemoveAt(removeIndex);

                    ListViewItem newItem = new ListViewItem(selectedItem.GameObjectName);
                    newItem.IndentCount = selectedItem.ChildDepthLevel;
                    newItem.ImageIndex = 0;
                    listView.Items.Insert(removeIndex, newItem);

                    // Remove each child from the displayed hierarchy
                    for (int i = selectedItem.HierarchyChildren.Count; i > 0; i--)
                    {
                        listView.Items.RemoveAt(removeIndex + i);
                        displayedHierarchyIDs.RemoveAt(removeIndex + i);
                    }
                }

                selectedItem.Expanded = !selectedItem.Expanded;
            }
        }

        public void CreateHierachyList(IntPtr engine)
        {
            int numberOfGameObjects = SceneInterface.GetGameObjectCount(engine);
            IntPtr hierarchy = SceneInterface.PopulateHierarchyItems(engine, numberOfGameObjects);
            int structSize = Marshal.SizeOf(typeof(SceneItem));

            hierarchyItems.Clear();
            displayedHierarchyIDs.Clear();

            listView.Items.Clear();

            for (int i = 0; i < numberOfGameObjects; i++)
            {
                // Parse the data recieved from the engine
                IntPtr data = new IntPtr(hierarchy.ToInt64() + structSize * i);
                SceneItem hItem = (SceneItem)Marshal.PtrToStructure(data, typeof(SceneItem));

                // Create the item that will be stored in the hierarchy
                HItem item = new HItem(hItem.GameObjectName, (int)hItem.GameObjectID, (int)hItem.ComponentCount);

                // Check if the item has a parent
                HItem itemParent = FindParent((int)hItem.GameObjectParentID);
                if (itemParent != null)
                {
                    // If the item has a parent, setup the parent and child data
                    item.HierarchyParent = itemParent;
                    itemParent.HierarchyChildren.Add(item);
                }
                else // Else add it's index to be rendered in the list
                {
                    displayedHierarchyIDs.Add(i);
                }

                // Cache the item
                hierarchyItems.Add(i, item);
            }

            // Determine every items depth
            for (int i = 0; i < hierarchyItems.Count; i++)
            {
                int depth = 0;
                FindChildDepth(ref depth, hierarchyItems[i]);
                hierarchyItems[i].ChildDepthLevel = depth;
            }

            // Add the items that are visible to the actual listview
            for (int i = 0; i < displayedHierarchyIDs.Count; i++)
            {
                // If this item does not have any children display without an expand icon
                if (hierarchyItems[displayedHierarchyIDs[i]].HierarchyChildren.Count == 0)
                {
                    listView.Items.Add(new ListViewItem(hierarchyItems[displayedHierarchyIDs[i]].GameObjectName));
                }
                else // If this icon has children display with an expand icon
                {
                    listView.Items.Add(new ListViewItem(hierarchyItems[displayedHierarchyIDs[i]].GameObjectName, 0));
                }   
            }

            SceneInterface.FreeMemory(hierarchy);
        }

        private HItem FindParent(int parentID)
        {
            for (int i = 0; i < hierarchyItems.Count; i++)
            {
                if (hierarchyItems[i].GameObjectID == parentID)
                {
                    return hierarchyItems[i];
                }
            }

            return null;
        }

        private void FindChildDepth(ref int depth, HItem parent)
        {
            if (parent.HierarchyParent != null)
            {
                depth++;
                FindChildDepth(ref depth, parent.HierarchyParent);
            }
        }
    }
}
