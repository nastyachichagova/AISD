//
// Created by Anastasia Chichagova on 08.06.2023.
//

#ifndef AISD_STACK_H
#define AISD_STACK_H
#include "List.h"


template<class T>
class Stack {
private:
    List<T> S;

public:
    T top() {
        return S.begin();
    }

    bool is_empty() {
        return S.is_empty();
    }

    // поместить элемент в стек
    void push(int _val) {
        S.push_front(_val);
    }

    //удалить элемент из стека
    void pop() {
        S.pop_front();
    }

    //количество элементов в списке
    int size() {
        return S.get_size();
    }
};


#endif //AISD_STACK_H
