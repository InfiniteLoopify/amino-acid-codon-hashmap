#include <iostream>
#include <string>
#include "Heading.h"

Heading::Heading(){}
Heading::~Heading(){}

void Heading::displayHeading(const std::string &str)
{
	std::cout << "\t";
	for (int i = 0; i < static_cast<int>(str.length()) + 2; ++i)
		std::cout << m_2;
	std::cout << "\n";

	std::cout << "\t" << m_1 << str << m_1 << std::endl;

	std::cout << "\t";
	for (int i = 0; i < static_cast<int>(str.length()) + 2; ++i)
		std::cout << m_3;
	std::cout << "\n";
}
