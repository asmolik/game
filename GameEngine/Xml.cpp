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
// Very simple - reads the string after the element until '<' is found.
std::string Xml::valueOfElement(const std::string& element)
{
	std::stringstream stream;
	std::string line;
	std::string tmp;
	std::string value;

	// Look for <elementName>
	while (true)
	{
		getline(stream, tmp, '<');
		getline(stream, tmp, '>');
		if (tmp.find(element) == std::string::npos)
			continue;
		getline(stream, value, '<');
		break;
	}
	return value;
}
