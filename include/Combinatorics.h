#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include <vector>
#include <fstream>

template <class T>
class Combinatorics
{
    public:
        Combinatorics(const std::vector<T> &tempList = std::vector<T>());
        ~Combinatorics();

        void set_objectList(const std::vector<T> &tempList);
        void set_repeat(bool doRepeat);
        void reset_count();

        int get_count();
        int get_repeat();
        void display_objectList();

        void permutation(int length, int index = 0);
        void combination(int length, int index = 0);

    private:
        void display_combination();

    private:
        std::vector<T> m_objectList;
        std::vector<T> m_combination;
        std::ofstream outf;
        bool m_repeat;
        int m_count;
};

#include "../src/Combinatorics.cpp"

#endif // COMBINATORICS_H
