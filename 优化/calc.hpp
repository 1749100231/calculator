#pragma once

#include <chrono>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
/*
 *����ջʵ�ּ򵥴���ʽ�ļ���
 */

stack<char> operator_stack; // �����ջ
stack<int> num_stack;       //  ����ջ

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
     *��ջ
     TODO ά��operator_stackʹ�ó�ջ��ʱ��֤ջ����������Ǿ��нϸ��������ȼ���.
     TODO ��������ջ����������ȼ�С�ڵ�ǰջ���������ʱ��
     TODO ѹ��num_stack���������֣��Լ�operator_stackջ�������������ǰ���м��㣬
     TODO ��������������ѹ��num_stack��
    */
    for (int i = 0; i < len; ++i) {
        char c = formula[i];
        if (isNum(c)) {
            string num = "";
            num += c;
            // ���������ȫ��������
            while (i + 1 < len && isNum(formula[i + 1]))
                num += formula[++i];
            // ������ѹ������ջ
            num_stack.push(atoi(num.c_str()));
        } else if (isOperator(c)) { // ���������
                                    // ��鼴����ջ������������ȼ��Ƿ�*��С��*ջ������������ȼ�
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
     *��ջ
     */
    // cout << "��ջ" << endl;
    while (!operator_stack.empty()) {
        stack_calc();
    }

    return num_stack.top();
}
