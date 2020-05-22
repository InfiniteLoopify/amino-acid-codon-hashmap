#include "Data.h"

Data::Data() : m_full(false), m_index(-1) {}
Data::~Data(){}

bool Data::isEmpty() {return !m_full;}
const std::string& Data::getKey() {return m_str;}
int Data::insertKey(int index, const std::string &str)
{
    m_index = index;
    m_str = str;
    m_full = true;
}
int Data::deleteKey(){m_full = false; m_index = -1;}
void Data::setIndex(int index){m_index = index;}
int Data::getIndex(){return m_index;}
