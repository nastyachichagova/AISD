#include <iostream>
#include <string>
#include "Calculator.h"
using namespace std;




int main() {
    setlocale(LC_ALL, "Russian");

    string s;

    cout << "Для завершения введите 0" << endl;

    while (s != "0"){
        cout << "Введите выражение: " << endl;
        getline(cin, s);

        try{
            Calculator calc(s);

            cout << "Результат: " << endl;
            calc.evaluate();
            calc.print();
        }catch (const char* e){
            cout << e << endl;
        }
    }



    return 0;
}
