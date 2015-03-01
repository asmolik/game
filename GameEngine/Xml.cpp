#include "Xml.h"


Xml::Xml()
{
}


Xml::~Xml()
{
}


int Xml::openFile(std::string fileName)
{
	file.open(fileName);
	if (!file.is_open())
	{
		return -1;
	}
	return 0;
}


// Read the value of the element.
std::string Xml::valueOfElement(std::string& elementName)
{
	std::stringstream stream;
	std::string line;
	std::string value;
	std::string element = "<" + elementName + ">";

	// Look for <element>
	while (getline(file, line))
	{
		if (line.find(element) == std::string::npos)
			continue;
	}
	return value;
}
