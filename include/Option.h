#ifndef OPTION_H
#define OPTION_H

#include <string>
//#include "Passenger.h"

class Option
{
public:
	Option();
	~Option();

	void pause();
    int selectOption(int start, int end, const std::string &str);
	int selectOption(int &num, const std::string &str);
	int selectOption(std::string &name, const std::string &str);
	void waiting(int tempTime, const std::string &str = "-");

};

#endif // OPTION_H
