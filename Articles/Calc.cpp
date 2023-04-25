#include <iostream>
#include <algorithm>
#include <cstring>

double K(const char *& start, const char * end);
double P(const char *& start, const char * end);
double E(const char *& start, const char * end);

// True if start points to requested operator
bool TryOperators(const char * start, const char * end, const char * ops) {
    if (start >= end) {
        return false;
    }

    for (int i = 0, sz = strlen(ops); i < sz; i++) {
        if (*start == ops[i]) {
            return true;
        }
    }

    return false;
}

// True if start points to number
bool TryNumber(const char * start, const char * end) {
    if (start >= end) {
        return false;
    }

    char * res = nullptr;
    std::strtof(start, &res);
    return res > start;
}

// Returns operator and moves pointer
char ConsumeOperator(const char *& start, const char * end, const char * ops) {
    if(!TryOperators(start, end, ops)) {
        throw std::string("Some of operators [") + ops + std::string("] was expected");
    }
    return *(start++);
}

// Returns number and moves pointer
double ConsumeNumber(const char *& start, const char * end) {
    if (!TryNumber(start, end)) {
        throw std::string("Number was expected");
    }
    return std::strtof(start, (char**) &start);
}

// K ::= number | (E)
double K(const char *& start, const char * end) {
    // number
    if (TryNumber(start, end)) {
        return ConsumeNumber(start, end);
    }

    // (E)
    ConsumeOperator(start, end, "(");
    double res = E(start, end);
    ConsumeOperator(start, end, ")");

    return res;
}

// P ::= K {[*/] K}*
double P(const char *& start, const char * end) {
    double res = K(start, end);

    while (TryOperators(start, end, "/*")) {
        char op = ConsumeOperator(start, end, "/*");

        double res1 = K(start, end);

        if (op == '*') {
            res *= res1;
        }
        if (op == '/') {
            res /= res1;
        }
    }

    return res;
}

// E ::= P {[+-] P}*
double E(const char *& start, const char * end) {
    double res = P(start, end);

    while (TryOperators(start, end, "+-")) {
        char op = ConsumeOperator(start, end, "+-");

        double res1 = P(start, end);

        if (op == '+') {
            res += res1;
        }
        if (op == '-') {
            res -= res1;
        }
    }

    return res;
}

double Calculate(const std::string & str) {
    std::string in = str;
    std::remove(in.begin(), in.end(), ' ');
    const char * start = (char*) in.c_str();
    const char * end = start + in.length();
    return E(start, end);
}

int main() {
    std::string expr;
    std::cin >> expr;
    std::cout << Calculate(expr);
    return 0;
}
