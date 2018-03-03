using GEPAA_Editor.Engine;
using System;
using System.Drawing;
using System.Windows.Forms;

using GEPAA_Editor.EditorControls;
using GEPAA_Editor.EditorComponents;
using System.IO;
using System.Reflection;

namespace GEPAA_Editor
{
    public partial class Editor : Form
    {
        private IntPtr _engine;
        private IntPtr _editorSystem;
        private IntPtr _sceneManagerSystem;

        private Scene _scene;

        // Controls
        private Hierachy _hierarchy;
        private EditorControls.Inspector _inspector;

        private bool mPlaying = false;
        private string _resoucesPath;

        #region Consts

        private const string EDITOR_TITLE_PREFIX = "GEPAA - ";

        #endregion

        #region Initilisation

        public Editor()
        {
            InitializeComponent();

            _resoucesPath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), @"..\..\..\..\Resources"));

            InitaliseCallbacks();
            InitaliseControls();

            _scene = new Scene();
            this.Text = EDITOR_TITLE_PREFIX + "Untilted";
        }

        private void InitaliseCallbacks()
        {
            this.FormClosing += this.EditorClosing;
            this.Shown += this.EditorLoaded;

            panel1.MouseDown += new MouseEventHandler(PanelMouseDown);
            panel1.MouseUp += new MouseEventHandler(PanelMouseRelease);
            panel1.MouseMove += new MouseEventHandler(PanelMouseMove);
            this.Controls.Add(this.panel1);

            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(KeyboardKeyDown);
            this.KeyUp += new KeyEventHandler(KeyboardKeyUp);
        }

        private void InitaliseControls()
        {
            btnPlay.DisableSelect();
            btnPlay.MouseClick += PlayClicked;

            _inspector = new Inspector(dgvInspector);
            _hierarchy = new Hierachy(hierarchyListBox, _inspector, _resoucesPath);
        }

        #endregion

        #region Editor load/close callbacks

        private void EditorLoading(object sender, EventArgs e)
        {
            _engine = EngineInterface.InitaliseEngine(panel1.Handle);

            _editorSystem = EngineInterface.GetEditorSystem(_engine);
            _sceneManagerSystem = EngineInterface.GetSceneManagerSystem(_engine);

            panel1.Focus();
        }

        private void EditorLoaded(object sender, EventArgs e)
        {
            _hierarchy.CreateHierachyList(_sceneManagerSystem);
            EngineInterface.StartUpdateLoop(_engine);
        }

        private void EditorClosing(object sender, FormClosingEventArgs e)
        {
            EngineInterface.CleanD3D(_engine);
        }

        #endregion

        private void PlayClicked(object sender, MouseEventArgs e)
        {
            if (!mPlaying)
            {
                mPlaying = true;
                btnPlay.Text = "STOP";
                this.BackColor = Color.AliceBlue;
                EngineInterface.PlayStarted(_editorSystem);
                _hierarchy.CreateHierachyList(_sceneManagerSystem);
            }
            else
            {
                mPlaying = false;
                btnPlay.Text = "PLAY";
                this.BackColor = Color.WhiteSmoke;
                EngineInterface.PlayStopped(_editorSystem);
                _hierarchy.CreateHierachyList(_sceneManagerSystem);
            }
        }


        #region Basic Input

        private void PanelMouseDown(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);

            if (e.Button == MouseButtons.Left)
                EngineInterface.LeftMouseClick(_editorSystem, point.X, point.Y);
            else
                EngineInterface.RightMouseClick(_editorSystem, point.X, point.Y);
        }

        private void PanelMouseRelease(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);

            if (e.Button == MouseButtons.Left)
                EngineInterface.LeftMouseRelease(_editorSystem, point.X, point.Y);
            else
                EngineInterface.RightMouseRelease(_editorSystem, point.X, point.Y);
        }

        private void PanelMouseMove(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
            EngineInterface.MouseMove(_editorSystem, point.X, point.Y);
        }

        private void KeyboardKeyUp(object sender, KeyEventArgs e)
        {
            EngineInterface.KeyUp(_editorSystem, e.KeyValue);
        }

        private void KeyboardKeyDown(object sender, KeyEventArgs e)
        {
            EngineInterface.KeyDown(_editorSystem, e.KeyValue);
        }

        #endregion

        private void LoadSceneClicked(object sender, EventArgs e)
        {
            OpenFileDialog theDialog = new OpenFileDialog
            {
                Title = "Load Scene",
                Filter = "XML files|*.xml"
            };
            if (theDialog.ShowDialog() == DialogResult.OK)
            {
                EngineInterface.LoadNewScene(_editorSystem, theDialog.FileName);

                _scene = new Scene
                {
                    Name = Path.GetFileNameWithoutExtension(theDialog.FileName),
                    FilePath = theDialog.FileName,
                    HasSavedOnce = true,
                    HasChanged = false,
                };
                this.Text = EDITOR_TITLE_PREFIX + _scene.Name;
                _hierarchy.CreateHierachyList(_sceneManagerSystem);
            }
        }

        private void NewSceneClicked(object sender, EventArgs e)
        {

        }

        private void SaveSceneClicked(object sender, EventArgs e)
        {
            if (_scene.HasSavedOnce)
            {
                EngineInterface.SaveScene(_editorSystem, _scene.FilePath); // TODO: Check if save was successful or not
                _scene.HasChanged = false;
            }
            else
            {
                SaveAsSceneClicked(sender, e); // Open up dialog and browse where to save scene
            }
        }

        private void SaveAsSceneClicked(object sender, EventArgs e)
        {
            SaveFileDialog theDialog = new SaveFileDialog
            {
                Title = "Save Scene",
                Filter = "XML files|*.xml"
            };
            if (theDialog.ShowDialog() == DialogResult.OK)
            {
                EngineInterface.SaveScene(_editorSystem, theDialog.FileName); // TODO: Check if save was successful or not

                _scene.Name = Path.GetFileNameWithoutExtension(theDialog.FileName);
                _scene.FilePath = theDialog.FileName;
                _scene.HasSavedOnce = true;
                _scene.HasChanged = false;
                this.Text = EDITOR_TITLE_PREFIX + _scene.Name;
            }
        }
    }
}
