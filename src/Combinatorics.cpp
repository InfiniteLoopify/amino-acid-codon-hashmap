#include <iostream>
#include <vector>
#include <algorithm>
#include "Combinatorics.h"

#ifndef COMBINATORICS_IMP
#define COMBINATORICS_IMP

template <class T> Combinatorics<T>::Combinatorics(const std::vector<T> &tempList)
                : m_repeat(true), m_count(0), m_objectList(tempList)
                {outf.open("Dictionary.txt");}
template <class T> Combinatorics<T>::~Combinatorics(){}

template <class T> void Combinatorics<T>::set_objectList(const std::vector<T> &tempList){m_objectList = tempList;}
template <class T> void Combinatorics<T>::set_repeat(bool doRepeat){m_repeat = doRepeat;}
template <class T> void Combinatorics<T>::reset_count(){m_count = 0;}

template <class T> int Combinatorics<T>::get_count(){return m_count;}
template <class T> int Combinatorics<T>::get_repeat(){return m_repeat;}
template <class T> void Combinatorics<T>::display_objectList()
{
    for(int i = 0; i < m_objectList.size(); ++i)
        std::cout << m_objectList[i];
    std::cout << "\n";
}
template <class T> void Combinatorics<T>::display_combination()
{
    for(int i = 0; i < m_combination.size(); ++i)
        outf << m_combination[i];
    outf << std::endl;
}
template <class T> void Combinatorics<T>::permutation(int length, int index)
{
    if(length < 0 || (length > m_objectList.size() && m_repeat == false))
    {
        std::cout << "Invalid: \n(r > n) || (r < 0)\n";
        return;
    }

    if(m_combination.size() >= length)
    {
        display_combination();
        ++m_count;
    }
    else
    {
        for(int i = 0; i < m_objectList.size(); ++i)
        {
            if (  (m_repeat == true) ||
                std::find(m_combination.begin(), m_combination.end(), m_objectList[i]) == m_combination.end() )
            {
                m_combination.push_back(m_objectList[i]);
                permutation(length, i);
                m_combination.pop_back();
            }
        }
    }
}
template <class T> void Combinatorics<T>::combination(int length, int index)
{
    if(length < 0 || (length > m_objectList.size() && m_repeat == false))
    {
        std::cout << "Invalid: \n(r > n) || (r < 0)\n";
        return;
    }

    if(m_combination.size() >= length)
    {
        display_combination();
        ++m_count;
    }
    else
    {
        for(int i = index; i < m_objectList.size(); ++i)
        {
            m_combination.push_back(m_objectList[i]);

            if(m_repeat == true)
                combination(length, i);
            else
                combination(length, i+1);

            m_combination.pop_back();
        }
    }
}

#endif // COMBINATORICS_IMP
