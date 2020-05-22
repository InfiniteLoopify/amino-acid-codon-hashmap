#include "Hashing.h"
#include <iostream>
#include <cmath>
#include <fstream>

HashTable::HashTable(int size) : CODON_LENGTH(3)
{
    m_collisions = 0;
    m_maxCollisions = 0;
    m_capacity = getNextPrime(size * 2); //capacity twice as much as size
    m_size = 0;
    m_table = new Data[m_capacity];
}

HashTable::~HashTable()
{
    if(m_table != nullptr)
        delete[] m_table;
}

//if load factor is greater than 0.5 than rehash
void HashTable::reHash()
{
    std::cout << "ReHashing...\n";

    int newCap = getNextPrime(m_capacity * 2);
    Data *temp = new Data[newCap];

    //for every element, replace its position according to new table capacity
    for(int i = 0; i < m_capacity; ++i)
    {
        //if table is not empty than find next index using double hashing
        if(!m_table[i].isEmpty())
        {
            const std::string &key = m_table[i].getKey();
            int hashVal = hash1(key);
            int index = hashVal & m_capacity;
            int i = 0;
            while(!temp[index].isEmpty())
            {
                ++i;
                index = (hashVal + i * hash2(index)) % m_capacity;
            }
            temp[index].insertKey(index, key);
        }
    }
    m_capacity = newCap;
    m_table = temp;
    delete[] temp;
}

//check if load factor is greater than 0.5
bool HashTable::isFull() {return (m_capacity - 1) == m_size;}

//hash function 1 to convert string to key
int HashTable::hash1(const std::string &codonString)
{
    //best value: 59
    int h = 0;
    for(int i = 0; i < codonString.length(); ++i)
        h = h * 59 + (codonString[i] - 26);
    return h;
}

//hash function 2 for double hashing
int HashTable::hash2(int data) {return 7883 - (data*2 % 7883);} //best value: 7883

//capitalize string
void HashTable::stringCapitalization(std::string &str)
{
    int operation = 32;
    for(int i = 0; i < str.length(); ++i)
        if(str[i] >= 'a' && str[i] <= 'z')
            str[i] -= operation;
}

//read protein chain string from a file and return it
std::string HashTable::readCodonChain(const std::string &fileName)
{
    std::ifstream inf(fileName);
    std::string chain;
    if(!inf)
        std::cerr << "File not Found.\n";
    else
    {
        inf >> chain;
        return chain;
    }
}

//search for a codon string in a codon protein chain
void HashTable::searchCodonChain(const std::string &codonString, const std::string &codonChain)
{
    //Rabin-Karp Algorithm
    int codonStringSum = codonString[0]*1 + codonString[1]*10 + codonString[2]*100;
    int count = 0;

    //if codon string is present in database then search it
    if(searchKeyPresent(codonString))
    {
        bool isPresent = false;
        std::cout << "Codon Position: ";
        const int codonLength = 4;

        //for all the codons in the chain
        for(int i = 0, tempI = 0; i < codonChain.length(); i += codonLength, tempI += codonLength-1)
        {
            int hashValue = codonChain[i]*1 + codonChain[i+1]*10 + codonChain[i+2]*100;

            //if hash value of substring of chain and codon is same, then display position and increment count
            if(hashValue == codonStringSum)
            {
                isPresent = true;
                count++;
                std::cout << tempI/CODON_LENGTH + 1 << " ";
            }
        }
        if(!isPresent)
            std::cout << "-";
        std::cout << "\nCodon Count: " << count << "\n";
    }
    //if string is not in database then inform user
    else
        std::cerr << "Invalid Input Entered.\n\n";
    return;
}

//insert element in database
void HashTable::insertKey(const std::string &codonString)
{
    //if table is full then rehash
    if(isFull())
        reHash();

    int hashVal = hash1(codonString);
    int index = hashVal % m_capacity;
    int i = 0;

    //find next position in hash table using double hashing until the position is empty and then insert new element
    while(!m_table[index].isEmpty())
    {
        ++i;
        index = (hashVal + i * hash2(index)) % m_capacity;
    }
    m_collisions += i;

    if(i >= m_collisionsCount.size())
        m_collisionsCount.resize(i + 1);
    ++m_collisionsCount[i];

    if(i > m_maxCollisions)
        m_maxCollisions = i;

    m_table[index].insertKey(index, codonString);
    ++m_size;
}

//delete element from hash table
void HashTable::deleteKey(const std::string &codonString)
{
    int hashVal = hash1(codonString);
    int index = hashVal % m_capacity;
    int i = 0;

    //find next index until its empty
    while(!m_table[index].isEmpty())
    {
        //if search data and table data is same then delete it
        if(m_table[index].getKey() == codonString)
        {
            m_table[index].deleteKey();
            --m_size;
            return;
        }
        ++i;
        index = (hashVal + i * hash2(index)) % m_capacity;
    }
    std::cout << "notFound\n";
}

//search element in hash table
const Data& HashTable::searchKey(const std::string &codonString)
{
    int hashVal = hash1(codonString);
    int index = hashVal % m_capacity;

    //if codon length is not equal to 3, then codon is invalid
    if(codonString.length() != CODON_LENGTH)
    {
        std::cout << "\nInvalid Length of " << codonString << "\n";
        return m_table[index];
    }

    int i = 0;
    //find next index until index is empty
    while(!m_table[index].isEmpty())
    {
        //element found then return it
        if(codonString == m_table[index].getKey())
            return m_table[index];
        ++i;
        index = (hashVal + i * hash2(index)) % m_capacity;
    }
    std::cout << "\n" << codonString << " not Found\n";
    return m_table[index];
}

//search if element is present or not in table
bool HashTable::searchKeyPresent(const std::string &codonString)
{
    //if codon length is not equal to 3, then codon is invalid
    if(codonString.length() != CODON_LENGTH)
        return false;

    int hashVal = hash1(codonString);
    int index = hashVal % m_capacity;
    int i = 0;

    //search until index is empty
    while(!m_table[index].isEmpty())
    {
        //if element is found then return true
        if(codonString == m_table[index].getKey())
            return true;
        ++i;
        index = (hashVal + i * hash2(index)) % m_capacity;
    }
    //if not found then return false
    return false;
}

//display info about the table
void HashTable::displayInfo()
{
    std::cout << "\n";
    std::cout << "Table Size: " << m_size << std::endl;
    std::cout << "Table Capacity: " << m_capacity << std::endl;
    std::cout << "Total Collisions: " << m_collisions << std::endl;
    std::cout << "Max Collisions: " << m_maxCollisions << std::endl;

    std::cout << "\nMax Collisions Count: " << std::endl;
    for(int i = 0; i < m_collisionsCount.size(); ++i)
        std::cout << "\t" << i << " Collisions: " << m_collisionsCount[i] << "\n";

    std::cout << "\n";
}

//display the complete table
void HashTable::displayTable()
{
    for(int i = 0; i < m_capacity; ++i)
        if(!m_table[i].isEmpty())
            std::cout << m_table[i].getKey() << " ";
}

int HashTable::getNextPrime(int num)
{
    for(int i = num; true; ++i)
        if(isPrime(i))
            return i;
}

int HashTable::isPrime(int num)
{
    for(int i = 2; i <= sqrt(num); ++i)
        if(num % i == 0)
            return false;
    return true;
}

//read all the records from file
void HashTable::readFile(const char* str)
{
    std::ifstream inf(str);
    std::string tempStr;
    if(!inf)
        std::cerr << "File not Found.";
    else
    {
        inf >> tempStr;
        while(!inf.eof())
        {
            inf >> tempStr;
            insertKey(tempStr);
        }
    }
}

int HashTable::getCap(){return m_capacity;}
int HashTable::getSize(){return m_size;}
