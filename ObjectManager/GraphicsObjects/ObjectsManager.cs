using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectManager
{
	class ObjectsManager
	{
		protected BindingList<Object> objects = new BindingList<Object>();

		internal BindingList<Object> Objects
		{
			get { return objects; }
			set { objects = value; }
		}

		public void addObject(Object o)
		{
			objects.Add(o);
		}
	}
}
