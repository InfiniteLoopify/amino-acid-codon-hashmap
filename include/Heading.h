#ifndef HEADING_H
#define HEADING_H

#include <string>

class Heading
{
public:
	Heading();
	~Heading();

	void displayHeading(const std::string &str);

private:
	unsigned const char m_1 = 219;
	unsigned const char m_2 = 220;
	unsigned const char m_3 = 223;
};

#endif
