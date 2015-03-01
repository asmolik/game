#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Xml
{
protected:
	std::fstream file;

public:
	Xml();
	~Xml();
	int openFile(std::string fileName);
	// Read the value of the element.
	std::string valueOfElement(std::string& element);
};

