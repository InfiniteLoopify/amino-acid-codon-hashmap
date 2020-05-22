#include "Data.h"
#include <string>
#include <vector>

#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable
{
    public:
        HashTable(int size);
        ~HashTable();

        void reHash();
        bool isFull();

        int getNextPrime(int num);
        int isPrime(int num);

        int hash1(const std::string &codonString);
        int hash2(int data);

        void insertKey(const std::string &codonString);
        void deleteKey(const std::string &codonString);
        const Data& searchKey(const std::string &codonString);
        bool searchKeyPresent(const std::string &codonString);

        void stringCapitalization(std::string &str);
        std::string readCodonChain(const std::string &fileName);
        void searchCodonChain(const std::string &codonString, const std::string &codonChain);

        void readFile(const char* str);
        void displayTable();
        void displayInfo();

        int getCap();
        int getSize();

    private:
        Data *m_table;
        int m_size;
        int m_capacity;
        int m_collisions;
        int m_maxCollisions;
        const int CODON_LENGTH;
        std::vector <int> m_collisionsCount;
};

#endif // HASHTABLE_H
