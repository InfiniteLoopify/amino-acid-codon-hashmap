#ifndef DATA_H
#define DATA_H

#include <string>

class Data
{
    public:
        Data();
        ~Data();

        bool isEmpty();
        const std::string &getKey();

        int insertKey(int index, const std::string &str);
        int deleteKey();

        void setIndex(int index);
        int getIndex();

    private:
        std::string m_str;
        bool m_full;
        int m_index;
};

#endif // DATA_H
