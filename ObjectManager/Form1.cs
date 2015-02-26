using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Xml.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ObjectManager
{
    public partial class ObjectManager : Form
    {
        public ObjectManager()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void menuToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void menu_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void open_Click(object sender, EventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.DefaultExt = "*.*";
            fd.Filter = "XML|*.xml";
            if (fd.ShowDialog() == DialogResult.OK)
            {
                //populate treeview with the data form the file
                TreeView tv = new TreeView();
                var xmlFromFile = XDocument.Load(fd.FileName);
                createTreeNodes(xmlFromFile.Root.Elements(), treeView1.Nodes);
            }
        }

        private void createTreeNodes(IEnumerable<XElement> elements,
                             TreeNodeCollection treeLevel)
        {
            foreach (var element in elements)
            {
                //Create nodes for each xml element..
                var node = new TreeNode(element.Name.LocalName);
                node.Nodes.Add(element.Nodes().OfType<XText>().First().Value);
                //..add them to the current "level" in the TreeView..
                treeLevel.Add(node);

                //..and then create (and add) each node's child nodes:
                createTreeNodes(element.Elements(), node.Nodes);
            }
        }

        private void convertMesh_Click(object sender, EventArgs e)
        {
            MeshImporter.CSMeshImporter importer = new MeshImporter.CSMeshImporter();
            OpenFileDialog fd = new OpenFileDialog();
            fd.DefaultExt = "*.*";
            if (fd.ShowDialog() == DialogResult.OK)
            {
                importer.loadMesh(fd.FileName);
            }
            SaveFileDialog sd = new SaveFileDialog();
            sd.FileName = "mesh.xml";
            sd.DefaultExt = "*.*";
            if (sd.ShowDialog() == DialogResult.OK)
            {
                importer.saveMesh(sd.FileName);
            }
        }
    }
}
