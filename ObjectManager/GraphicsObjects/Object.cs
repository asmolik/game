using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace ObjectManager
{
	class Object
	{
		protected String type = "";
		protected float[] position = new float[3] { 0.0f, 0.0f, 0.0f };
		protected float[] orientation = new float[4] { 0.0f, 0.0f, 0.0f, 1.0f };
		protected float[] scale = new float[3] { 1.0f, 1.0f, 1.0f };
		protected String meshFile = "";
		protected String materialFile = "";

		public String Type
		{
			get { return type; }
			set { type = value; }
		}

		public float[] Scale
		{
			get { return scale; }
			set { scale = value; }
		}

		public float[] Orientation
		{
			get { return orientation; }
			set { orientation = value; }
		}

		public float[] Position
		{
			get { return position; }
			set { position = value; }
		}

		public String MeshFile
		{
			get { return meshFile; }
			set { meshFile = value; }
		}

		public String MaterialFile
		{
			get { return materialFile; }
			set { materialFile = value; }
		}

		internal void readXml(System.Xml.Linq.XElement element)
		{
			try
			{
				type = element.Element("Type").Value;
				// Load data of the object.
				position[0] = float.Parse(element.Element("Position").Element("X").Value,
					CultureInfo.InvariantCulture);
				position[1] = float.Parse(element.Element("Position").Element("Y").Value,
					CultureInfo.InvariantCulture);
				position[2] = float.Parse(element.Element("Position").Element("Z").Value,
					CultureInfo.InvariantCulture);

				orientation[0] = float.Parse(element.Element("Orientation").Element("X").Value,
					CultureInfo.InvariantCulture);
				orientation[1] = float.Parse(element.Element("Orientation").Element("Y").Value,
					CultureInfo.InvariantCulture);
				orientation[2] = float.Parse(element.Element("Orientation").Element("Z").Value,
					CultureInfo.InvariantCulture);
				orientation[3] = float.Parse(element.Element("Orientation").Element("W").Value,
					CultureInfo.InvariantCulture);

				scale[0] = float.Parse(element.Element("Scale").Element("X").Value,
					CultureInfo.InvariantCulture);
				scale[1] = float.Parse(element.Element("Scale").Element("Y").Value,
					CultureInfo.InvariantCulture);
				scale[2] = float.Parse(element.Element("Scale").Element("Z").Value,
					CultureInfo.InvariantCulture);

				meshFile = element.Element("Mesh").Value;
				materialFile = element.Element("Material").Value;
			}
			catch (System.Exception ex)
			{
				ex.ToString();
			}
		}
	}
}
