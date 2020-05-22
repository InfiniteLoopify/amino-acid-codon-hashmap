#include <iostream>
#include <windows.h>
#include "Option.h"
#include "Heading.h"

Option::Option(){}
Option::~Option(){}

void Option::pause()
{
	system("Pause");
	system("cls");
}

int Option::selectOption(int start, int end, const std::string &str = "-")
{
	int select;
	while (true)
	{
		Heading heading;
		heading.displayHeading("Protein Codon Dictionary");

		std::cout << str << std::endl;
		std::cin >> select;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cerr << "\nInvalid Entry.";
			std::cout << '\a' << "\n";
			pause();
		}
		else
		{
			std::cin.ignore(32767, '\n');

			if (select >= start && select <= end)
			{
				std::cout << "\n";
				pause();
				return select;
			}
			else
			{
				std::cerr << "\nInvalid Entry.\n";
				pause();
			}
		}
	}
}
int Option::selectOption(int &num, const std::string &str = "-")
{
	while (true)
	{
		Heading heading;
		heading.displayHeading("Protein Codon Dictionary");

		std::cout << str << std::endl;
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cerr << "\nInvalid Data Entered.";
			std::cout << '\a' << "\n";
			pause();
		}
		else
		{
			std::cin.ignore(32767, '\n');

			if (num > 0)
			{
				std::cout << "\n";
				pause();
				return num;
			}
			else
			{
				std::cerr << "\nInvalid Value Entered.\n";
				pause();
			}
		}
	}
}
int Option::selectOption(std::string &name, const std::string &str = "-")
{
	Heading heading;
	heading.displayHeading("Protein Codon Dictionary");

	std::cout << str << std::endl;
	std::getline(std::cin, name);
	pause();
	return true;
}

void Option::waiting(int tempTime, const std::string &str)
{
    char arrow = 16;
	while (tempTime > 0)
	{
//		Heading heading;
//		heading.displayHeading("Protein Codon Dictionary");

		std::cout << " " << arrow << " " << str;
		for (int i = 0; i < 3 - (tempTime % 3); ++i)
			std::cout << ".";
		std::cout << "\n";
		Sleep(500);
		system("cls");
		tempTime--;
	}
	std::cout << " " << arrow << " " << str << " ";
}
