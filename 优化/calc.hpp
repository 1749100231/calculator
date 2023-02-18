#pragma once

#include <chrono>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
/*
 *利用栈实现简单代数式的计算
 */

stack<char> operator_stack; // 运算符栈
stack<int> num_stack;       //  数字栈

bool isNum(char c)
{
    return ('0' <= c && c <= '9');
}

bool isOperator(char c)
{

    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}
int getPriority(char c)
{
    switch (c) {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}
int calc(int num1, char oper, int num2)
{
    // cout << num1 << oper << num2 << endl;
    switch (oper) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    }
    return -1;
}
void stack_calc()
{
    int num1 = num_stack.empty() ? 0 : num_stack.top();
    num_stack.pop();
    int num2 = num_stack.empty() ? 0 : num_stack.top();
    num_stack.pop();
    char oper = operator_stack.top();
    operator_stack.pop();
    num_stack.push(calc(num2, oper, num1));
}
int mutiOperatorCalc(string formula)
{
    int len = formula.length();
    int ans;
    /*
     *入栈
     TODO 维护operator_stack使得出栈的时候保证栈顶的运算符是具有较高运算优先级的.
     TODO 当即将入栈的运算符优先级小于当前栈顶的运算符时，
     TODO 压出num_stack中两个数字，以及operator_stack栈顶的运算符，提前进行计算，
     TODO 并将计算结果重新压入num_stack中
    */
    for (int i = 0; i < len; ++i) {
        char c = formula[i];
        if (isNum(c)) {
            string num = "";
            num += c;
            // 向后搜索完全整个数字
            while (i + 1 < len && isNum(formula[i + 1]))
                num += formula[++i];
            // 将数字压入数字栈
            num_stack.push(atoi(num.c_str()));
        } else if (isOperator(c)) { // 处理运算符
                                    // 检查即将入栈的运算符的优先级是否*不小于*栈顶的运算符优先级
            if (!operator_stack.empty()) {
            }
            if (c == '(')
                operator_stack.push(c);
            else if (c == ')') {
                // cout << "123";
                while (!operator_stack.empty() && operator_stack.top() != '(') {
                    stack_calc();
                }
                operator_stack.pop();
            } else {
                while (!operator_stack.empty() && getPriority(c) <= getPriority(operator_stack.top())) {
                    stack_calc();
                }
                operator_stack.push(c);
            }
        }
    }
    /*
     *出栈
     */
    // cout << "出栈" << endl;
    while (!operator_stack.empty()) {
        stack_calc();
    }

    return num_stack.top();
}
