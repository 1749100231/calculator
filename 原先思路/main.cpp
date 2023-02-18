#include "calc.hpp"

int main()
{
    string formula;
    cout<<"input:";
    cin >> formula;
    cout << MutipleOperatorCalc(formula);
    system("pause");
    return 0;
}
