#include <iostream>
#include <vector>
#include <conio.h>
#include "Combinatorics.h"
#include "Hashing.h"
#include "Heading.h"
#include "Option.h"

using namespace std;

//vector to store all 20 amino Acid names
vector <string> AminoAcids {
    "A-Alanine",
    "C-Cysteine",
    "D-Aspartic acid",
    "E-Glutamic acid",
    "F-Phenylalanine",
    "G-Glycine",
    "H-Histidine",
    "I-Isoleucine",
    "K-Lysine",
    "L-Leucine",
    "M-Methionine",
    "N-Asparagine",
    "P-Proline",
    "Q-Glutamine",
    "R-Arginine",
    "S-Serine",
    "T-Threonine",
    "V-Valine",
    "W-Tryptophan",
    "Y-Tyrosine",
};

//display all 20 amino acids with formating
void displayList()
{
    const int maxLength = 15;
    for(int i = 0; i < AminoAcids.size(); ++i)
    {
        cout << AminoAcids[i];
        for(int j = AminoAcids[i].length(); j < maxLength; ++j)
            cout << " ";
        if((i+1) % 4 == 0)
            cout << "\n";
        else
            cout << "\t";
    }
    cout << "\n";
}

//display the full amino acid name of combination in a codon
bool displayCombination(const string &str)
{
    bool unknown = false;
    for(int i = 0; i < str.length(); ++i)
    {
        for(int j = 0; j < AminoAcids.size(); ++j)
        {
            if(AminoAcids[j][0] == str[i])
            {
                cout << "\t" << AminoAcids[j] << "\n";
                break;
            }
            if(j == AminoAcids.size() - 1)
            {
                unknown = true;
                cout << "\t" << str[i] << "-???\n";
            }
        }
    }
    return unknown;
}

int main()
{
    //change console color
    system("COLOR f0");
	system("title Protein Codon Dictionary");

	//read the count number of records in database from the
    const char *fileName = "Dictionary.txt";
    ifstream inf(fileName);
    int dataSize = 0;
    if(!inf)
    {
        std::cerr << "File not Found.\n";
        system("pause");
        return 0;
    }
    inf >> dataSize;

    //read all the records from the file
    HashTable ht(dataSize);
    ht.readFile(fileName);

    //loop to run Program until the user wants to
    bool runProgram = true;
    while(runProgram)
    {
        //select and option from the menu
       	Option option;
        int selectCase = option.selectOption(0, 5, "Menu: \n_____ \n"
											"1. Show Database.\n"
											"2. Show Database Info.\n"
											"3. Search Database.\n"
											"4. Search Codon in Chain (File).\n"
											"5. Search Codon in Chain (User).\n\n"
											"0. End Program.\n");

        switch (selectCase)
		{
		case 0: //if user wants to end program
			runProgram = false;
			break;
		case 1: //if user wants to display the complete database
			ht.displayTable();
			option.pause();
			break;
		case 2: //if user wants to show the information about the database
		    ht.displayInfo();
			option.pause();
			break;
		case 3: //if user wants to search a specific codon in the database
            {
                displayList();

                //ask user for codon an capitalize it
                cout << "Enter Codon to Search: ";
                string input;
                getline(cin, input);
                ht.stringCapitalization(input);

                //if codon is present in database, i.e is valid
                if(ht.searchKeyPresent(input))
                {
                    Data key = ht.searchKey(input);
                    cout << "\nCodon: " << key.getKey() << "\n";
                    displayCombination(key.getKey());
                    cout << "\nIndex: " << key.getIndex() << "\n";
                    cout << "\n";
                }
                //if codon is not present in database, i.e is invalid
                else
                {
                    displayCombination(input);
                    cout << "\n";
                        cout << input << " not Found in Database\n\n";
                }
            }
            option.pause();
            break;
        case 4: //if user wants to know the position and count of codon in a protein chain provided in a file
            {
                displayList();

                //read protein chain from file
                string file = "Amino-Chain.txt";
                cout << "File Name: " << file << "\n";

                //option to change file name
                cout << "Change File Name? (Yes-1 / No-2) \n";
                char opt = '-';
                while(!(opt == '1' || opt == '2'))
                    opt = getch();
                system("pause");

                //if yes, then enter file name
                if(opt == '1')
                {
                    cout << "\nFile Name: ";
                    getline(cin, file);
                }
                string chain = ht.readCodonChain(file);

                //if file not found then return to menu
                if(chain.empty())
                {
                    option.pause();
                    break;
                }
                cout << "\nCodon Chain:\n" << chain << "\n\n";

                //ask user for codon and capitalize it
                cout << "Codon Search: ";
                string input;
                getline(cin, input);
                ht.stringCapitalization(input);
                displayCombination(input);
                cout << "\n";

                //search the codon in chain and display the count and position of codon
                ht.searchCodonChain(input, chain);
                cout << "\n";
            }
            option.pause();
            break;
        case 5: //if user wants to know the position and count of codon in a protein chain provided by the user
            {
                displayList();

                //input a protein chain from user
                cout << "***NOTE*** \nCodon Chain Format: XXX-XXX-XXX-XXX-XXX-...\n\n";
                cout << "Enter Codon Chain: ";
                string chain;
                getline(cin, chain);
                ht.stringCapitalization(chain);
                cout << "\nCodon Chain:\n" << chain << "\n\n";

                //ask user for codon and capitalize it
                cout << "Codon Search: ";
                string input;
                getline(cin, input);
                ht.stringCapitalization(input);
                displayCombination(input);
                cout << "\n";

                //search the codon in chain and display the count and position of codon
                ht.searchCodonChain(input, chain);
                cout << "\n";
            }
            option.pause();
            break;
		default: //if the case selected is invalid
			std::cerr << "\nInvalid SelectionCase Entered.\n";
		}
    }

    return 0;
}

//    vector<char> vec {'A','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','Y'};
//    Combinatorics<char> co;
//    co.set_repeat(true);
//    co.set_objectList(vec);
//
//    co.permutation(3);
//    cout << co.get_count();

