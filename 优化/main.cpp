#include "calc.hpp"

int main()
{
    string formula;
    cout<<"input:";
    cin >> formula;
    cout << mutiOperatorCalc(formula);
    system("pause");
    return 0;
}
