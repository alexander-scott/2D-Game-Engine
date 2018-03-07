namespace GEPAA_Editor
{
    partial class Editor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.panel1 = new System.Windows.Forms.Panel();
            this.lblHierachy = new System.Windows.Forms.Label();
            this.lblPrefabs = new System.Windows.Forms.Label();
            this.btnPlay = new System.Windows.Forms.Button();
            this.hierarchyListBox = new System.Windows.Forms.ListView();
            this.dgvInspector = new System.Windows.Forms.DataGridView();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.newGameObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.renameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.testToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.dgvInspector)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            this.mainMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(257, 66);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(915, 598);
            this.panel1.TabIndex = 1;
            // 
            // lblHierachy
            // 
            this.lblHierachy.AutoSize = true;
            this.lblHierachy.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblHierachy.Location = new System.Drawing.Point(72, 38);
            this.lblHierachy.Name = "lblHierachy";
            this.lblHierachy.Size = new System.Drawing.Size(97, 25);
            this.lblHierachy.TabIndex = 2;
            this.lblHierachy.Text = "Hierachy";
            // 
            // lblPrefabs
            // 
            this.lblPrefabs.AutoSize = true;
            this.lblPrefabs.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblPrefabs.Location = new System.Drawing.Point(72, 364);
            this.lblPrefabs.Name = "lblPrefabs";
            this.lblPrefabs.Size = new System.Drawing.Size(100, 25);
            this.lblPrefabs.TabIndex = 4;
            this.lblPrefabs.Text = "Inspector";
            // 
            // btnPlay
            // 
            this.btnPlay.Location = new System.Drawing.Point(571, 37);
            this.btnPlay.Name = "btnPlay";
            this.btnPlay.Size = new System.Drawing.Size(75, 23);
            this.btnPlay.TabIndex = 8;
            this.btnPlay.Text = "PLAY";
            this.btnPlay.UseVisualStyleBackColor = true;
            // 
            // hierarchyListBox
            // 
            this.hierarchyListBox.AllowDrop = true;
            this.hierarchyListBox.LabelEdit = true;
            this.hierarchyListBox.Location = new System.Drawing.Point(12, 66);
            this.hierarchyListBox.Name = "hierarchyListBox";
            this.hierarchyListBox.Size = new System.Drawing.Size(229, 295);
            this.hierarchyListBox.TabIndex = 9;
            this.hierarchyListBox.UseCompatibleStateImageBehavior = false;
            // 
            // dgvInspector
            // 
            this.dgvInspector.AllowUserToAddRows = false;
            this.dgvInspector.AllowUserToDeleteRows = false;
            this.dgvInspector.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvInspector.Location = new System.Drawing.Point(12, 392);
            this.dgvInspector.Name = "dgvInspector";
            this.dgvInspector.Size = new System.Drawing.Size(229, 272);
            this.dgvInspector.TabIndex = 11;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newGameObjectToolStripMenuItem,
            this.renameToolStripMenuItem,
            this.deleteToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(168, 70);
            // 
            // newGameObjectToolStripMenuItem
            // 
            this.newGameObjectToolStripMenuItem.Name = "newGameObjectToolStripMenuItem";
            this.newGameObjectToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.newGameObjectToolStripMenuItem.Text = "New GameObject";
            // 
            // renameToolStripMenuItem
            // 
            this.renameToolStripMenuItem.Name = "renameToolStripMenuItem";
            this.renameToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.renameToolStripMenuItem.Text = "Rename";
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testToolStripMenuItem});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(1184, 24);
            this.mainMenu.TabIndex = 12;
            this.mainMenu.Text = "menuStrip1";
            // 
            // testToolStripMenuItem
            // 
            this.testToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newSceneToolStripMenuItem,
            this.loadSceneToolStripMenuItem,
            this.saveSceneToolStripMenuItem,
            this.saveAsSceneToolStripMenuItem});
            this.testToolStripMenuItem.Name = "testToolStripMenuItem";
            this.testToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.testToolStripMenuItem.Text = "Scene";
            // 
            // newSceneToolStripMenuItem
            // 
            this.newSceneToolStripMenuItem.Name = "newSceneToolStripMenuItem";
            this.newSceneToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.newSceneToolStripMenuItem.Text = "New Scene";
            this.newSceneToolStripMenuItem.Click += new System.EventHandler(this.NewSceneClicked);
            // 
            // loadSceneToolStripMenuItem
            // 
            this.loadSceneToolStripMenuItem.Name = "loadSceneToolStripMenuItem";
            this.loadSceneToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.loadSceneToolStripMenuItem.Text = "Load Scene";
            this.loadSceneToolStripMenuItem.Click += new System.EventHandler(this.LoadSceneClicked);
            // 
            // saveSceneToolStripMenuItem
            // 
            this.saveSceneToolStripMenuItem.Name = "saveSceneToolStripMenuItem";
            this.saveSceneToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.saveSceneToolStripMenuItem.Text = "Save Scene";
            this.saveSceneToolStripMenuItem.Click += new System.EventHandler(this.SaveSceneClicked);
            // 
            // saveAsSceneToolStripMenuItem
            // 
            this.saveAsSceneToolStripMenuItem.Name = "saveAsSceneToolStripMenuItem";
            this.saveAsSceneToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.saveAsSceneToolStripMenuItem.Text = "Save As Scene";
            this.saveAsSceneToolStripMenuItem.Click += new System.EventHandler(this.SaveAsSceneClicked);
            // 
            // Editor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.WhiteSmoke;
            this.ClientSize = new System.Drawing.Size(1184, 704);
            this.Controls.Add(this.mainMenu);
            this.Controls.Add(this.dgvInspector);
            this.Controls.Add(this.hierarchyListBox);
            this.Controls.Add(this.btnPlay);
            this.Controls.Add(this.lblPrefabs);
            this.Controls.Add(this.lblHierachy);
            this.Controls.Add(this.panel1);
            this.MainMenuStrip = this.mainMenu;
            this.Name = "Editor";
            this.Text = "Editor";
            this.Load += new System.EventHandler(this.EditorLoading);
            ((System.ComponentModel.ISupportInitialize)(this.dgvInspector)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label lblHierachy;
        private System.Windows.Forms.Label lblPrefabs;
        private System.Windows.Forms.Button btnPlay;
        private System.Windows.Forms.ListView hierarchyListBox;
        private System.Windows.Forms.DataGridView dgvInspector;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem newGameObjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem renameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem testToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newSceneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadSceneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveSceneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsSceneToolStripMenuItem;
    }
}

