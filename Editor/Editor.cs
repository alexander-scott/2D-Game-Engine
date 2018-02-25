using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using SimpleSampleEditor.EditorHierachy;
using SimpleSampleEditor.EditorComponents;
using System.IO;
using System.Reflection;

namespace SimpleSampleEditor
{
    public partial class Editor : Form
    {
        private string mResoucesPath;

        /// <summary>
        /// Pointer to the instance of the Engine. Used to make sure all calls to the engine use the same instance of the Game
        /// </summary>
        private IntPtr mEngine;

        private IntPtr _editorSystem;

        private Hierachy mHierachy;

        private bool mPlaying = false;

        public Editor()
        {
            InitializeComponent();
            this.FormClosing += this.EditorClosing;
            this.Shown += this.EditorLoaded;

            panel1.MouseDown += new MouseEventHandler(PanelMouseDown);
            panel1.MouseUp += new MouseEventHandler(PanelMouseRelease);
            panel1.MouseMove += new MouseEventHandler(PanelMouseMove);
            this.Controls.Add(this.panel1);

            mResoucesPath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\..\..\Resources"));

            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(KeyboardKeyDown);
            this.KeyUp += new KeyEventHandler(KeyboardKeyUp);

            btnPlay.DisableSelect();
            btnPlay.MouseClick += PlayClicked;

            hierarchyListBox.DisableSelect();
            hierarchyListBox.Scrollable = true;
            hierarchyListBox.View = View.Details;
            hierarchyListBox.Columns.Add(new ColumnHeader
            {
                Text = "Hierarchy",
                Name = "Hierarchy",
                Width = 100
            });
            ImageList list = new ImageList();
            list.Images.Add("ClosedTriangle", Image.FromFile(@"" + mResoucesPath + "\\Editor\\ClosedTriangle.bmp"));
            list.Images.Add("OpenTriangle", Image.FromFile(@"" + mResoucesPath + "\\Editor\\OpenTriangle.bmp"));
            
            hierarchyListBox.SmallImageList = list;
            hierarchyListBox.FullRowSelect = true;

            mHierachy = new Hierachy(hierarchyListBox);
        }

        private void PlayClicked(object sender, MouseEventArgs e)
        {
            if (!mPlaying)
            {
                mPlaying = true;
                EngineInterface.PlayStarted(mEngine);
                mHierachy.CreateHierachyList(mEngine); // Update hierarchy
            }
            else
            {
                mPlaying = false;
                EngineInterface.PlayStopped(mEngine);
                mHierachy.CreateHierachyList(mEngine); // Update hierarchy
            }
        }

        private void EditorLoading(object sender, EventArgs e)
        {
            mEngine = EngineInterface.InitaliseEngine(panel1.Handle);
            panel1.Focus();
        }

        private void EditorLoaded(object sender, EventArgs e)
        {
            mHierachy.CreateHierachyList(mEngine);

            //EngineInterface.StartUpdateLoop(mEngine);  
        }

        private void EditorClosing(object sender, FormClosingEventArgs e)
        {
            EngineInterface.CleanD3D(mEngine);
        }

        #region Basic Input

        private void PanelMouseDown(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);

            if (e.Button == MouseButtons.Left)
                EngineInterface.LeftMouseClick(mEngine, point.X, point.Y);
            else
                EngineInterface.RightMouseClick(mEngine, point.X, point.Y);
        }

        private void PanelMouseRelease(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);

            if (e.Button == MouseButtons.Left)
                EngineInterface.LeftMouseRelease(mEngine, point.X, point.Y);
            else
                EngineInterface.RightMouseRelease(mEngine, point.X, point.Y);
        }

        private void PanelMouseMove(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
            EngineInterface.MouseMove(mEngine, point.X, point.Y);
        }

        private void KeyboardKeyUp(object sender, KeyEventArgs e)
        {
            EngineInterface.KeyUp(mEngine, e.KeyValue);
        }

        private void KeyboardKeyDown(object sender, KeyEventArgs e)
        {
            EngineInterface.KeyDown(mEngine, e.KeyValue);
        }

        #endregion

        private void LoadSceneClicked(object sender, EventArgs e)
        {
            OpenFileDialog theDialog = new OpenFileDialog
            {
                Title = "Open Scene",
                Filter = "XML files|*.xml"
            };
            if (theDialog.ShowDialog() == DialogResult.OK)
            {
                EngineInterface.LoadNewScene(mEngine, theDialog.FileName);
                mHierachy.CreateHierachyList(mEngine);
            }
        }

        private void NewSceneClicked(object sender, EventArgs e)
        {

        }

        private void SaveSceneClicked(object sender, EventArgs e)
        {
            SaveFileDialog theDialog = new SaveFileDialog
            {
                Title = "Save Scene",
                Filter = "XML files|*.xml"
            };
            if (theDialog.ShowDialog() == DialogResult.OK)
            {

            }
        }
    }
}
