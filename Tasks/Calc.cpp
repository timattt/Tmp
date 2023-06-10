#include <iostream>

static bool IsBadMinus(const std::string & line, int i, int j, int k)
{
    if (line[k] != '-') { // not even minus
        return false;
    }
    if (i == k) { // start of expression
        return true;
    }

    char prev = line[k - 1];
    bool isPrevOperator = prev == '*' || prev == '+' || prev == '/';
    bool isNextNumber = '0' < line[k + 1] && line[k + 1] < '9';
    return isPrevOperator && isNextNumber;
}

static char FindOperator(const std::string & line, int i, int j, int & operPos)
{
    const char operators[] = {'+', '-', '*', '/'};
    for (char op : operators) {
        int bracketsCount = 0;
        for (int k = j - 1; k >= i; k--) {
            if (line[k] == ')') {
                bracketsCount++;
            }
            if (line[k] == '(') {
                bracketsCount--;
            }
            if (line[k] == op && !IsBadMinus(line, i, j, k) && bracketsCount == 0) {
                operPos = k;
                return line[k];
            }
        }
    }

    return -1;
}

static long double Calc(const std::string & line, int i, int j)
{
    // operator
    int k = -1;
    char oper = FindOperator(line, i, j, k);
    switch (oper) {
        case '+':
            return Calc(line, i, k) + Calc(line, k + 1, j);
        case '*':
            return Calc(line, i, k) * Calc(line, k + 1, j);
        case '-':
            return Calc(line, i, k) - Calc(line, k + 1, j);
        case '/':
            return Calc(line, i, k) / Calc(line, k + 1, j);
    }

    // bracket
    if (line[i] == '(') {
        return Calc(line, i + 1, j - 1);
    }

    // number
    return std::strtold(line.substr(i, j).c_str(), nullptr);
}

int main() {
    std::string line;
    std::cin >> line;
    std::cout << Calc(line, 0, line.length()) << "\n";
}
