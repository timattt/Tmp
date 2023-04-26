#pragma once

#include <cstdio>

template <typename T>
class CMyUniquePointer {
public:

    CMyUniquePointer(T * ptr) : m_pointer(ptr)
    {
    }

    ~CMyUniquePointer()
    {
        if (m_pointer != nullptr) {
            delete m_pointer;
        }
    }

    CMyUniquePointer(CMyUniquePointer && other)
    {
        m_pointer = other.m_pointer;
        other.m_pointer = nullptr;
    }

    CMyUniquePointer& operator=(const CMyUniquePointer & other) = delete;

    T& operator*()
    {
        return *m_pointer;
    }

    T* operator->()
    {
        return m_pointer;
    }

    void Info()
    {
        const int mx = 1000;
        long long p2 = (long long) m_pointer;
        p2 %= mx;
        printf("MyUniquePointer: m_pointer = %Ld\n", p2);
    }

private:

    T * m_pointer;

};

struct CCounters {
    long counter = 0;
    long weakCounter = 0;
};

template<typename T>
class CMySharedPointer {
public:

    CMySharedPointer(T * ptr) : m_pointer(ptr)
    {
        Acquire();
    }

    ~CMySharedPointer()
    {
        Release();
    }

    CMySharedPointer(const CMySharedPointer & other) : m_pointer(other.m_pointer)
    {
        Acquire();
    }

    CMySharedPointer& operator=(const CMySharedPointer & other)
    {
        Release();
        m_counter = other.m_counter;
        m_pointer = other.m_pointer;
        Acquire();
        return *this;
    }

    T& operator*()
    {
        return *m_pointer;
    }

    T* operator->()
    {
        return m_pointer;
    }

    void Info()
    {
        const int mx = 1000;
        long long p1 = (long long) m_counter;
        long long p2 = (long long) m_pointer;
        p1 %= mx;
        p2 %= mx;
        printf("MySharedPointer: m_counter = %Ld, *m_counter = %ld, *m_weakCounter = %ld, m_pointer = %Ld\n", p1, m_counter->counter, m_counter->weakCounter, p2);
    }

    template<typename K> friend class CMyWeakPointer;

private:

    CMySharedPointer(CCounters * counter, T * pointer) : m_counter(counter), m_pointer(pointer)
    {
        Acquire();
    }

    CCounters * m_counter = nullptr;
    T * m_pointer = nullptr;

    void Acquire()
    {
        if (m_pointer != nullptr) {
            if (m_counter == nullptr) {
                m_counter = new CCounters();
            }

            m_counter->counter++;
        }
    }

    void Release()
    {
        if (m_counter != nullptr) {
            m_counter->counter--;
            if (m_counter->counter == 0) {
                if (m_counter->weakCounter == 0) {
                    delete m_counter;
                    m_counter = nullptr;
                }
                if (m_pointer != nullptr) {
                    delete m_pointer;
                    m_pointer = nullptr;
                }
            }
        }
    };
};

template<typename T>
class CMyWeakPointer {
public:

    CMyWeakPointer(const CMySharedPointer<T> & ptr) : m_counter(ptr.m_counter), m_pointer(ptr.m_pointer)
    {
        Acquire();
    }
    ~CMyWeakPointer()
    {
        Release();
    }
    CMyWeakPointer(const CMyWeakPointer & other) : m_counter(other.m_counter), m_pointer(other.m_pointer)
    {
        Acquire();
    }
    CMyWeakPointer& operator=(const CMyWeakPointer & other)
    {
        Release();
        m_counter = other.m_counter;
        m_pointer = other.m_pointer;
        Acquire();
    }
    void Info()
    {
        const int mx = 1000;
        long long p1 = (long long) m_counter;
        long long p2 = (long long) m_pointer;
        p1 %= mx;
        p2 %= mx;
        printf("MyWeakPointer: m_counter = %Ld, *m_counter = %ld, *m_weakCounter = %ld, m_pointer = %Ld\n", p1, m_counter->counter, m_counter->weakCounter, p2);
    }
    CMySharedPointer<T> Lock() {
        return CMySharedPointer<T>(m_counter, m_pointer);
    }
    bool IsAvailable() {
        return m_counter != nullptr && m_counter->counter > 0;
    }

private:

    void Acquire()
    {
        if (m_counter != nullptr) {
            m_counter->weakCounter++;
        }
    }

    void Release()
    {
        if (m_counter != nullptr) {
            m_counter->weakCounter--;

            if (m_counter->weakCounter == 0 && m_counter->counter == 0) {
                delete m_counter;
                delete m_pointer;
                m_counter = nullptr;
                m_pointer = nullptr;
            }
        }
    };

    CCounters * m_counter = nullptr;
    T * m_pointer = nullptr;

};

template<typename T> CMyUniquePointer<T> make_unique()
{
    return CMyUniquePointer<T>(new T);
}
template<typename T> CMySharedPointer<T> make_shared()
{
    return CMySharedPointer<T>(new T);
}
