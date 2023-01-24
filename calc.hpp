#include <algorithm>
#include <iostream>
#include <math.h>
#include <regex>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

std::string replace(std::string str, const std::string &pattern, const std::string &to)
{
    std::regex r(pattern);
    return std::regex_replace(str, r, to);
}

bool isNum(char c)
{
    return ('0' <= c && c <= '9');
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double SingleOperatorCalc(string formula)
{
    int len = formula.length();
    char operator_ = '+';
    int index = 0;
    double num1, num2;
    // 找到运算符
    for (unsigned int i = 0; i < len; i++) {
        char t = formula[i];
        if (isOperator(t)) {
            operator_ = t;
            index = i;
            break;
        }
    }

    num1 = atof(formula.substr(0, index).c_str());
    num2 = atof(formula.substr(index + 1, len).c_str());
    switch (operator_) {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;

    default:
        break;
    }
    return 0;
}

double _MutipleOperatorCalc(string formula)
{
    // cout << formula << endl;
    int len = formula.length();
    for (unsigned int i = 0; i < len; i++) {
        char t = formula[i];
        if (t == '*' || t == '/') {
            int L = i, R = i;
            while (L - 1 >= 0 && !isOperator(formula[L - 1])) {
                L--;
            }
            while (R + 1 <= len - 1 && !isOperator(formula[R + 1])) {
                R++;
            }
            int tLen = R - L + 1;                                      // 子代数式的长度
            double sAns = SingleOperatorCalc(formula.substr(L, tLen)); // 子代数式的答案
            return _MutipleOperatorCalc(formula.replace(L, tLen, std::to_string(sAns)));
        }
    }

    for (unsigned int i = 0; i < len; i++) {
        char t = formula[i];
        if (isOperator(t) && i != 0) {
            int index = i;
            int L = 0, R = index;
            while (R + 1 <= len - 1 && !isOperator(formula[R + 1])) {
                R++;
            }
            int tLen = R - L + 1;                                      // 子代数式的长度
            double sAns = SingleOperatorCalc(formula.substr(L, tLen)); // 子代数式的答案
            return _MutipleOperatorCalc(formula.replace(L, tLen, std::to_string(sAns)));
        }
    }
    return atof(formula.c_str());
}

string __MutipleOperatorCalc(string formula)
{
    /*
        (1+2)/3
    */
    cout << "=" << formula << endl;
    int len = formula.length();
    int L = 0;
    int R = len;
    for (int i = 0; i < len; i++) {
        if (formula[i] == '(') {
            // 记录左括号
            L = i;
        } else if (formula[i] == ')') {
            // 搜索到右括号就结束
            R = i;
            int tLen = R - L - 1;                                            // 子代数式的长度
            double sAns = _MutipleOperatorCalc(formula.substr(L + 1, tLen)); // 子代数式的答案
            return __MutipleOperatorCalc(formula.replace(L, tLen + 2, std::to_string(sAns)));
            break;
        }
    }
    return formula;
}

double MutipleOperatorCalc(string formula)
{
    formula = replace(formula, "--", "+");
    formula = __MutipleOperatorCalc(formula);
    return _MutipleOperatorCalc(formula);
}
