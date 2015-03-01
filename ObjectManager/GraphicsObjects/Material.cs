using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace ObjectManager
{
	class Material
	{
		private String name = "";
		protected float[] diffuseColor = new float[4] { 135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f };
		protected float[] specularColor = new float[4] { 0.25f, 0.25f, 0.25f, 1.0f };
		protected float shininess;
		protected String diffuseTexture;
		protected String specularTexture;
		protected String normalTexture;
		protected String shininessTexture;

		protected String Name
		{
			get { return name; }
			set { name = value; }
		}

		public float[] DiffuseColor
		{
			get { return diffuseColor; }
			set { diffuseColor = value; }
		}

		public float[] SpecularColor
		{
			get { return specularColor; }
			set { specularColor = value; }
		}

		public float Shininess
		{
			get { return shininess; }
			set { shininess = value; }
		}

		public String DiffuseTexture
		{
			get { return diffuseTexture; }
			set { diffuseTexture = value; }
		}

		public String SpecularTexture
		{
			get { return specularTexture; }
			set { specularTexture = value; }
		}

		public String NormalTexture
		{
			get { return normalTexture; }
			set { normalTexture = value; }
		}

		public String ShininessTexture
		{
			get { return shininessTexture; }
			set { shininessTexture = value; }
		}

		internal void readXml(System.Xml.Linq.XElement element)
		{
			try
			{
				diffuseColor[0] = float.Parse(element.Element("ColorDiffuse").Element("R").Value,
					CultureInfo.InvariantCulture);
				diffuseColor[1] = float.Parse(element.Element("ColorDiffuse").Element("G").Value,
					CultureInfo.InvariantCulture);
				diffuseColor[2] = float.Parse(element.Element("ColorDiffuse").Element("B").Value,
					CultureInfo.InvariantCulture);
				specularColor[0] = float.Parse(element.Element("ColorSpecular").Element("R").Value,
					CultureInfo.InvariantCulture);
				specularColor[1] = float.Parse(element.Element("ColorSpecular").Element("G").Value,
					CultureInfo.InvariantCulture);
				specularColor[2] = float.Parse(element.Element("ColorSpecular").Element("B").Value,
					CultureInfo.InvariantCulture);
				shininess = float.Parse(element.Element("Shininess").Value,
					CultureInfo.InvariantCulture);

				diffuseTexture = element.Element("diffuseTexture").Value;
				specularTexture = element.Element("specularTexture").Value;
				normalTexture = element.Element("normalTexture").Value;
				shininessTexture = element.Element("shininessTexture").Value;

			}
			catch (System.Exception ex)
			{
				ex.ToString();
			}
		}
	}
}
