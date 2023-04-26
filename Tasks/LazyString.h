#pragma once

class CLazyString {
public:

    CLazyString(const char * cStr);
    CLazyString(const CLazyString & other);
    CLazyString(const CLazyString && other);
    char& operator[](int pos);
    char operator[](int pos) const;
    void operator+=(const CLazyString & other);
    void Print() const;
    ~CLazyString();

private:

    void EnsureUnique();

    char * m_data;
    int * m_counter;
    int m_length;
};

