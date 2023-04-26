//
// Created by timat on 26.04.2023.
//

#include <cstring>
#include <iostream>
#include "LazyString.h"

LazyString::LazyString(const char *cStr) {
    std::cout << "Alloc\n";
    m_length = strlen(cStr);
    m_data = new char[m_length];
    memccpy(m_data, cStr, 1, m_length);
    m_counter = new int(1);
}

LazyString::LazyString(const LazyString &other) : m_data(other.m_data), m_length(other.m_length), m_counter(other.m_counter) {
    (*m_counter)++;
}

LazyString::LazyString(const LazyString &&other) : LazyString(other) {
}

char &LazyString::operator[](int pos) {
    EnsureUnique();
    return m_data[pos];
}

char LazyString::operator[](int pos) const {
    return m_data[pos];
}

void LazyString::Print() const {
    std::cout << "Lazy string. counter=" << *m_counter << " [";
    for (int i = 0; i < m_length; i++) {
        std::cout << m_data[i];
    }
    std::cout << "] id=" << (long long)(m_counter)%1000 << "\n";
}

LazyString::~LazyString() {
    (*m_counter)--;
    if (*m_counter == 0) {
        delete m_counter;
        delete[] m_data;
    }
}

void LazyString::EnsureUnique() {
    if (*m_counter > 1) {
        (*m_counter)--;
        std::cout << "Copy\n";
        m_counter = new int(1);
        char * old = m_data;
        m_data = new char[m_length];
        memccpy(m_data, old, 1, m_length);
    }
}

void LazyString::operator+=(const LazyString &other) {
    EnsureUnique();
    char * old = m_data;
    int oldLen = m_length;
    m_length += other.m_length;
    m_data = new char[m_length];
    memccpy(m_data, old, 1, oldLen);
    memccpy(m_data + oldLen, other.m_data, 1, other.m_length);
    delete[] old;
}
