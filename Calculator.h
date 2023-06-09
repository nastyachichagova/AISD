//
// Created by Anastasia Chichagova on 08.06.2023.
//

#ifndef AISD_CALCULATOR_H
#define AISD_CALCULATOR_H
#include <string>
#include <sstream>
#include <iostream>
#include "Stack.h"
using namespace std;

bool is_numeric(string const& s){
    char* p;
    strtol(s.c_str(), &p, 10);
    return *p == 0;
}

bool issign(char const& c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int prec (char c){
    if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

//Парсинг строки
void parser(string& s){
    string::iterator it = s.begin();

    if(*(it) == '-'){
        it ++;
    }

    while(it != s.end()){
        if(isdigit(*it)){
            if(isdigit(*(it + 1))) {
                it += 1;
            }else if (isspace(*(it + 1))) {
                it += 2;
            }else{
                s.insert(it + 1, ' ');
                it += 2;
            }
        }else if(issign(*it) && *(it  +1 ) == '-') {
            s.insert(it + 1, ' ');
            it += 3;
        }else if((*it == '-') && (*(it - 2) == '(' || issign(*(it - 2)))){
            it += 1;
        }else{
            if(!isspace(*(it + 1))){
                s.insert(it + 1, ' ');
                it += 2;
            }else{
                it += 2;
            }
        }
    }
}

//Проверка правильности расстановки скобок
bool braces(string const& s){
    Stack<int> p;

    for(int i = 0; i < s.size(); i++){
        if(s[i]=='(' || s[i] == '{'){
            p.push(s[i]);
        }
        else{
            if(s[i] == ')' && !p.is_empty() && p.top() == '(') {
                p.pop();
            }else if (s[i] == '}' && !p.is_empty() && p.top() == '{') {
                p.pop();
            }else if ((s[i] == '}' || s[i] == ')') && p.is_empty()) {
                p.push(i);
                break;
            }
        }
    }
    if(p.is_empty()){
        return true;
    }else{
        return false;
    }
}


class Calculator {
private:
    string s;
public:
    Calculator(string ss) {
        int n = 0; //чисел
        int m = 0; //арифметический знаков
        int k = 0; //прочего

        parser(ss);

        string ss1 = ss;
        istringstream iss2(ss1);
        while (getline(iss2, ss1, ' ')) {
            if (is_numeric(ss1)) {
                n++;
            } else if (issign(ss1[0])) {
                m++;
            } else if (ss1[0] != ')' && ss1[0] != '(') {
                k++;
            }
        }


        if ((n != m + 1) || k || !m)
            throw "Ошибка: неверное выражение.\n";

        if(!braces(ss))
            throw "Ошибка: неверная скобочная последовательность.\n";

        s = ss;
    }


    //Преобразование инфиксной записи в постфиксную
    void infix_to_postfix() {
        Stack<char> st;
        istringstream iss2(s);
        string res;

        while (getline(iss2, s, ' ')) {
            if (is_numeric(s)) {
                res += s + " ";
            } else if (s == "(") {
                st.push(s[0]);
            } else if (s == ")") {
                while (!st.is_empty() && st.top() != '(') {
                    res += st.top();
                    res += ' ';
                    st.pop();
                }
                if (!st.is_empty()) {
                    st.pop();
                }
            } else {
                while (!st.is_empty() && prec(st.top()) >= prec(s[0])) {
                    res += st.top();
                    res += ' ';
                    st.pop();
                }
                st.push(s[0]);
            }
        }

        while (!st.is_empty()) {
            res += st.top();
            res += ' ';
            st.pop();
        }

        s = res;
    }

    void print() {
        cout << s << endl;
    }

    int evaluate() {
        Stack<int> st;

        infix_to_postfix();

        istringstream iss2(s);

        while (getline(iss2, s, ' ')) {
            //если число - добавляем в стек
            if (is_numeric(s))
                st.push(stoi(s));

                //если арифметический знак
            else {
                int b = st.top();
                st.pop();
                int a = st.top();
                st.pop();

                if (s == "+") {
                    st.push(a + b);
                } else if (s == "-") {
                    st.push(a - b);
                } else if (s == "*") {
                    st.push(a * b);
                } else {
                    if (!b)
                        throw "Ошибка: деление на ноль.\n";
                    else
                        st.push(a / b);
                }
            }
        }
        s = to_string(st.top());
        return st.top();
    }

};



#endif //AISD_CALCULATOR_H
