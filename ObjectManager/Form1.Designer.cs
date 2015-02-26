namespace ObjectManager
{
    partial class ObjectManager
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
            this.menu = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.open = new System.Windows.Forms.ToolStripMenuItem();
            this.save = new System.Windows.Forms.ToolStripMenuItem();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.convertToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.convertMesh = new System.Windows.Forms.ToolStripMenuItem();
            this.menu.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem,
            this.convertToolStripMenuItem});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(833, 24);
            this.menu.TabIndex = 0;
            this.menu.Text = "menu";
            this.menu.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menu_ItemClicked);
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.open,
            this.save});
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.menuToolStripMenuItem.Text = "File";
            this.menuToolStripMenuItem.Click += new System.EventHandler(this.menuToolStripMenuItem_Click);
            // 
            // open
            // 
            this.open.Name = "open";
            this.open.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.open.Size = new System.Drawing.Size(152, 22);
            this.open.Text = "Open";
            this.open.Click += new System.EventHandler(this.open_Click);
            // 
            // save
            // 
            this.save.Name = "save";
            this.save.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.save.Size = new System.Drawing.Size(152, 22);
            this.save.Text = "Save";
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.Location = new System.Drawing.Point(3, 3);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(807, 382);
            this.treeView1.TabIndex = 1;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(0, 27);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(821, 414);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.treeView1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(813, 388);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(813, 388);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // convertToolStripMenuItem
            // 
            this.convertToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.convertMesh});
            this.convertToolStripMenuItem.Name = "convertToolStripMenuItem";
            this.convertToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.convertToolStripMenuItem.Text = "Convert";
            // 
            // convertMesh
            // 
            this.convertMesh.Name = "convertMesh";
            this.convertMesh.Size = new System.Drawing.Size(152, 22);
            this.convertMesh.Text = "Mesh";
            this.convertMesh.Click += new System.EventHandler(this.convertMesh_Click);
            // 
            // ObjectManager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(833, 453);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.menu);
            this.MainMenuStrip = this.menu;
            this.Name = "ObjectManager";
            this.Text = "Object manager";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem open;
        private System.Windows.Forms.ToolStripMenuItem save;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ToolStripMenuItem convertToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem convertMesh;

    }
}

