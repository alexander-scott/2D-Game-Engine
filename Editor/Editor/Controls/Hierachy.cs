using GEPAA_Editor.EditorComponents;
using GEPAA_Editor.Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace GEPAA_Editor.EditorControls
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

        private ListView _listView;
        private ContextMenuStrip _menu; 

        private Inspector _inspector;

        private Scene _scene;

        private IntPtr _sceneManager;
        private string _resourcesPath;

        public Hierachy(Inspector inspector,string resourcesPath)
        {
            _inspector = inspector;
            _resourcesPath = resourcesPath;
        }

        public void SetScene(Scene scene)
        {
            _scene = scene;
        }

        public void InitaliseControls(ListView lv, ContextMenuStrip menu)
        {
            _listView = lv;
            _menu = menu;

            _listView.DisableSelect();
            _listView.Scrollable = true;
            _listView.View = View.Details;
            _listView.Columns.Add(new ColumnHeader
            {
                Text = "Hierarchy",
                Name = "Hierarchy",
                Width = 100
            });
            ImageList list = new ImageList();
            list.Images.Add("ClosedTriangle", Image.FromFile(@"" + _resourcesPath + "\\Editor\\ClosedTriangle.bmp"));
            list.Images.Add("OpenTriangle", Image.FromFile(@"" + _resourcesPath + "\\Editor\\OpenTriangle.bmp"));

            _listView.SmallImageList = list;
            _listView.FullRowSelect = true;
            _listView.HeaderStyle = ColumnHeaderStyle.None;

            _listView.MouseDoubleClick += ItemDoubleClicked;
            _listView.MouseDown += HierarchyClicked;
            _listView.SelectedIndexChanged += HierarchyItemSelected;

            _listView.AfterLabelEdit += GameObjectRenamed;

            _listView.DragDrop += _listView_DragDrop;
            _listView.DragOver += _listView_DragOver;
            _listView.ItemDrag += _listView_ItemDrag;

            _menu.Items[0].Click += NewGameObjectClicked;
            _menu.Items[1].Click += RenameClicked;
            _menu.Items[2].Click += DeleteClicked;
            _menu.MouseLeave += MenuLeft;
        }

        private void _listView_ItemDrag(object sender, ItemDragEventArgs e)
        {
            _listView.DoDragDrop(e.Item, DragDropEffects.All);
        }

        private void _listView_DragOver(object sender, DragEventArgs e)
        {
            if ((e.KeyState & 8) == 8)
                e.Effect = DragDropEffects.Copy;
            else
                e.Effect = DragDropEffects.Move;
        }

        private void _listView_DragDrop(object sender, DragEventArgs e)
        {
            if (_listView.SelectedItems.Count == 0) { return; }
            Point p = _listView.PointToClient(new Point(e.X, e.Y));
            ListViewItem item = _listView.GetItemAt(p.X, p.Y);
            if (item == null) { return; }
        }

        private void DeleteClicked(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void MenuLeft(object sender, EventArgs e)
        {
            _menu.Close();
        }

        private void GameObjectRenamed(object sender, LabelEditEventArgs e)
        {
            if (e.Label != null)
            {
                _scene.HasChanged = true;
                SceneInterface.RenameGameObject(_sceneManager, (ulong)hierarchyItems[_listView.FocusedItem.Index].GameObjectID, e.Label);
            }
        }

        private void RenameClicked(object sender, EventArgs e)
        {
            _listView.FocusedItem.BeginEdit();
        }

        private void NewGameObjectClicked(object sender, EventArgs e)
        {
            IntPtr sceneItem = SceneInterface.CreateGameObject(_sceneManager);
            IntPtr data = new IntPtr(sceneItem.ToInt64());
            SceneItem hItem = (SceneItem)Marshal.PtrToStructure(data, typeof(SceneItem));

            displayedHierarchyIDs.Add(hierarchyItems.Count);

            HItem item = new HItem(hItem.GameObjectName, (int)hItem.GameObjectID, (int)hItem.ComponentCount);
            item.ChildDepthLevel = 0;
            hierarchyItems.Add(hierarchyItems.Count, item);

            ListViewItem lvItem = new ListViewItem(hierarchyItems[displayedHierarchyIDs[hierarchyItems.Count - 1]].GameObjectName);
            _listView.Items.Add(lvItem);
            lvItem.Focused = true;

            SceneInterface.FreeMemory(sceneItem);
            _scene.HasChanged = true;

            _listView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            RenameClicked(null, null);
        }

        private void HierarchyClicked(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (_listView.FocusedItem != null && _listView.FocusedItem.Bounds.Contains(e.Location) == true)
                {
                    _menu.Items[1].Enabled = true;
                    _menu.Items[2].Enabled = true;
                } 
                else
                {
                    _menu.Items[1].Enabled = false;
                    _menu.Items[2].Enabled = false;
                } 

                _menu.Show(Cursor.Position);
            }
        }

        private void HierarchyItemSelected(object sender, EventArgs e)
        {
            if (_listView.SelectedIndices.Count > 0)
            {
                int index = _listView.SelectedIndices[0];
                _inspector.GameObjectClicked(_sceneManager, hierarchyItems[index].GameObjectID, hierarchyItems[index].ComponentCount);
            }
            else
            {
                _inspector.ClearInspector();
            }
        }

        private void ItemDoubleClicked(object sender, MouseEventArgs e)
        {
            HItem selectedItem = hierarchyItems[displayedHierarchyIDs[_listView.FocusedItem.Index]];

            // If the item has children
            if (selectedItem.HierarchyChildren.Count != 0)
            {
                if (!selectedItem.Expanded) // If not expanded we will need to make visible
                {
                    // First of all switch the icon around on this item
                    int removeIndex = _listView.FocusedItem.Index;
                    _listView.Items.RemoveAt(removeIndex);

                    ListViewItem newItem = new ListViewItem(selectedItem.GameObjectName);
                    newItem.IndentCount = selectedItem.ChildDepthLevel;
                    newItem.ImageIndex = 1;
                    _listView.Items.Insert(removeIndex, newItem);

                    for (int i = 0; i < selectedItem.HierarchyChildren.Count; i++)
                    {
                        ListViewItem newChildItem = new ListViewItem(selectedItem.HierarchyChildren[i].GameObjectName);
                        newChildItem.IndentCount = selectedItem.HierarchyChildren[i].ChildDepthLevel;

                        if (selectedItem.HierarchyChildren[i].HierarchyChildren.Count != 0) // If the child has children add icon
                            newChildItem.ImageIndex = 0;
  
                        _listView.Items.Insert(removeIndex + 1, (newChildItem));
                        displayedHierarchyIDs.Insert(removeIndex + 1, removeIndex + 1 + i);
                    }
                }
                else
                {
                    // First of all switch the icon around on this item
                    int removeIndex = _listView.FocusedItem.Index;
                    _listView.Items.RemoveAt(removeIndex);

                    ListViewItem newItem = new ListViewItem(selectedItem.GameObjectName);
                    newItem.IndentCount = selectedItem.ChildDepthLevel;
                    newItem.ImageIndex = 0;
                    _listView.Items.Insert(removeIndex, newItem);

                    // Remove each child from the displayed hierarchy
                    for (int i = selectedItem.HierarchyChildren.Count; i > 0; i--)
                    {
                        _listView.Items.RemoveAt(removeIndex + i);
                        displayedHierarchyIDs.RemoveAt(removeIndex + i);
                    }
                }

                selectedItem.Expanded = !selectedItem.Expanded;
            }
        }

        public void CreateHierachyList(IntPtr sceneManager)
        {
            _sceneManager = sceneManager;

            int numberOfGameObjects = SceneInterface.GetGameObjectCount(sceneManager);
            IntPtr hierarchy = SceneInterface.PopulateHierarchyItems(sceneManager, numberOfGameObjects);
            int structSize = Marshal.SizeOf(typeof(SceneItem));

            hierarchyItems.Clear();
            displayedHierarchyIDs.Clear();

            _listView.Items.Clear();

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
                    _listView.Items.Add(new ListViewItem(hierarchyItems[displayedHierarchyIDs[i]].GameObjectName));
                }
                else // If this icon has children display with an expand icon
                {
                    _listView.Items.Add(new ListViewItem(hierarchyItems[displayedHierarchyIDs[i]].GameObjectName, 0));
                }   
            }

            SceneInterface.FreeMemory(hierarchy);

            _listView.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
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
