#pragma once

class LazyString {
public:

    LazyString(const char * cStr);
    LazyString(const LazyString & other);
    LazyString(const LazyString && other);
    char& operator[](int pos);
    char operator[](int pos) const;
    void operator+=(const LazyString & other);
    void Print() const;
    ~LazyString();

private:

    void EnsureUnique();

    char * m_data;
    int * m_counter;
    int m_length;
};

